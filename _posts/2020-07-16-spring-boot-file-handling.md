---  
layout: post  
title: 'Spring Boot에서 File을 송수신할 때의 disk I/O'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 23:33  
tags: [spring-boot, kotlin, java]  
  
---  

## dist I/O는 위험하다!

우리 process의 자원만 의도한만큼 잡아먹는다면 아무 문제가 없지만, 만약 한 머신에서 여러 서버가 돌고 있다면?

disk I/O는 머신 전체에 영향을 미치기 때문에 굉장히 신중해야 한다. 사실 그걸 떠나서 그냥 느리기도 하다.

기본적으로, JVM 기반의 언어(Java, Kotlin)에서 사용하는 File 또는 Resource 관련 class들은 in-memory data를 관리하는 게 아니다.

이러한 class들은 input stream을 이용해서 binary를 '읽어 오는' 작업과 그 파일의 메타 데이터를 '관리하는' 역할을 수행한다.

## 파일을 수신했다!

나는 `MultipartFile` 외에 다른 방법으로 파일을 받아본 적이 없어서 `Multipartfile`만 언급하겠다.

`MultipartFile`을 수신하면, 서블릿은 이 파일을 disk의 temp directory에 임시로 '저장'한다.

`MultipartFile`은 `Resource`를 member로 가지고 있고, `Resource`는 binary를 input stream을 통해 읽어 오는데, 서블릿은 binary를 disk에서 직접 읽는 구현체를 사용하는 것 같다. (그도 그럴 것이 서버 띄우는 머신이 어지간히 고사양 아닌 이상, 메모리에서 파일을 들고 있기는 좀 많이 부담스럽다.)

다시 말해, 일단 파일을 수신하면 I/O가 무조건 발생한다.

disk에 저장된 파일을 송신하는 경우라면, 송신할 때도 마찬가지로 I/O가 발생한다.

## in-memory Resource 객체 생성하기

어떤 api를 통해 binary를 획득해서 binary만 메모리에 들고 있거나, binary를 직접 generate 하는 등의 경우에, 이 binary를 in-memory 객체로 관리하고 싶은 경우가 있다.

하지만 대부분의 관련 class는 disk I/O가 여러번 발생할 뿐더러, 여러 meta data를 직접 설정해줘야 해서 좀 까다로운 경우가 많다.

```kotlin
val file = object : ByteArrayResource(byteArray) {
    override fun getFilename(): String {
        return "tempFileName.ext"
    }
}
```

그런 경우에는 위와 같이 `ByteArrayResource`를 이용해서 in-memory로 관리할 수 있다...고 추측한다. (솔직히 이거 디스크에 쓰면 에바지 ㅋㅋ)

구현체를 본 적이 없어서 저게 실제로는 disk에 임시로 저장하고 읽어오는 건지 뭔지는 잘 모른다.

`ByteArrayResource`는 `getInputStream()`을 호출할 때마다 새로운 input stream을 뱉는다고 한다. 

내 예상에는 binary를 메모리에 들고 있으면서, `ByteArrayInputStream`을 써서 memory에서 읽어오도록 되어 있을 것 같다.

그런 방식이 아니라면 애초에 이 파일에 대한 meta-data를 생성자에서 더 요구했어야 한다.

`ByteArrayResource`가 `AbstractResource`를 상속하고 있어서 이 주장이 조금 더 강력해진다(?)

그리고 (최초에 객체 생성시 disk I/O가 발생하는지 여부를 떠나서) 메모리에 오른 다음부터는 disk I/O가 여러번 발생하지 않는다고 한다.

정리하면 내 주장은 '`ByteArray`로 `ByteArrayResource` 객체를 만들면 disk I/O가 0회 발생한다.'이고, 내 주장이 틀렸을 때의 가설은 '`ByteArray`로 `ByteArrayResource` 객체를 만들면 최초 생성시에 disk I/O가 1회 발생한다.'이다.

내 주장이 맞다면 더 좋겠지만, 틀리더라도 최초 1회만 I/O가 발생하니 나쁠 건 없다.

이 부분은 허위사실일 가능성이 있으므로 조심하자.

(근데 이거 여러모로 메모리 누수에 조심해야 할 부분이 많아보인다)