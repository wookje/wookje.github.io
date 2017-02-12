---
layout: post
title: 'SIGPL Winter School 2017 3일차 정리'
author: wookje.kwon
date: 2017-02-11 11:56
tags: [sigpl, sigpl-winter-school-2017, programming-language, proof, number-theory, coq, math]

---

## SIGPL Winter School 2017 3일차 정리

### 마지막 날

**Type Check**
: Val/Computation.Inductive/Fuction 4가지 룰이랑 Eval만 사용해서 체크함
: logical한 step

4개의 룰만 있으면 거의 모든 증명을 할 수 있음  
나머지 불가능한 것도 axiom? 추가하면 가능  

프로그램 식을 그대로 읽으면 증명하는 거랑 똑같음  

**->**은 non dependent function
**forall**은  dependent function

==forall, ->, =, P -> false, True, False, /|, |/, exists==
이것만 가지고 모든 set을 만들 수 있음  

set이 바로 proposition (coq에서, m zigler set은 set prop는 prop)  
수학자들은 일찍, 컴과학자들은 1940 1950쯤 같다 발견  

`Check (forall n: nat, n=0 /| n=1 : Prop).`  
거짓이지만 거짓인 Prop  

`Check (forall n: nat, n=0 |/ (n=0 -> False) : Prop).`  
사실인 Prop  

모든 인간의 직관은 4개의 룰로 나타낼 수 있다(철학적인거)  

double regation? ligation

루트2가 무리수인가? 귀류법을 써도 되고 안 써도 되는데 쓰면 더 편함. 근데 본질적으로는 같음  

axiom_of_choice  
A가 empty set이어도 trivial하게 A->B가 있음을 증명 가능  

연속적인 (실수, 시간) set을 정의하려면 코시 시퀀스 등을 씀  
martin 교수님 강의  

axiom으로 정의했으니까 axiom을 증명하면 됨  
어차피 증명 불가능한 건 coq에서 증명 불가능  


### 썰 풀이

llvm compiler  

linux - gcc 협력관계  
리눅스용 컴파일 따로 함  

언어마다 메모리 모델이 inconsistant 했는데  
coq로 증명함  
실제로 허교수님 Lab에서 발견하고 JAVA에 곧 패치 예정  

자동차나 비행기 같은 거 미들웨어도  




http://sf.snu.ac.kr/  