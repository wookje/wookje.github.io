---
layout: post
title: '[BOJ] 14969 : Taro`s Shopping'
author: wookje.kwon
comments: true
date: 2018-06-30 17:33
tags: [boj, acm-icpc, naive]

---

[14969 : Taro's Shopping](https://www.acmicpc.net/problem/14969)  

## 풀이

별빛이 내린다

## 코드

```cpp
#include <cstdio>

int n, m, a[1001];
int main() {
    while (1) {
        scanf("%d %d", &n, &m);
        if (!n && !m) {
            return 0;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }

        int res = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int s = a[i] + a[j];
                if (s <= m && s > res) res = s;
            }
        }
        if (res != -1) {
            printf("%d\n", res);
        }
        else {
            printf("NONE\n");
        }
    }

    return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge, C, C++, 씨, 씨쁠쁠, JAVA, algorithm, 자바, 알고리즘, 자료구조, 문제, 문제 풀이, 풀이
