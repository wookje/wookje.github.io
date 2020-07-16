---  
layout: post  
title: 'Spring Boot 프로젝트에서 파일 리소스 관리하기'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 15:43  
tags: [spring-boot, kotlin, java]  
  
---  

```kotlin
// resources/dir/file.txt
@Value("classpath:dir/file.txt")
lateinit var resource: Resource
```

## getResources() 함수와의 차이점

`getResources()` 함수는 자바 내장 함수입니다. `(java.lang.ClassLoader.getResources)`  

`getResources()`로 파일을 가져오면 ide상의 로컬 개발 환경에서 잘 돌아갈 수 있지만, jar를 뽑아서 실행할 때 uri가 바뀌기 때문에 아마 화가 나게 될 수도 있습니다.  

`getResources()`로 해도 잘 되는 경우도 있는데, 제가 했던 프로젝트의 경우는 잘 안 되었습니다. 코틀린이라 그런가?  

반면 위에서는 spring annotation을 사용했기 때문에 스프링이 path를 관리해 줍니다.  

그래서 jar를 서버에 올려서 실행할 때도 문제가 없(다고합)니다.  

## resources/static 에 넣으면 안 돼요  

저는 `resources/static/dir/file.ext`와 같은 경로에 파일을 집어넣었다가 '왜 안 되지?' 하면서 고통 받았습니다.  
`resources/static`에는 css 등의 스프링스러운 파일들을 스프링이 관리하고 있기 때문에 맘대로 사용할 수 없다고 합니다.  
그래서 `resources/dir/file.ext`와 같이 경로를 바꿔서 해결했습니다.  

## 불러온 Resource의 uri로 다시 File 객체를 만들면 안 됩니다

```kotlin
val file = File(resource.uri)
```

애써 Spring 컨테이너로 가져온 리소스를, 굳이 다시 uri를 찾아서 가져오는 멍청한 짓을 할 필요는 없죠... (본인이 했었음) 저러면 `getResources()`랑 똑같아져서 파일 못 가져옵니다 (...)

## @Value를 포함하는 클래스는 Bean에 등록되어 있어야 합니다

Bean에 등록되지 않은 Class를 스프링 컨테이너가 관리해 주지 못하니까 당연합니다.  