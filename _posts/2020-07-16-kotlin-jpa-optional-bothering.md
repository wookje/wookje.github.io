---  
layout: post  
title: 'Kotlin에서 JPA 기본 repository interface 사용시 짜증나는 점'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 16:38  
tags: [jpa, kotlin]  
  
---  

JPA가 자랑하는 장점 중 하나인 respository interface를 **코틀린에서** 사용하면 굉장히 짜증나는 상황이 발생한다.

```kotlin
interface SometingRepository : CrudRepository<Something, Long> {
    // (1) fun findById(id: Long): Something?
    // (2) fun findByIdAndActiveIsTrue(id: Long): Something?
}
```

```kotlin
var entity = somethingRespoitory.findById(id);
```

여기서 `entity`의 type은 `Optional<T>`이다. 왜냐면 interface가 `Optional<T> findById(ID var1);` 이따구로 생겼기 때문이다.  

`Optional`로 뱉으면 어떤 문제가 벌어질까? 이 멍청한 interface의 가장 큰 문제는 `Optional<Something>`가 아니라, `Optional<Something?>`을 뱉는다는 점이다.  

kotlin-java 100% 호환 정말 대단합니다 ^^;  

이대로 코드를 작성하면, 물음표가 엄청나게 많은 호기심 가득한 코드를 짜게 될 수 있다. (혹은 느낌표가 가득한 자신감 넘치는 코드를 짜게 될 수도 있다.)

그렇다고 `(1)`처럼 함수를 재정의 할 수도 없다. (오버라이딩도 안 됨)  

그래서 `(2)`처럼 사용했다. 일부러 조건을 하나 더 넣어서 코드의 유지보수성과 가독성을 살렸다.  

퍼포먼스가 그렇게 중요한 프로젝트도 아니었고, 어차피 id가 primary key여서 가벼운 조건 하나 추가한다고 크게 느려지지 않을 것이라는 계산이 깔려있다. (어차피 병목은 저런 간단한 곳에서 발생하지 않는다.)  