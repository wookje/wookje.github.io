---
layout: post
title: '[BOJ] 4586 : Image Compression'
author: wookje.kwon
comments: true
date: 2017-09-03 18:12
tags: [boj, acm-icpc, divide-and-conquer]

---

[4586 : Image Compression](https://www.acmicpc.net/problem/4586)

## 풀이

흑흑 문제를 잘못 읽어서 한 번 틀렸다 ㅠㅠ

네 조각씩 나눠서 분할정복을 하면 된다.

제한이 크지 않으므로 나이브하게 사각형을 다 돌아보면 된다.

룰루

## 코드

```cpp
#include <stdio.h>
#define y1 fuck
typedef double db;

int n, t;
char a[66][66];

void go(int x1, int y1, int x2, int y2) {
	if (x1 == x2 && y1 == y2) return;

	int siz = (x2 - x1 + 1) * (y2 - y1 + 1), cnt = 0;
	for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) cnt += a[i][j];
	if ((db)cnt / siz * 100.0 >= t) {
		for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) a[i][j] = 1;
		return;
	}
	if ((db)(siz - cnt) / siz * 100.0 >= t) {
		for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) a[i][j] = 0;
		return;
	}

	go(x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2);
	go(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);
	go((x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2);
	go((x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1, x2, y2);
}

int main() {
	int wow = 1;
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		scanf("%d", &t);

		for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] -= '0';

		go(1, 1, n, n);

		printf("Image %d:\n", wow++);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) printf("%d", a[i][j]);
			printf("\n");
		}
	}

	return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge