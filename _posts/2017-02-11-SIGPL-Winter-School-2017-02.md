---
layout: post
title: 'SIGPL Winter School 2017 2일차 정리'
author: wookje.kwon
comments: true
date: 2017-02-11 11:51
tags: [sigpl, sigpl-winter-school-2017, programming-language, proof, number-theory, coq, math]

---

## SIGPL Winter School 2017 2일차 정리

### Martin Ziegler Logic 강의

tautology - always true  
satisfiability - true but not always  
inconsistency - false  

emptyset : false -> true  

추후에 추가 예정

### 다시 Coq 강의

istrue = predicate

type check 동시에 evaluate

```
P -> Q     P
------------
      Q
```

증명 불가능한 함수는 짤 수 없다  
1+(n:nat)를 짤 수는 없지만 1+(n:nat)->false 는 가능  

evaluation은 증명을 단순화 시키는 것, simplify  
: type checking 할 때 evaluation 해도 안전함  
: eval termination 보장됨  

```
e : T	T ->* T'
     	      = ?
e : S	S ->* S'
```

```
e : T   S->T (S===T)
--------------------
       e : s
```

intentionaly equip  
1 + n === S(n)  
e : vector (1+n)    E : vector (S(n))  

type이 달라도 convertable 하면 okok  

`forall n:nat, istrue (evenb n) -> true (evenb (2+n))`  
simpl 가능  

`forall n:nat, istrue (evenb n) -> true (evenb (n+2))`  
simpl 불가, 다른 방법으로 구현해야  

```
Inductive even : nat -> Type :=
  | zero_is_even : even 0
  | succ_succ_even (n : nat) (pf: even n) : even (S(S(n))
```

* zero_is_even : even 0
* succ_succ_even 0 zero_is_even : even (S(S(n))
* succ_succ_even (S(S(0)) (succ_succ_even 0 zero_is_even) : even (S(S(S(S 0))))

```
Definition induction_for_nat :
  forall P : nat -> Type,
    P 0 ->
      (forall n : nat, P n -> P (S n)) ->
  forall n : nat, P n
```

수학적인 statement로 쓰고 싶으면 Prop  
데이터로 쓰고 싶으면 Type (다르긴 함, 몰라도 됨)  

Type : hierarchy check 함  
Prop : hierarchy check 안 함  

**Prop의 직관**
* even n : Prop
* e: even n 
* Prop은 match가 없음, element 구분 x, 괴델의 불완전성 뭐시기 없음
* forall (P: Type) (x y : P), x = y. false 증명 불가
* forall (P: Prop) (x y : P), x = y. false 증명 가능
* Prop -> Prop은 case analysis 가능
* Prop이 Type의 subset
* Prop은 singleton set
* Prop -> Prop도 Prop
* (nat -> (even 2 : Prop)) : Prop     끝이 Prop이면 Prop
* Prop 명시 안 해주면 Type으로 유추할 때도 있음
* inference가 complete하지 않을 듯 (뇌피셜)