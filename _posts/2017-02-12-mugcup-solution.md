---
layout: post
title: 'SIGPL Winter School 2017 3일차 정리'
author: wookje.kwon
date: 2017-02-1 18:12
tags: [boj, mugcup]

---

## [BOJ] 머그컵 풀이 및 소스코드

(문제는 >[여기](https://www.acmicpc.net/contest/view/213)<에서 볼 수 있다)  

태어나서 처음으로 열어본 대회이다. 사실 cms로 어쩌구 저쩌구 해서 열려고 했는데, 귀찮아서 스타트링크(!!!!!)의 도움을 받아 [acmicpc.net](acmicpc.net)에서 개최하게 되었다! (감사합니다) 다만 대회가 조금 아쉬웠던 게, 여러 사정에 의해 출제자가 꽤 많아져서 내가 문제를 일일히 검증하기가 어려웠다(사실 포켓몬 잡느라 귀찮아서 안 했다). 결국 ~~대참사~~ 두 문제에서 오류가 발견되었고 덕분에 슬랙에서 신나게 까였다. ~~(내가 낸 문제 아닌데 ㅠㅠ)~~

### A. 준오는 심술쟁이!!

출제자: [behind06](https://www.acmicpc.net/user/behind06) (나)  

원래 계획에 없던 문제인데, 대회 업로드 실수로 하루 연기되는 바람에 이벤트성으로 뚝딱 만들어낸 문제다. (정답률 16%로 제일 낮아서 뿌듯했다!)  

출제자의 풀이:
```
문제를 읽어보면 알겠지만 전형적인 다이나믹 문제이다.

다만 일부러 생각없이 짰을 때 TLE가 나도록 시간제한을 1초로 설정했다.

제한시간이 1초이기 때문에 단순히 3000 * 3000 * 25 dp를 돌렸다간 시간초과를 받는다.  

==dp[문자열길이][s의 합]== 일 때, 문자열 길이를 p, s 합을 q라고 하면  

==dp[p][q] = k가 0 ~ min(q, 25)일 때의 모든 dp[p-1][q-k]의 합==  

으로 점화식을 세워 해결할 수 있다.  

나머지 연산 과정에서 음수가 나올 수 있으니 주의한다.  
```

출제자의 코드:

```cpp
#include <iostream>
#include <string>

#define min(x, y) ((x)<(y)?(x):(y))

using namespace std;

typedef long long ll;

const int MOD = 1000000007;
const int MAX_LEN = 3000;
const int MAX_SUM = 3000;

int s;
int dp[MAX_LEN + 1][MAX_SUM + 1]; //±ÛÀÚ¼ö, s°³¼ö
string str;

int main()
{
	cin >> s;
	cin >> str;

	int len = str.length();

	/*
    //
    // TLE code
    //
    int len_i, s_j;
	for (len_i = 1; len_i <= MAX_LEN; ++len_i) dp[len_i][0] = 1;
	for (s_j = 0; s_j <= 25; ++s_j) dp[1][s_j] = 1;
	for (len_i = 2; len_i <= MAX_LEN; ++len_i)
	{
		int limit_s = min(len_i * 25, MAX_SUM);
		for (s_j = 1; s_j <= limit_s; ++s_j)
		{
			int limit_k = min(25, s_j);
			for (int k = 0; k <= limit_k; k++)
			{
				dp[len_i][s_j] += dp[len_i - 1][s_j - k];
				dp[len_i][s_j] %= MOD;
			}
		}
	}*/

	int len_i, s_j;
	for (len_i = 1; len_i <= MAX_LEN; ++len_i) dp[len_i][0] = 1;
	for (s_j = 0; s_j <= 25; ++s_j) dp[1][s_j] = 1;
	for (len_i = 2; len_i <= MAX_LEN; ++len_i)
	{
		int limit_s = min(len_i * 25, MAX_SUM);
		for (s_j = 1; s_j <= limit_s; ++s_j)
		{
			ll temp = (dp[len_i - 1][s_j] + dp[len_i][s_j - 1]);
			if (s_j > 25) temp = temp - dp[len_i - 1][s_j - 26] + MOD;
			dp[len_i][s_j] = temp % MOD;
		}
	}

	cout << dp[len][s];

	return 0;
}
```

### B. 배스킨라빈스 31

출제자: [proqk](https://www.acmicpc.net/user/proqk)  

문제 조건과 예제가 잘못 되었던 문제다 (지금은 수정되었다)  

출제자의 풀이:

```
‘다음 승리 전략을 이용’ 해야 하기 때문에 서로 최대한 많이 말하다 우연히 유진이가 이긴 길이가 아닌, 유진이 턴에서 무조건 필승숫자를 부르고 게임을 끝내야 최소 턴의 길이가 된다.

그렇게 생각하면 최소 턴은 (필승 숫자의 개수 * 2)이므로 ==((말하면 지는 수 – 필승숫자 초항) / (한 턴에 말할 수 있는 개수 + 1)+1)*2==로 답을 구할 수 있다.
```

출제자의 코드:

```cpp
#include <stdio.h>
#define nm 10000001

long long int r, q, a, b, sum = nm, n, s;

int main() {
	scanf("%lld", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &a, &b);

		q = (((a - ((a - 1) % (b + 1))) / (b + 1) + 1) * 2);
		if (q < sum) {
			s = i + 1;
			sum = q;
		}
	}
	printf("%lld %lld", s, sum);
	return 0;
}
```

### C. 자원 캐기

출제자: [leehun456](https://www.acmicpc.net/user/leehun456)  

탐색 문제이다! 아니 근데 왜 탐색 문제라고 풀이에 써놓고 다이나믹으로 짰지?

출제자의 풀이:

```
우선 WOOK은 오른쪽이나 아래쪽으로 이동할 수 있으므로, 한 지점에서 이동할 수 있는 경우의 수는 두 가지이다.

아래쪽으로 내려가서 수집할 수 있는 자원의 개수와 오른쪽으로 가서 수집할 수 있는 자원의 개수와 비교하여 큰 값을 현재 칸에 있는 칸에 있는 자원의 개수에 더하여 반환시켜 주는 깊이 우선탐색을 해주면 된다.

총 시간 복잡도는 (N+M-1)^2 이다.
```

출제자의 코드:

```cpp
#include <cstdio>
int N, M, A[310][310],DP[310][310];
int max(int a, int b) {
	return a > b ? a : b;
}
int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &A[i][j]);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (i == 1 && j == 1)
				DP[i][j] = A[i][j];
			else
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) + A[i][j];
		}
	}
	printf("%d\n", DP[N][M]);
	return 0;
}
```

### D. 소수마을

출제자: [wjdtmddnr24](https://www.acmicpc.net/user/wjdtmddnr24)  

분류: 백트래킹, 최단경로 라고 출제자가 써두었다.

출제자의 풀이: 

`먼저, 입력 받은 마을들에 갈수 있는 모든 길들을 찾으며 (최대 4000*4001/2), 거리가 소수이면 인접 리스트에 추가한다. 소수 판정 시간 절약을 위해 1~9000 사이의 모든 소수들을 찾아 놓는 것이 좋다. 이후 다익스트라 알고리즘을 이용하여 최단 경로를 구하면 된다.`

출제자의 코드:

```cpp
#include <stdio.h>
#include <math.h>
#include <functional>
#include <memory.h>
#include <queue>
#include <vector>
#include <map>
using namespace std;
bool isprime[10000];
vector<pair<int, int> > P;
vector<pair<int, int> > V[6000];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
int n;
int visited[4040];
int track[4040] = { 0, };
void findprime(){
	memset(isprime, true, sizeof(isprime));
	isprime[0] = false;
	isprime[1] = false;
	for (int i = 2; i < 10000; i++)
	{
		for (int j = i * 2; j < 10000; j += i)
		{
			isprime[j] = false;
		}
	}
}
int getlength(pair<int, int> a, pair<int, int> b){
	int dx = abs(a.first - b.first);
	int dy = abs(a.second - b.second);
	double len = sqrt((double)dx*dx + dy*dy);
	return (int)len;
}
void findAvailablePath(){
	for (int ii = 0; ii < P.size() - 1; ii++)
	{
		for (int j = ii + 1; j < P.size(); j++)
		{
			if (isprime[getlength(P[ii], P[j])]){
				V[ii].push_back(make_pair(getlength(P[ii], P[j]), j));
				V[j].push_back(make_pair(getlength(P[ii], P[j]), ii));
			}
		}
	}
}
int main(){
	fill(visited, visited + 4040, 987654321);
	getlength(make_pair(1, 2), make_pair(3, 6));
	findprime();

	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	P.push_back(make_pair(a, b));
	P.push_back(make_pair(c, d));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		P.push_back(make_pair(a, b));
	}
	findAvailablePath();
	visited[0] = 0;
	Q.push(make_pair(0, 0));
	while (!Q.empty()){
		pair<int, int> cur = Q.top(); Q.pop();
		for (int i = 0; i < V[cur.second].size(); i++)
		{
			pair<int, int> there = V[cur.second][i];
			if (visited[there.second] > cur.first + there.first){
				visited[there.second] = cur.first + there.first;
				Q.push(make_pair(visited[there.second], there.second));
				track[there.second] = cur.second;
			}
		}
	}
	if (visited[1] == 987654321){
		printf("-1");
	}
	else{
		printf("%d", visited[1]);
	}
	return 0;
}
```

### E. 우물

출제자: [skyoun97](https://www.acmicpc.net/user/skyoun97)  

~~출제자가 소스 잘못 짜놓고 학원으로 도망가서 킹갓 tonyjjw 님이 데이터를 다시 만들었다.~~

출제자의 풀이:

```
먼저, 입력조건에서 “단, 임의의 A마을에서 B마을까지 가는 길의 경로는 한가지이다.” 라는 조건을 보면 입력이 트리 형태인 것을 알 수 있다.

입력이 트리 형태이기 때문에 싸이클이 생기지 않고, A와 B마을로 가는 경로는 무조건 존재하게 된다.

무조건 최적인 경우를 생각해 보면, 임의의 마을에서 인접한 마을의 수가 하나밖에 없을 경우 그 인접한 마을에 공급해주면 된다.

왜냐하면 그 인접한 마을에 공급하면 임의의 마을과 그 인접한 마을과 그 인접한 마을에 인접한 마을까지 채울 수 있기 때문이다.

그렇기 때문에 자식이 없는 리프 노드에서 필요한 우물의 수만큼 부모 노드에 공급해주면, 리프 노드에 공급했을 때 보다 더 많은 우물을 충족 시킬 수 있다.

따라서 아무 노드를 루트 노드로 잡고 DFS로 탐색하면서 자식 노드 중 필요한 우물의 수가 가장 큰 수만큼 부모 노드에 채워주면 된다.

단, 필요한 우물의 수의 최대가 1,000,000이고 마을이 최대 100,000이기 때문에 ans연산 과정에서 오버플로우가 발생할 수 있어서 int 이상의 범위인 자료형으로 연산해주어야 한다.  

시간복잡도 : O(N)
```

~~출제자~~ tonyjjw의 코드:
```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<functional>
#include<stdlib.h>
using namespace std;

#define all(A) (A).begin(), (A).end()
#define II(A) int (A); scanf("%d",&(A));
#define DBG if(1)
#define NDBG if(0)

typedef long long ll;
typedef pair<int,int> pii;

const int MN = 100000 + 100;

vector<int> E[MN];

int N, M;
int req[MN];
ll ans;

void apply(int n, int v){
	req[n] -= v;
	for(int t: E[n]){
		req[t] -= v;
	}
	ans += v;
}

void dfs(int n, int bef){
	int maxv = 0;
	for(int t: E[n]) if(t != bef){
		dfs(t, n);
		maxv = max(maxv, req[t]);
	}
	apply(n, maxv);
}

int main(){
	scanf("%d%d", &N, &M);
	if(N-1 != M){
		for(;;);
	}
	for(int i=0;i<N;i++){
		scanf("%d", &req[i]);
	}
	for(int i=0;i<M;i++){
		II(a)II(b); a--, b--;
		E[a].push_back(b), E[b].push_back(a);
	}
	dfs(0, -1);
	if(req[0] > 0){
		apply(0, req[0]);
	}
	printf("%lld\n", ans);
	return 0;
} 
```

### F. 한조 대기 중

출제자: [behind06](https://www.acmicpc.net/user/behind06)

출제자의 풀이:

```
문제를 잘 읽어보면, 트롤픽을 최대한 많이 고르는 이분매칭 문제임을 알 수 있다.

이분매칭을 알고 있다면 크게 어렵지 않은 문제이다!
```

(출제자는 대충 짜고 자려고 함수 복붙해서 2개씩 만들었다) ~~도대체 출제자가 누구야? 극혐이네~~

```cpp
#include <stdio.h>
#include <vector>
#include <memory.h>

using namespace std;

vector<int> A[501], B[501];
int visitedA[501], visitedB[501];
bool chkA[501], chkB[501];

bool gogoA(int a)
{
	for (auto b : A[a])
	{
		if (chkA[b]) continue;
		chkA[b] = true;
		if (visitedA[b] == -1 || gogoA(visitedA[b]))
		{
			visitedA[b] = a;
			return true;
		}
	}
	return false;
}

bool gogoB(int a)
{
	for (auto b : B[a])
	{
		if (chkB[b]) continue;
		chkB[b] = true;
		if (visitedB[b] == -1 || gogoB(visitedB[b]))
		{
			visitedB[b] = a;
			return true;
		}
	}
	return false;
}

int main()
{
	int N, M, K1, K2;

	scanf("%d %d %d %d", &N, &M, &K1, &K2);
	for (int i = 0; i < K1; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b); --a, --b;
		A[a].push_back(b);
	}
	for (int i = 0; i < K2; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b); --a, --b;
		B[a].push_back(b);
	}

	int res1 = 0, res2 = 0;
	memset(visitedA, -1, sizeof(visitedA));
	memset(visitedB, -1, sizeof(visitedB));
	for (int i = 0; i < N; ++i)
	{
		memset(chkA, 0, sizeof(chkA));
		memset(chkB, 0, sizeof(chkB));
		if (gogoA(i)) ++res1;
		if (gogoB(i)) ++res2;
	}

	if (res1 < res2) printf("네 다음 힐딱이");
	else printf("그만 알아보자");

	return 0;
}
```




### G. 놀이기구1

출제자: [tonyjjw](https://www.acmicpc.net/user/tonyjjw)  

고마워요 토니!

출제자의 풀이:

```
아이들의 키가 자라기만 하고 줄어들지는 않기 때문에, 주어지는 (i, j, k) 쌍에 대해 한번 놀이기구를 타기 시작하면 계속 놀이기구를 탈 수 있게 됩니다.

즉 각 질문에 대해, 최초로 조건이 만족되는 시점이 언제인지를 구하게 되면 문제를 해결할 수 있습니다. 이를 나이브하게 하면 O(QK)의 시간이 걸립니다.

하지만 Parallel binary search(http://codeforces.com/blog/entry/45578)를 사용하면 O((Q + K) log K)의 시간복잡도로 문제를 해결할 수 있습니다.
```

출제자의 코드:

```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<functional>
#include<stdlib.h>
#include<queue>
using namespace std;

#define all(A) (A).begin(), (A).end()
#define II(A) int (A); scanf("%d",&(A));
#define DBG if(1)
#define NDBG if(0)

typedef long long ll;
typedef pair<int,int> pii;

const int MN = 200000 + 10;

int N, M, K, Q;
int lim[MN];
int who[MN];
int height[MN];
int satisfied[MN];

struct QUERY{
	int i, j, k;
}query[MN];

int half(int q){
	return (lim[query[q].k] - height[query[q].i] - height[query[q].j] + 1) / 2;
}

struct PQ{
	int q, v;
	PQ(){}
	PQ(int q, int v):q(q),v(v){}
	bool operator <(PQ A)const{
		return v > A.v;
	}
};

priority_queue<PQ> pq[MN];
int ans[MN];

int main(){
	scanf("%d%d%d%d", &N, &M, &K, &Q);
	for(int i=0;i<M;i++){
		scanf("%d", &lim[i]);
	}
	for(int i=0;i<K;i++){
		scanf("%d", &who[i]); who[i]--;
	}
	for(int i=0;i<Q;i++){
		scanf("%d%d%d", &query[i].i, &query[i].j, &query[i].k);
		query[i].i--, query[i].j--, query[i].k--;
		pq[query[i].i].emplace(i, half(i));
		pq[query[i].j].emplace(i, half(i));
	}
	for(int i=0;i<K;i++){
		if(i > 0){
			ans[i] = ans[i-1];
		}
		int n = who[i];
		height[n]++;
		while(!pq[n].empty()){
			auto info = pq[n].top();
			if(height[n] < info.v){
				break;
			}
			pq[n].pop();
			if(half(info.q) <= 0){
				if(!satisfied[info.q]){
					satisfied[info.q] = 1;
					ans[i]++;
				}
			}
			else{
				pq[query[info.q].i].emplace(info.q, height[query[info.q].i] + half(info.q));
				pq[query[info.q].j].emplace(info.q, height[query[info.q].j] + half(info.q));
			}
		}
		printf("%d\n", ans[i]);
	}
	return 0;
} 
```

### H. 놀이기구2

출제자: [tonyjjw](https://www.acmicpc.net/user/tonyjjw)  

고마워요 토니!

출제자의 풀이:

```
앞선 문제와의 차이점은 Parallel binary serach를 사용할 수 없다는 것입니다.

때문에 이 문제를 풀기 위해서는 첫번째 날부터 K번째 날까지 시뮬레이션을 하면서, 각 날마다 Q개의 질문 중 몇개가 처음으로 만족되었는지 알아내야 합니다!

역시 나이브하게 하면 O(QK)의 시간으로 해결 가능하지만, 시간제한상 충분치 않습니다.

O(QK)가 의미하는 바는, 각 질문에 대해 K번씩 만족되었는지 검사를 한다는 뜻이죠. 이제부터 쓸데없는 검사 횟수를 줄이도록 해보겠습니다.

아이 i의 키를 Ai라고 한다면, 임의의 질문은 Ai + Aj >= C (C는 상수) 라는 부등식으로 변환됩니다.

그리고 여기서 중요한 사실은 Ai, Aj중 하나는 C/2 이상이어야 부등식을 만족시킬 수 있다는 것입니다.

즉 Ai, Aj 모두 C/2 미만일 경우 그 질문은 검사를 할 필요가 없게 됩니다.

따라서 각 질문에 대해 log2C 번 정도의 검사만으로도 충분하다는 것을 알 수 있습니다.

구체적인 구현은 우선순위 큐(Priority queue) 등을 이용해 구현할 수 있으며, 시간복잡도는 O(Q log2키제한 + K)입니다.
```

출제자의 코드:

```cpp

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<functional>
#include<stdlib.h>
#include<queue>
using namespace std;

#define all(A) (A).begin(), (A).end()
#define II(A) int (A); scanf("%d",&(A));
#define DBG if(1)
#define NDBG if(0)

typedef long long ll;
typedef pair<int,int> pii;

const int MN = 200000 + 10;

int N, M, K, Q;
int lim[MN];
int who[MN];
int height[MN];
int satisfied[MN];

struct QUERY{
	int i, j, k;
}query[MN];

int half(int q){
	return (lim[query[q].k] - height[query[q].i] - height[query[q].j] + 1) / 2;
}

struct PQ{
	int q, v;
	PQ(){}
	PQ(int q, int v):q(q),v(v){}
	bool operator <(PQ A)const{
		return v > A.v;
	}
};

priority_queue<PQ> pq[MN];
int ans[MN];

int main(){
	scanf("%d%d%d%d", &N, &M, &K, &Q);
	for(int i=0;i<M;i++){
		scanf("%d", &lim[i]);
	}
	for(int i=0;i<K;i++){
		scanf("%d", &who[i]); who[i]--;
	}
	for(int i=0;i<Q;i++){
		scanf("%d%d%d", &query[i].i, &query[i].j, &query[i].k);
		query[i].i--, query[i].j--, query[i].k--;
		pq[query[i].i].emplace(i, half(i));
		pq[query[i].j].emplace(i, half(i));
	}
	for(int i=0;i<K;i++){
		if(i > 0){
			ans[i] = ans[i-1];
		}
		int n = who[i];
		height[n]++;
		if(i > 1 && ans[i-1] > ans[i-2]){
			height[n]++;
		}
		while(!pq[n].empty()){
			auto info = pq[n].top();
			if(height[n] < info.v){
				break;
			}
			pq[n].pop();
			if(half(info.q) <= 0){
				if(!satisfied[info.q]){
					satisfied[info.q] = 1;
					ans[i]++;
				}
			}
			else{
				pq[query[info.q].i].emplace(info.q, height[query[info.q].i] + half(info.q));
				pq[query[info.q].j].emplace(info.q, height[query[info.q].j] + half(info.q));
			}
		}
		printf("%d\n", ans[i]);
	}
	return 0;
} 
```