---  
layout: post  
title: 'Kotlin에서 JPA 기본 repository interface 사용시 짜증나는 점'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 16:38  
tags: [jpa, kotlin]  
  
---  

JPA가 자랑하는 장점 중 하나인 respository interface를 **코틀린에서** 사용하면 짜증나는 상황이 발생한다.

```kotlin
interface SometingRepository : CrudRepository<Something, Long> {
    // (1) fun findById(id: Long): Something?
    // (2) fun findByIdAndActiveIsTrue(id: Long): Something?
}
```

```kotlin
var entity = somethingRespoitory.findById(id);
```

여기서 `entity`의 type은 `Optional<Something>`이다. 왜냐면 interface가 `Optional<T> findById(ID var1);` 이따구로 생겼기 때문이다.  

`Optional`로 뱉으면 어떤 문제가 벌어질까? 이 멍청한 interface의 가장 큰 문제는 `Optional<Something>`가 아니라, `Optional<Something?>`을 뱉는다.  

왜 그렇게 되는지 머리로는 이해가 되는데 가슴으로는 이해가 되지 않는 어둠의 코틀린 중 일부이다. (kotlin-java 100% 호환 대단합니다 ^^;)  

이대로 코드를 작성하면, 물음표가 엄청나게 많은 호기심 가득한 코드를 짜게 될 수 있다. (혹은 느낌표가 가득한 자신감 넘치는 코드를 짜게 될 수도 있다.)

그렇다고 `(1)`처럼 함수를 재정의 할 수도 없다.