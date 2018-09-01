---
layout: post
title: '[BOJ] 14971 : A Garden With Ponds'
author: wookje.kwon
comments: true
date: 2018-06-30 17:34
tags: [boj, acm-icpc, naive]

---

[14971 : A Garden With Ponds](https://www.acmicpc.net/problem/14971)  

## 풀이

코드 개더러워...

## 코드

```cpp
#include <cstdio>
#include <algorithm>
#define REP(k,l,r) for(int k=(l);k<(r);k++)
using namespace std;

int n, m, a[12][12];
int main() {
    while (1) {
        scanf("%d %d", &n ,&m);
        if (!n && !m) return 0;
        REP(i,1,n+1) REP(j,1,m+1) scanf("%d", &a[i][j]);
        int res = 0;
        REP(i,1,n+1) REP(j,1,m+1) {
            REP(x,i+2,n+1) REP(y,j+2,m+1) {
                int mo = 1e9;
                REP(k,i,x+1) mo = min(mo, min(a[k][j], a[k][y]));
                REP(k,j,y+1) mo = min(mo, min(a[i][k], a[x][k]));
                int mi = -1, sum = 0;
                REP(u,i+1,x) REP(v,j+1,y) {
                    mi = max(mi, a[u][v]);
                    sum += mo - a[u][v];
                }
                if (mi < mo) res = max(res, sum);
            }
        }
        printf("%d\n", res);
    }

    return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge, C, C++, 씨, 씨쁠쁠, algorithm, 알고리즘, 자료구조, 문제, 문제 풀이, 풀이
