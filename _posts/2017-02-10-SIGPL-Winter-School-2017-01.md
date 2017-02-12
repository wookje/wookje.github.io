---
layout: post
title: 'SIGPL Winter School 2017 1일차 정리'
author: wookje.kwon
comments: true
date: 2017-02-11 00:30
tags: [sigpl, sigpl-winter-school-2017, programming-language, proof, number-theory, coq, math]

---

## SIGPL Winter School 2017 1일차 정리

**주어가 명시되지 않은 문장은 대부분 Coq가 그렇다는 의미로 받아들이면 대부분 알아들을 수 있을 것이다.**

Coq는 실제 계산할 때 퍼포먼스 때문에 nat에서 다른 타입으로 계산을 허용한다고 한다.  

Coq로 짠 코드를 실행하다가 오버플로우 등의 현실적인 에러가 발생할 수 있지만, 애초에 Coq는 Theorem을 증명하는 데에 목적을 두기 때문에 Coq에 대해 문제를 제기할 필요는 없다.  


문제 없이 Type Check를 통과하면 안전하다고 보장된다. 이의를 제기할 필요는 없다. Type Check를 통과하면 안전하다는 사실이 이미 다 검증되어있다.  

~~패턴매칭 할 때 o => o | S m => m 이면 o => o | S m => m만 가능  
근데 symantic sugar로  3개도 됨~~ (도대체 무슨 내용을 적어놓은 건지는 모르겠지만 일단 그렇다고 한다.)  

Coq에서 fix는 리턴타입을 명시하지 못하도록 강제한다 : fix 자체가 재귀적이기 때문에 Type이 명백하다.

S n은 재귀적으로 다음과 같이 표현된다 : S S n-1, S S S n-2, S S S S n-3, ...

Coq의 Check는 기본적으로 decrease theory? (뭐 그런 비슷한) 에 의해 `해당 함수가 감소하다가 종료된다`는 체크를 한다.  
의미있는 반복한 허용한다는 의미와도 같다.  
가끔씩 안 돌아갈 때도 있는데 그건 Coq가 바보라서 그렇다.  
적당히 바꿔서 짜면 돌아간다.  
어떤 함수 F와 동치인 F'은 반드시 구현할 수 있음이 보장되어있다.(ex: 퀵소트와 버블소트, 퍼포먼스는 다르지만, 결국 리스트를 정렬하는 함수이다)  
체크를 통과하면 그 함수는 끝난다고 보장된다.  

수학적 귀납법을 이용해 증명하기 때문에 직접 숫자를 대입할 필요가 전혀 없다  
: case 1+1, case 1+2, case 1+3 ...  

~~순수한 수학 함수를 표현하는 syntax~~ (이건 또 뭘 메모한 거야)

시멘틱 슈가는 별로 의미가 없다. 어차피 시멘틱 슈가도 4개의 룰에 의해 정의되기 때문에, 사용하지 않아도 증명 가능하다.  

1진법을 사용하는 이유: 증명하기가 가장 쉬움, 대신 느림  

Check (Type : Type).
: 대부분의 경우에 잘 돌아가지만 특별한 경우에 에러가 발생한다
: 그런 경우엄청 fancy한 트릭을 사용해서 해결할 수 있다
: 어려우니까 에러가 발생하면 그 때 알아보자
: 증명할 때 엄청 유용하게 쓴다고 한다

Type은 모든 set들의 집합(Set of Set)이다.

Coq를 수학답게 만들어주는 우아한 것, 수학과 프로그래밍의 갭을 줄여주는
: Dependent function space

```
Definition btype (b: bool)
  : Type
:=
  | true => nat
  | false => bool
  end.

Definition foo (b: bool)
  : btype b
:=
  | true => 100
  | false => true
  end.
```

```
Compute foo true.  : nat
Compute foo false. : bool
```

```
Check foo.
foo
  : forall b : bool, btype b
argument is bool, return type is (b:btype)
```

`nat -> nat` = `forall (_:nat), nat` (argument is nat, return type is nat)
```
e1 : Type
e2 : Type
forall (x:e1), e2 : Type
```

```
Definition foo (b: bool)
  : match b with
    | true => nat
    | false => bool
  end
```
는 결국 : Type (Type은 모든 집합을 원소로 갖기 때문)

n을 받아서 길이가 n인 벡터를 리턴
- forall (n: nat), vector n (길이가 반드시 보장됨)
- nat -> list (길이가 보장되지 않음)
- `f : nat -> list` // f(n) must return a list of length n
- 증명의 관점, 명시적임

fun은 fix의 special case  
: 수학적으로는 같지만 내부 구현의 차이
