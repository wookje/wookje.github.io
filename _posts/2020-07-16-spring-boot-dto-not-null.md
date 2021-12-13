---  
layout: post  
title: 'Spring Boot 프로젝트에서 Request Dto에 NotNull 사용하기'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 16:25  
tags: [spring-boot, kotlin]  
  
---  

```kotlin
import javax.validation.Valid

@PostMapping("/hi")
fun someFunction(@RequestBody @Valid dto: Dto)
```

```kotlin
import javax.validation.constraints.NotNull

data class Dto(
    @field:NotNull
    var temp1: String? = null,

    var temp2: String? = null
)
```

꼭 dto 앞에 `@Valid`가 붙어 있어야 validation을 해줍니다.

`@RequestBody @Valid dto: Dto`에서 `@Vaild`가 뒤쪽에 있어야 동작했었는지, 순서가 상관 없었는지는 잘 기억이 안 나네요.

Response Dto에는 NotNull 어노테이션이 동작하지 않았습니다.  

그리고 `@NotNull`은 java annotation인데, kotlin에서 사용할 때는 꼭 `@field:NotNull`로 필드가 NotNull임을 명시해 주어야 한다고 들었습니다.  