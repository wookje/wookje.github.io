---
layout: post
title: '[codeforces] #403 B. The Meeting Place Cannot Be Changed'
author: wookje.kwon
comments: true
date: 2017-03-15 09:19
tags: [boj, binary-search]

---

[#403 B. The Meeting Place Cannot Be Changed](http://codeforces.com/contest/782/problem/B)

## 풀이

코포 문제는 처음 풀이한다! (두근두근)

이분 탐색을 돌리면 쉽게 해결할 수 있다.

만나는 시간을 mid로 두면, n*log(최대차이)이므로 제한시간에 맞게 돌릴 수 있다.

각각의 좌표 x[i]를 돌면서 mid에 갈 수 있는 max_left, min_right를 구한다.

max_left <= min_right면 mid에 만날 수 있다.

왜 그런지는 그림판에 대충 선 몇 개 그려보면 직관적으로 이해 될 것이다. (아마?) 

AC 받긴 했는데 저렇게 짜도 실수 오차 안 나는지는 모르겠다 (...)

## 코드

```cpp
#include <stdio.h>

typedef double dbl;

const int n_ = 6e4 + 10;
int n, x[n_], v[n_];

dbl max(dbl a, dbl b) { return a > b ? a : b; }
dbl min(dbl a, dbl b) { return a < b ? a : b; }

int main() {
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &x[i]);
	for (i = 0; i < n; i++) scanf("%d", &v[i]);

	bool ac;
	dbl l = 0, r = 1e9, ans;
	while (l <= r) {
		dbl m = (l + r) / 2;
		dbl max_l = 0, min_r = 1e9;
		for (i = 0; i < n; i++) {
			max_l = max(max_l, x[i] - v[i] * m);
			min_r = min(min_r, x[i] + v[i] * m);
		}
		if (max_l <= min_r) r = m - 0.00000001, ans = m;
		else l = m + 0.00000001;
	}
	printf("%lf", ans);

	return 0;
}
```
