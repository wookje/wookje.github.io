---
layout: post
title: '[BOJ] 1011 : Fly me to the Alpha Centauri'
author: wookje.kwon
comments: true
date: 2018-03-25 19:20
tags: [boj, math]

---

[1011 : Fly me to the Alpha Centauri](https://www.acmicpc.net/problem/1011)

## 풀이

`1 2 3 ... i-1 i i-1 ... 3 2 1` 이렇게 삼각형으로 증가/감소하는 수열 s를 생각해보자.

s의 원소들의 합은 `i^2`이다.

`dist = end - start`일 때, dist가 음수가 되지 않는 가장 큰 i를 골라서 `dist - i^2`를 해주자.

남은 거리는 1와 i 사이에 숫자를 잘 골라서 채워넣을 수 있다.

## 코드

```cpp
#include <stdio.h>
#include <math.h>

int main() {
	int tc;
	for (scanf("%d", &tc); tc; tc--) {
		int s, e;
		scanf("%d %d", &s, &e);

		long long i = 1, d = e - s;
		while (i*i <= d) i++; i--;
		d = ceil((double)(d-i*i)/i);

		printf("%lld\n", i+i-1+d);
	}
	return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge, C, C++, 씨, 씨쁠쁠, JAVA, algorithm, 자바, 알고리즘, 자료구조, 문제, 문제 풀이, 풀이
