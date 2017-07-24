---
layout: post
title: '[BOJ] 2150번: Strongly Connected Component'
author: wookje.kwon
comments: true
date: 2017-04-17 11:43
tags: [boj, scc, graph, dfs]

---

[2150 : Strongly Connected Component](https://www.acmicpc.net/problem/2150)

## 풀이

scc를 구현하자!

다른 블로그에 좋은 scc 설명이 많으니까 나는 구현만 해야겠다

원래 stl stack 써서 짰는데

메모리 많이 먹길래 기분 나빠서(?) 배열로 바꿨다.

처음 코드가 타잔, 다음 코드가 코사라주이다. 

## 코드

타잔

```cpp
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
const int v_ = 1e4 + 1;

int v, e, cnt, pos, scc[v_], chk[v_], stk[v_];
vi gph[v_];
vector<vi> res;

int dfs(int now) {
	chk[now] = ++cnt;
	int ret = chk[now];
	stk[pos++] = now;
	for (int nxt : gph[now]) {
		if (!chk[nxt]) ret = min(ret, dfs(nxt));
		else if (!scc[nxt]) ret = min(ret, chk[nxt]);
	}

	if (ret != chk[now]) return ret;

	res.push_back(vi());
	while (1) {
		int top = stk[--pos];
		scc[top] = res.size();
		res[scc[top] - 1].push_back(top);
		if (top == now) break;
	}

	return ret;
}

int main() {
	int i;
	
	scanf("%d %d", &v, &e);
	for (i = 1; i <= e; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		gph[a].push_back(b);
	}

	for (i = 1; i <= v; i++)
		if (!chk[i]) dfs(i);

	for(auto &i : res) sort(i.begin(), i.end());
	sort(res.begin(), res.end(), [](const vi &i, const vi &j) { return i[0] < j[0]; });

	printf("%d\n", res.size());
	for (auto &i : res) {
		for (auto j : i) printf("%d ", j);
		puts("-1");
	}

	return 0;
}
```

코사라주

```cpp
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;
const int v_ = 1e4 + 1;

int v, e, cnt, pos, stk[v_];
bool vst[v_];
vi gp1[v_], gp2[v_];
vector<vi> res;

void dfs(int now) {
	vst[now] = true;
	for (int nxt : gp1[now]) if (!vst[nxt])
		dfs(nxt);
	stk[pos++] = now;
}

void scc(int now) {
	vst[now] = true;
	res[cnt].push_back(now);
	for (int nxt : gp2[now]) if (!vst[nxt])
		scc(nxt);
}

int main() {
	int i;
	
	scanf("%d %d", &v, &e);
	for (i = 1; i <= e; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		gp1[a].push_back(b);
		gp2[b].push_back(a);
	}

	for (i = 1; i <= v; i++)
		if (!vst[i]) dfs(i);
	memset(vst, 0, sizeof(vst));
	while (pos) {
		int top = stk[--pos];
		if (vst[top]) continue;
		res.push_back(vi());
		scc(top);
		cnt++;
	}

	for (i = 0; i < cnt; i++) sort(res[i].begin(), res[i].end());
	sort(res.begin(), res.end(), [](const vi &i, const vi &j) { return i[0] < j[0]; });
	
	printf("%d\n", res.size());
	for (auto &i : res) {
		for (auto j : i) printf("%d ", j);
		puts("-1");
	}

	return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge