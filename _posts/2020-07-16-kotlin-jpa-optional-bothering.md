---  
layout: post  
title: 'Kotlin에서 JPA 기본 repository interface 사용시 불편한 점'  
author: wookje.kwon  
comments: true  
date: 2020-07-16 16:38  
tags: [jpa, kotlin]  
  
---  

JPA의 respository interface를 **코틀린에서** 사용하면 조금 불편한 상황이 발생한다.

```kotlin
interface SometingRepository : CrudRepository<Something, Long> {
    // (1) fun findById(id: Long): Something?
    // (2) fun findByIdAndActiveIsTrue(id: Long): Something?
}
```

```kotlin
val entity = somethingRespoitory.findById(id);
```

여기서 `entity`의 type은 `Optional<T>`이다. 왜냐면 interface가 `Optional<T> findById(ID var1);` 이렇게 생겼기 때문이다.

이 interface는 `Optional<Something!>`를 뱉는다. 그러면 어떤 문제가 벌어질까?

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

이렇게 되면 좋겠는데

```kotlin
val entity = somethingRespoitory.findById(id);
val data: Something?
try {
    data = entity.get()
} catch (e: Exception) {
    logger.error("serious?")
}
```

이렇게 해야 한다. (물론 자바에서는 항상 저렇게 해야 함)  

그렇다고 `(1)`처럼 함수를 재정의 할 수도 없다. (오버라이딩도 안 됨)  

그래서 `(2)`처럼 사용했다.  

(근데 포스팅 쓰면서 알았는데 `findAllById`는 `(Mutable)Iterable<Something!>`을 뱉는다.)