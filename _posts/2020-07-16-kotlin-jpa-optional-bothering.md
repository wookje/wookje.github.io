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
val entity = somethingRespoitory.findById(id);
```

여기서 `entity`의 type은 `Optional<T>`이다. 왜냐면 interface가 `Optional<T> findById(ID var1);` 이따구로 생겼기 때문이다.  

이 멍청한 interface는 `Optional<Something!>`를 뱉는다. 그러면 어떤 문제가 벌어질까?

`entity.get()`으로 그 안에 들어있는 데이터를 가져올 수 있다.

```java
/**
* If a value is present, returns the value, otherwise throws
* {@code NoSuchElementException}.
*
* @apiNote
* The preferred alternative to this method is {@link #orElseThrow()}.
*
* @return the non-{@code null} value described by this {@code Optional}
* @throws NoSuchElementException if no value is present
*/
public T get() {
    if (value == null) {
        throw new NoSuchElementException("No value present");
    }
    return value;
}
```

만약 find 결과가 없어서 반환할 게 없으면 null을 뱉는 게 아니고 Exception을 던져버린다.  

```kotlin
val data = somethingRepository.findById(id);
```

이렇게만 해도 충분했어야 할 코드가

```kotlin
val entity = somethingRespoitory.findById(id);
val data: Something?
try {
    data = entity.get()
} catch (e: Exception) {
    logger.error("serious?")
}
```

이따구로 되어버린다.  

kotlin-java 100% 호환 정말 대단합니다 ^^;  

그렇다고 `(1)`처럼 함수를 재정의 할 수도 없다. (오버라이딩도 안 됨)  

그래서 `(2)`처럼 사용했다. 일부러 조건을 하나 더 넣어서 코드의 유지보수성과 가독성을 살렸다.  

퍼포먼스가 그렇게 중요한 프로젝트도 아니었고, 어차피 id가 primary key여서 가벼운 조건 하나 추가한다고 크게 느려지지 않을 것이라는 계산이 깔려있다. (어차피 병목은 저런 간단한 곳에서 발생하지 않는다.)  