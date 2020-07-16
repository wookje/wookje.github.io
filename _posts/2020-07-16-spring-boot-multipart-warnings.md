---  
layout: post  
title: 'Spring Boot 프로젝트에서 DTO를 통해 MultipartFile을 받을 때 주의점'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 15:59  
tags: [spring-boot, kotlin]  
  
---  

```kotlin
var file: MultipartFile? (O)

val file: MultipartFile? (X, null)
```

(아래는 추측입니다)

primitive value들은 DTO 객체를 만드는 시점에 값을 바로 집어 넣을 수 있지만  

파일은 뭔가 비동기 처리가 되는지, 아니면 단순히 수신이 완료되는 시점을 보장할 수 없어서 그런지 모르겠지만, 일단 temp object를 constructor에 넣어서 DTO 객체를 만들어 놓고, 파일 수신이 완료된 뒤에서야 바이너리를 덮어씌우는 것 같습니다.  

File list를 받을 때는, `MutableList<MultipartFile>`가 아닌 `List<MultipartFile>`로도 작동하는 걸로 보아, List에 Add 하는 게 아니라 일단 dummy object list를 만들어놓고 나중에 set 해주는 것 같습니다.  