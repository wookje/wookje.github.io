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

`@RequestBody @Valid dto: Dto`에서 `@Vaild`가 뒤쪽에 있어야 동작했었는지, 순서가 상관 없었는지는 잘 기억이 나지 않습니다. 테스트하긴 귀찮네요...  

Response Dto에는 NotNull 어노테이션이 동작하지 않았습니다. 그래도 명시해 주면, 나중에 배포하거나 일할 때 조금 더 편해서 저는 그냥 써줬습니다.  

그리고 `@NotNull`은 java annotation인데, kotlin에서 사용할 때는 꼭 `@field:NotNull`로 필드가 NotNull임을 명시해 주어야 한다고 들었습니다.  

Kotlin에서 class field들의 setter와 getter가 기본으로 제공되는 것과 관련이 있다고 했는데, 정확한 내용은 까먹었습니다. 근데 안 붙여도 어떤 경우에는 되긴 되더라구요(?)