---
layout: post
title: '[codeforces] #403 div1 A (div2 C)'
author: wookje.kwon
comments: true
date: 2017-03-15 15:00
tags: [boj, dfs]

---

[#403 div1 A. Andryusha and Colored Balloons](http://codeforces.com/contest/781/problem/A)

## 풀이

이전 노드의 색, 이번 노드의 색에 대한 정보를 가지고 dfs를 돌리면 해결할 수 있다.  

추가로, (가장 큰 차수)+1만 가지고 최소로 색칠할 수 있다.

## 코드

```cpp
#include <bits/stdc++.h>
using namespace std;

const int n_ = 2e5 + 10;

int n, ans, col[n_];
vector<int> gph[n_];

void dfs(int prv, int cur) {
	int i = 1;
	for (auto nxt : gph[cur]) {
		if (col[nxt]) continue;
		while (col[prv] == i || col[cur] == i) i++;
		col[nxt] = i++;
		ans = max(ans, i);
		dfs(cur, nxt);
	}
}

int main() {
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		gph[a].push_back(b);
		gph[b].push_back(a);
	}

	col[1] = 1;
	dfs(0, 1);

	printf("%d\n", ans - 1);
	for (i = 1; i <= n; i++) printf("%d ", col[i]);

	return 0;
}
```
