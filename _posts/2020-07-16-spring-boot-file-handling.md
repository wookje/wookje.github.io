---  
layout: post  
title: 'Spring Boot에서 File을 송수신할 때의 disk I/O'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 23:33  
tags: [spring-boot, kotlin, java]  
  
---  

기본적으로, JVM 기반의 언어(Java, Kotlin)에서 사용하는 File 또는 Resource 관련 class들은 in-memory data를 관리하는 게 아니다.

이러한 class들은 지정한 파일의 uri를 기억해두고, input stream을 이용해서 Disk에 저장된 바이너리를 '읽어 오는' 작업과 그 파일의 메타 데이터를 '관리하는' 역할을 수행한다.

## 파일을 수신했다!

나는 `MultipartFile` 외에 다른 방법으로 파일을 받아본 적이 없어서 `Multipartfile`만 언급하겠다.

`MultipartFile`을 수신하면, 서블릿이 이 파일을 물리적인 temp directory에 임시로 파일을 '저장'한다.

왜냐면 `MultipartFile`은 `Resource`를 데이터로 관리하고, `Resource`는 바이너리를 disk에서 읽어오는 class이기 때문이다. ('p이기 때문에 q이다'라는 주장은 아니다. 하나의 이유일 뿐이다.)

다시 말해, 일단 파일을 수신하면 I/O가 무조건 발생한다.

disk에 저장된 파일을 송신하는 경우라면, 송신할 때도 마찬가지로 I/O가 발생한다.

## in-memory Resource 객체 생성하기

어떤 api를 통해 binary를 획득해서 binary만 메모리에 들고 있거나, binary를 직접 generate 하는 등, in-memory binary를 파일 관련 객체로 관리하고 싶은 경우가 있다.

하지만 이 경우에는 `File` class를 사용하면 disk I/O가 여러번 발생할 뿐더러, 여러 meta data를 직접 설정해줘야 해서 좀 까다롭다.

```kotlin
val file = object : ByteArrayResource(byteArray) {
    override fun getFilename(): String {
        return "tempFileName.ext"
    }
}
```

이 경우에는 위와 같이 임시로 파일 객체를 만들어서 in-memory로 관리할 수 있다...고 추측한다. (솔직히 이거 디스크에 쓰면 에바지 ㅋㅋ)

구현체를 본 적이 없어서 저게 실제로는 disk에 임시로 저장하고 읽어오는 건지 뭔지는 잘 모른다.

하지만 내 예상에는 binary를 메모리에 들고 있으면서, `ByteArrayInputStream`을 써서 memory에서 읽어오도록 되어 있을 것 같다.

`ByteArrayResource`가 `AbstractResource`를 상속하고 있어서 더욱 더 이 주장에 강력함을 더할 수 있다(?)

구글링에 의하면, (`ByteArray`로 객체를 생성했을 때 dist I/O가 발생하는지 여부를 떠나서) 일단 메모리에 오른 다음부터는 disk I/O를 여러번 실행하지 않는다고 한다.

정리하면 내 주장은 '`ByteArray`로 `ByteArrayResource` 객체를 만들면 disk I/O가 0회 발생한다.'이고, 내 주장이 틀렸을 때의 가설은 '`ByteArray`로 `ByteArrayResource` 객체를 만들면 최초 생성시에 disk I/O가 1회 발생한다.'이다.

이 부분은 허위사실일 가능성이 있으므로 조심하자.