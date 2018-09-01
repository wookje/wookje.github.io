---
layout: post
title: '[BOJ] 10547 : STUDENTSKO'
author: wookje.kwon
comments: true
date: 2018-04-17 09:49
tags: [boj, coci, naive]

---

## COCI 2014/2015 Contest #2 3번

[10547 : STUDENTSKO](https://www.acmicpc.net/problem/10547)  

## 풀이

한 팀에 들어가야 하는 학생들에게 같은 그룹 넘버를 부여하자  

그냥 부여하는 건 아니고 먼저 뽑혀야하는 팀부터 오름차순으로 부여하자

그리고 **가장 긴 단조증가하는 수열의 길이**를 구하자.

## 코드

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n, k, len, a[5005], lis[5005];
pair<int, int> p[5005];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), p[i].first = a[i];
    sort(a, a + n);

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        if (a[i] == p[j].first) p[j].second = i / k + 1;
    
    for (int i = 0; i < n; i++) {
        auto a = upper_bound(lis, lis + len, p[i].second);
        if (!(*a)) len++;
        *a = p[i].second;
    }

    printf("%d", n - len);
    
    return 0;
}
```

### 아무말  
백준, 백준 온라인 저지, BOJ, Baekjoon Online Judge, C, C++, 씨, 씨쁠쁠, algorithm, 알고리즘, 자료구조, 문제, 문제 풀이, 풀이
