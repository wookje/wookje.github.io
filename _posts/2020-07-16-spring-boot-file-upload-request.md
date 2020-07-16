---  
layout: post  
title: 'Spring Boot 프로젝트에서 MultipartFile을 수신할 때 주의점'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 15:57  
tags: [spring-boot, kotlin]  
  
---  

## 잡것들

`Content-Type`은 `multipart/form-data`이고, form-data를 보내므로 `@RequestBody` 같은 어노테이션을 붙이면 안 됩니다.  

또, File 외에 primitive type의 fields를 함께 수신하고 싶어도 데이터 타입은 무조건 String입니다.  

text만 받는 것이 http 표준인지는 잘 모르겠는데, 적어도 제가 작업했던 환경에서는 그랬고 저는 표준이나 표준 비슷한 거라고 알고 있었습니다.  

찾아보니 표준([https://www.ietf.org/rfc/rfc2388.txt](https://www.ietf.org/rfc/rfc2388.txt))에 무조건 String이라고 명시되어 있지는 않긴 한데, client에서 정수를 보내고 server에서 정수형으로 받으면 값이 안 들어가고 `null`이 찍힙니다.  

다른 프레임워크나 언어에서는 어떤지 잘 모르겠습니다. Kotlin과 Spring Boot를 사용할 때는 그랬습니다.  

## DTO 사용시 반드시 var을 사용할 것

```kotlin
var file: MultipartFile? (O)

val file: MultipartFile? (X, null)
```

(아래는 추측입니다)

primitive value들은 DTO 객체를 만드는 시점에 값을 바로 집어 넣을 수 있지만  

파일은 뭔가 비동기 처리가 되는지, 아니면 단순히 수신이 완료되는 시점을 보장할 수 없어서 그런지 모르겠지만, 일단 temp object를 constructor에 넣어서 DTO 객체를 만들어 놓고, 파일 수신이 완료된 뒤에서야 바이너리를 덮어씌우는 것 같습니다.  

File list를 받을 때는, `MutableList<MultipartFile>`가 아닌 `List<MultipartFile>`로도 작동하는 걸로 보아, List에 Add 하는 게 아니라 일단 dummy object list를 만들어놓고 나중에 set 해주는 것 같습니다.  

http spec이랑 관련있는 내용은 아니어 보이고, 서블릿 근방의 어딘가에서 어떻게 처리하는지, 그게 코틀린에 와서는 어떻게 동작하는지 알아봐야 할 것 같은데 찾아보기는 좀 만만치 않아보이고 귀찮네요... 크리티컬한 이슈는 아니어서 저렇게 하면 된다 정도로 넘어갑니다.  