---  
layout: post  
title: '추상화'  
author: wookje.kwon  
comments: true  
date: 2026-08-10 23:33  
tags: [chat]  
  
---  

[Structure and Interpretation of Computer Programs](https://web.mit.edu/6.001/6.037/sicp.pdf)에서 문장들을 발췌하여 기록할 것이다. 내가 이 책을 읽는 목적의 51%는 커리어, 49%는 철학에 관한 것으로, 구체적으로는 추상화, 시스템, 컴퓨터과학에 관한 통찰을 얻어가는 것이다. 따라서 내 독서 목적 하에서 인상 깊은 문장들이 발췌될 것이다. 정확히 발췌만 하지는 않고, 내가 속독하기 편하도록 약간의 재배열을 할 수도 있다. 볼드도 추가할 것이다. 책이 두껍고, 내가 바쁘고, 내 관심사도 자주 바뀌기 때문에 언제 독서가 끝날지는 알 수 없다.  

오랜만에 전공 서적 읽으려니 재밌기도 하고, 어릴 때 이런 것도 안 읽고 뭐했나 싶기도 하고, 어릴 땐 영어 더 못해서 어차피 못 읽었을 것 같기도 하고 그르넹!  

---

_2026-08-10 23:42_

# 1 Building Abstractions with Procedures

The acts of the mind, wherein it exerts its power over simple ideas, are chiefly these three:
- Combining several simple ideas into one compound **one**, and thus all complex ideas are made.  
- Bringing **two** ideas, whether simple or complex, together, and setting them by one another so as to take a view of them at once, without uniting them into one, by which it gets all its ideas of relations.
- Separating them from all other ideas that accompany them in their real existence: this is called **abstraction**, and thus all its general ideas are made.  
— John Locke, _An Essay Concerning Human Understanding_ (1690)  

We are about to study the idea of a computational process. Computational processes are abstract beings that inhabit computers. As they evolve, **processes manipulate other abstract things called data**. The evolution of a process is directed by a **pattern of rules called a program**. People create programs to direct processes.  

> 여기까지, 혼신의 힘을 다해 적은 도입부가 매우 인상적이다.  

... A computational process, in a correctly working computer, executes
programs precisely and accurately. ... novice **programmers must learn to understand and to anticipate the consequences of their conjuring**. ...

... Real-world programming, however, requires care, expertise, and wisdom. ...

Master **software engineers have the ability to** organize programs so that they can be reasonably sure that the resulting processes will **perform the tasks intended**.
- They can **visualize** the behavior of their systems in advance.
- They know how to **structure** programs so that unanticipated problems do not lead to catastrophic consequences.
- They can **debug** their programs when problems do arise.  

Well-designed computational systems, like well-designed automobiles or nuclear reactors, are designed in a **modular manner**, so that the parts can be constructed, replaced, and debugged separately.  

> 구구절절 맞는 말. 읽으면 120% 공감할 수 있지만, 내가 쓴다면 이 수준으로 정밀하고 자신감 있게 설명할 자신이 없다. 저명한 시스템 박사와 날라리 학사의 격의 차이를 여실히 느꼈다.  

## 1.1 The Elements of Programming

A powerful programming language is more than just a means for instructing a computer to perform tasks. The **language also serves as a framework within which we organize our ideas** about processes. Thus, when we describe a language, we should pay particular attention to the means that the language provides for combining simple ideas to form more complex ideas. Every powerful language has three mechanisms for accomplishing this:  
- **Primitive expressions**, which represent the simplest entities the
language is concerned with
- **Means of combination**, by which compound elements are built
from simpler ones
- **Means of abstraction**, by which compound elements can be named
and manipulated as units.  

> 1과, 2와, 3 이상인 것의 차이를 느낄 수 있다. 도입부에서 제시한 원자 단위, 복합 단위, 추상 단위가 예시를 들어 설명되었고 나에게 인상적이다. 일상 생활에서 예시가 하나 뿐임에도 추상화부터 하려고 하는 시도를 마주했을 때, 그러한 시도를 더욱 통찰력 있게 비난할 수 있게 되었다. 언어가 관념을 담는 프레임워크라는 말은 언어철학과도 맞닿아 있다.  

In programming, we deal with two kinds of elements: **procedures** and **data**. (Later we will discover that they are really not so distinct.) Informally, data is "stuff" that we want to manipulate, and procedures are descriptions of the rules for manipulating the data. Thus, any powerful programming language should be able to describe primitive data and primitive procedures and should have methods for combining and abstracting procedures and data.  

> 프로그래밍은 두 가지 요소를 다룬다: 데이터, 데이터를 조작하는 규칙의 모음  

_2026-08-15 14:24_

### 1.1.1 Expressions

...  

No ambiguity can arise, ...  

There is no limit (in principle) to the depth of such nesting and to the overall complexity ...  

> 예를 들어, 구글 클라우드에 사진을 드래그앤드랍 했을 때 일어나는 기저의 모든 사건에는 모호함이 없으며, 컴퓨팅에 관해 100년간 쌓아올린 인류의 첨예한 지성은 '딸-깍'으로 추상화 된다.  

> 까지가 이상적인 세계이고 현실은 undefined behavior로 가득가득이다!  

### 1.1.2 Naming and the Environment

A critical aspect of a programming language is the means it provides for using **names** to refer to computational objects. ...

...

... In general, computational objects may have very complex structures, and it would be **extremely inconvenient to have to remember and repeat their details each time** we want to use them. Indeed, **complex programs are constructed by building, step by step, computational objects of increasing complexity**. ...

> '이름'이 부여된다는 것에는 많은 함의가 있다. 관념에 부여되는 이름은 1) 도입이거나 2) 층위의 상승이어야 하며 3) 동어 반복이 되어서는 안 된다. 프로그램의 고도화는 반드시 무언가의 '편의'를 동반하고, 동반해야 한다. 이때 공학자라면 트레이드 오프에 관해 생각할 수밖에 없는데 일단 넘어가겠다.  

### 1.1.3 Evaluating Combinations  

...

Even this simple rule illustrates some important points about processes in general. ... Thus, the evaluation rule is recursive in nature; that is, it includes, as one of its steps, the need to invoke the rule itself.

...  

> 재귀의 아름다움의 일부에 대한 흔한 설명  

_2026-08-15 22:22_

### 1.1.4 Compound Procedures

We have identified in Lisp some of the elements that must appear in any powerful programming language:
- Numbers and arithmetic operations are primitive data and procedures.
- Nesting of combinations provides a means of combining operations.
- Definitions that associate names with values provide a limited means of abstraction.

...

> 이름과 value를 연결 짓는 것은 제한된(부분적인?) 추상화 수단을 제공한다. 나에게 value는 '값'으로도 읽히고 '가치'로도 읽힌다. 근데 숫자가 왜 프로시저인 거지...  

> 매우 유능한 친구들의 지성을 빌려 20분만에 이해했다. PL적 사고를 하면 (PL이라는 이름으로 추상화된 맥락의 모음을 로딩한다는 뜻) 금방 이해할 수 있는데 너무 먼 발치에서 생각했다. 근데 데이터랑 프로시저가 같다고 주장하는 건 뭔가 현실에 굴복한 느낌이라 뭔가 따지고 싶다.  

