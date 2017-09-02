---
layout: post
title: '[BOJ] 6191 : Cows on Skates'
author: wookje.kwon
comments: true
date: 2017-09-03 00:37
tags: [boj, usaco, bfs]

---

[6191 : Cows on Skates](https://www.acmicpc.net/problem/6191)

## 풀이

(1,1)~(r,c)까지의 경로를 찾아주자!

왜 이게 usaco gold 문제인지는 모르겠다 ㅋㅋㅋ

## 코드

```cpp
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

const int dx[] = { 0,0,-1,1 }, dy[] = { -1,1,0,0 };
struct ABC { int x, y; };
int n, m;
char a[123][123];
ABC chk[123][123];
queue<ABC> que;

void f(int x, int y) {
	if (x != 1 || y != 1) f(chk[x][y].x, chk[x][y].y);
	printf("%d %d\n", x, y);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);

	chk[1][1].x = chk[1][1].y = 0;
	que.push({ 1,1 });
	while (!que.empty()) {
		ABC now = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i], ny = now.y + dy[i];
			if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
			if (!chk[nx][ny].x && !chk[nx][ny].y && a[nx][ny] == '.') {
				que.push({ nx,ny });
				chk[nx][ny].x = now.x, chk[nx][ny].y = now.y;
			}
		}
	}

	f(n, m);

	return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge