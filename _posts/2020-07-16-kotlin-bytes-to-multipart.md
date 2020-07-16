---  
layout: post  
title: 'Kotlin에서 ByteArray를 MultipartFile로 post하기'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 22:32  
tags: [kotlin, http, rest]  
  
---  

```kotlin
val file = object : ByteArrayResource(byteArray) {
    override fun getFilename(): String {
        return "tempFileName.ext"
    }
}

val headers = HttpHeaders()
headers.contentType = MediaType.MULTIPART_FORM_DATA

val body: MultiValueMap<String, Any> = LinkedMultiValueMap()
body.add("file", file)

val requestEntity = HttpEntity(body, headers)
val response = restTemplate.exchange(uri, HttpMethod.POST, requestEntity, object : ParameterizedTypeReference<String?>() {})
```

구현체를 못 봐서 정확히는 모르지만, 추측하자면 `MultiparFile`의 interface에는 `getResource()`가 정의되어 있고, `Resource` 타입의 객체를 리소스로서 들고 있는 것 같다.

`ByteArrayResource`는 `Resource`를 조상 클래스로 두고 있는, `ByteArray`를 리소스로 관리하는 클래스이므로

`ByteArrayResource`를 `Resource`로 업캐스팅해서 전송하면 무리없이 실행되는 것을 확인할 수 있다.

다만, 일반적으로 파일을 읽어온 리소스 객체와는 다르게 임의로 생성한 객체여서 파일 이름이 null이다.

파일 이름이 null이면 수신하는 측에서 처리하기가 곤란했었나, 제대로 수신이 안 되었나는 기억이 안 난다.

어차피 확장자도 붙여서 알려줘야 하므로 적당히 `getFilename()`을 오버라이딩한 임시 객체를 만들어서 사용하자.

그러면 깔끔하게 바이너리를 `multipart/form-data`로 전송할 수 있다.