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

2026-08-10 23:42

# 1 Building Abstractions with Procedures

The acts of the mind, wherein it exerts its power over simple ideas, are chiefly these three:
- Combining several simple ideas into one compound one, and thus all complex ideas are made.  
- Bringing two ideas, whether simple or complex, together, and setting them by one another so as to take a view of them at once, without uniting them into one, by which it gets all its ideas of relations.
- Separating them from all other ideas that accompany them in their real existence: this is called abstraction, and thus all its general ideas are made.  
— John Locke, _An Essay Concerning Human Understanding_ (1690)  

We are about to study the idea of a computational process. Computational processes are abstract beings that inhabit computers. As they evolve, **processes manipulate other abstract things called data**. The evolution of a process is directed by a **pattern of rules called a program**. People create programs to direct processes.  
(혼신의 힘을 다해 적은 도입부가 매우 인상적이다.)  

... A computational process, in a correctly working computer, executes
programs precisely and accurately. ... novice programmers must learn to understand and to anticipate the consequences of their conjuring. ...

... Real-world programming, however, requires care, expertise, and wisdom. ...

Master software engineers have the ability to organize programs so that they can be reasonably sure that the resulting processes will **perform the tasks intended**.
- **They can visualize** the behavior of their systems in advance.
- **They know how to structure** programs so that unanticipated problems do not lead to catastrophic consequences.
- **They can debug** their programs when problems do arise.  

Well-designed computational systems, like well-designed automobiles or nuclear reactors, are designed in a **modular manner**, so that the parts can be constructed, replaced, and debugged separately.  

## 1.1 The Elements of Programming

A powerful programming language is more than just a means for instructing a computer to perform tasks. The **language also serves as a framework within which we organize our ideas** about processes. Thus, when we describe a language, we should pay particular attention to the means that the language provides for combining simple ideas to form more complex ideas. Every powerful language has three mechanisms for accomplishing this:  
- **Primitive expressions**, which represent the simplest entities the
language is concerned with
- **Means of combination**, by which compound elements are built
from simpler ones
- **Means of abstraction**, by which compound elements can be named
and manipulated as units.  
(여기서 1과, 2와, 3 이상인 것의 차이를 느낄 수 있다. 도입부에서 제시한 원자 단위, 복합 단위, 추상 단위가 곧바로 예시로 설명되었고 나에게 인상적이다. 예시가 하나 뿐인데 추상화부터 하는 행동을 더욱 통찰력 있게 비난할 수 있게 되었다. 언어가 관념을 담는 프레임워크라는 말은 프로그래밍의 바깥에서도 생각해볼만 하다.)  

In programming, we deal with two kinds of elements: procedures and data. (Later we will discover that they are really not so distinct.) Informally, **data is "stuff" that we want to manipulate**, and **procedures are descriptions of the rules** for manipulating the data. Thus, any powerful programming language should be able to describe primitive data and primitive procedures and should have methods for combining and abstracting procedures and data.  

