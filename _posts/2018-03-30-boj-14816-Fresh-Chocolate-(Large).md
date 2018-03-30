---
layout: post
title: '[BOJ] 14816 : Fresh Chocolate (Large)'
author: wookje.kwon
comments: true
date: 2018-03-30 17:04
tags: [boj, google-code-jam, math]

---

[14816 : Fresh Chocolate (Large)](https://www.acmicpc.net/problem/14816)

## 풀이

뭔가 제너럴한 규칙을 찾으려고 했는데 잘 모르겠당

p가 2~4밖에 안 되므로 그냥 경우를 나눠서 잘 따져주자.

## 코드

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int tc, t, n, p, c[5];
	scanf("%d", &tc);
	for (t = 1; t <= tc; t++) {
		c[0] = c[1] = c[2] = c[3] = 0;
		
		scanf("%d %d", &n, &p);
		for (int i = 0, a; i < n; i++) scanf("%d", &a), c[a % p]++;
		
		int r = c[0];
		if (p == 2) {
			r += (c[1] + 1) / 2;
		}
		else if (p == 3) {
			if (c[1] > c[2]) swap(c[1], c[2]);
			r += c[1] + (c[2] - c[1] + 2) / 3;
		}
		else {
			if (c[1] > c[3]) swap(c[1], c[3]);
			if (c[2] % 2 && c[3] - c[1] != 1) r++, c[3] -= 2;
			r += c[1] + c[2] / 2 + (c[3] - c[1] + 3) / 4;
		}

		printf("Case #%d: %d\n", t, r);
	}

	return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge, C, C++, 씨, 씨쁠쁠, JAVA, algorithm, 자바, 알고리즘, 자료구조, 문제, 문제 풀이, 풀이
