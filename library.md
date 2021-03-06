---
layout: page
title: 라이브러리
permalink: /library/
sitemap:
  priority: 0.7
---

(업데이트 중)

알고리즘/자료구조 복붙용 라이브러리

코드에 오류가 있을 가능성 아주 높습니다

수정 및 추가 제안, 오류 제보 환영합니다

wookje.happy@gmail.com 또는 개인적으로 연락 주세요

## include 인클루드

```cpp
// http://wookje.dance/library/
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
#include<stack>
#include<string>
#include<list>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<bitset>
#include<tuple>
#include<functional>
#include<utility>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<cassert>
#define y1 fuckfuckfuck
#define fst first
#define snd second
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v)) (v).begin(), (v).end()
#define PQ priority_queue
using namespace std;
using ll = long long;
using ull = unsigned long long;
using dbl = double;
using ldb = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b) {if(!a||!b)return 0;return a*(b/gcd(a,b));}
pll ext_gcd(ll a, ll b){
    if (b == 0) return { 1,0 };
    auto t = ext_gcd(b, a%b);
    return { t.second,t.first-(a/b)*t.second };
}
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
struct point {
    int x, y;
    bool operator <(point a)const {
        return x == a.x ? y < a.y : x < a.x;
    }
};

const int powmod = 1e9+7;
ll fast_pow(ll base, ll exp) {
    if (base == 1) return 1;
    ll ans = 1;
    while (exp) {
        if (exp & 1) {
            ans = (ans * base)%powmod;
        }
        base = (base*base)%powmod;
        exp >>= 1;
    }
    return ans;
}


int main() {
    //cin.tie(0); ios_base::sync_with_stdio(0);



    return 0;
}

```

## Tree 트리

### Fenwick Tree 펜윅 트리

point update, range query

`qry(h): 1~h까지의 합`  
`upd(h, v): h에 v만큼 더함`  

```cpp
typedef long long ll;
const int MAXN = 1e6 + 1;

int n;
ll tree[MAXN];

inline void upd(int h, ll v) {
    for (int i = h; i <= n; i += i&-i) tree[i] += v;
}

ll qry(int h) {
    ll ret = 0;
    for (int i = h; i; i -= i&-i) ret += tree[i];
    return ret;
}
```

range update, point query

`qry(h): h의 누적합`  
`upd(s, e, x): [s, e]에 x만큼 더함`  

```cpp
typedef long long ll;
const int MAXN = 1e6 + 1;

int n;
ll tree[MAXN];

inline void upd(int s, int e, ll x) {
    if (s <= e) {
        for (int i = s; i <= n; i += i&-i) tree[i] += x;
        for (int i = e+1; i <= n; i += i&-i) tree[i] -= x;
    }
    else {
        for (int i = 1; i <= n; i += i&-i) tree[i] += x;
        for (int i = s+1; i <= n; i += i&-i) tree[i] -= x;
        for (int i = e; i <= n; i += i&-i) tree[i] += x;
    }
}

ll qry(int h) {
    ll ret = 0;
    for (int i = h; i; i -= i&-i) ret += bit[i];
    return ret;
}
```

### Non Recursive Segment Tree 비재귀 세그먼트 트리

sum, point update, range query

```cpp
typedef long long ll;

const int MAXN = (1 << 20);
ll tree[MAXN*2+10];

void update(int i, ll v) {
    i += MAXN;
    while (i) {
        tree[i] += v;
        i /= 2;
    }
}

ll query(int s, int e) {
    ll sum = 0;
    s += MAXN; e += MAXN;
    while (s <= e) {
        if (s % 2 == 1) sum += tree[s];
        if (e % 2 == 0) sum += tree[e];
        s = (s + 1) / 2;
        e = (e - 1) / 2;
    }
    return sum;
}
```

min(max), point update, range query

```cpp
TODO
```

### Lazy Propagation 레이지

```cpp
TODO
```

### Merge Sort Tree 머지 소트 트리

```cpp
TODO
```

### PST Persistent Segment Tree 피에스티

```cpp
const int MAXN = 1<<17;
int root[MAXN];
struct PST {
    int cnt = 1, v[MAXN*17], l[MAXN*17], r[MAXN*17];
    // init(s,e) : 다음 트리들을 만드는 데 베이스가 될 트리를 만든다. 이 트리의 모든 노드에는 0이 들어가 있다. [s,e]는 앞으로의 질의들이 들어갈 닫힌 범위이다.
    int init(int s, int e) {
        int idx = cnt++;
        if (s < e) {
            int m = (s+e)>>1;
            l[idx] = init(s, m);
            r[idx] = init(m+1, e);
        }
        return idx;
    }
    // update(root,s,e,pos,val) : root가 루트인 트리를 기반으로 pos 위치에 val만을 업데이트(덧셈)한 트리를 만들어, 그 루트를 반환해 준다.
    int update(int root, int s, int e, int pos, int val) {
        if (pos < s || e < pos) return root;
        int idx = cnt++;
        if (s == e) {
            v[idx] = v[root] + val;
        }
        else {
            int m = (s+e)>>1;
            l[idx] = update(l[root], s, m, pos, val);
            r[idx] = update(r[root], m+1, e, pos, val);
            v[idx] = v[l[idx]] + v[r[idx]];
        } return idx;
    }
    // query(idx,s,e,l,r) : idx를 루트로 한 트리에서 [l,r] 구간의 값의 합을 반환해 준다.
    int query(int idx, int s, int e, int x, int y) {
        if (x <= s && e <= y) return v[idx];
        else if (e < x || y < s) return 0;
        else {
            int m = (s+e)>>1;
            return query(l[idx], s, m, x, y) + query(r[idx], m+1, e, x, y);
        }
    }
} pst;
```

### Li Chao 리차오

```cpp
TODO
```

## Flow 플로우

### Dinic 디닉

`O(V^2E)`

```cpp
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN = 3333; // !!! enough MAXN required: src=MAXN-4, snk=MAXN-3 !!!
struct dinic {
    int n, src, snk;
    int lr_src, lr_snk, lr_lsum; // !!! use this IFF use L-R flow !!!
    int cur[MAXN], lvl[MAXN];
    struct edg { int idx, cap, rev; };
    vector<edg> gph[MAXN];
    void add_edge(int u, int v, int k) {
        gph[u].push_back({ v,k,(int)gph[v].size() });
        gph[v].push_back({ u,0,(int)gph[u].size()-1 });
    }
    // !!! use this IFF use L-R flow !!!
    void add_lr_edge(int u, int v, int l, int r) {
        add_edge(lr_src, v, l);
        add_edge(u, lr_snk, l);
        add_edge(u, v, r-l);
        lr_lsum += l;
    }
    void init() {
        memset(cur, 0, sizeof(cur));
        memset(lvl, 0, sizeof(lvl));
        for (int i = 0; i < MAXN; i++) gph[i].clear();
        src = MAXN-4;
        snk = MAXN-3;
        lr_src = MAXN-2;
        lr_snk = MAXN-1;
        //add_edge(snk, src, 2e9); // !!! use this IFF use L-R flow !!!
    }
    dinic() {
        init();
    }
    bool bfs(int src, int snk) {
        queue<int> que;
        memset(lvl, -1, sizeof(lvl));
        lvl[src] = 0;
        que.push(src);
        while (!que.empty()) {
            int now = que.front(); que.pop();
            for (edg nxt : gph[now]) {
                if (nxt.cap > 0 && lvl[nxt.idx] == -1) {
                    lvl[nxt.idx] = lvl[now]+1;
                    que.push(nxt.idx);
                }
            }
        }
        return lvl[snk] != -1;
    }
    ll dfs(int now, int snk, int flw) {
        if (now == snk) return flw;
        for (int &i = cur[now]; i < gph[now].size(); i++) {
            edg &nxt = gph[now][i];
            if (nxt.cap > 0 && lvl[nxt.idx] == lvl[now]+1) {
                ll ret = dfs(nxt.idx, snk, min(nxt.cap, flw));
                if (ret > 0) {
                    nxt.cap -= ret;
                    gph[nxt.idx][nxt.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    ll match() {
        ll dap = 0;
        while (bfs(src, snk)) {
            memset(cur, 0, sizeof(cur));
            ll ret;
            while (ret = dfs(src, snk, 2e9)) {
                dap += ret;
            }
        }
        return dap;
    }
    // !!! use this IFF use L-R flow !!!
    bool lr_match() {
        ll dap = 0;
        while (bfs(lr_src, lr_snk)) {
            memset(cur, 0, sizeof(cur));
            ll ret;
            while (ret = dfs(lr_src, lr_snk, 2e9)) {
                dap += ret;
            }
        }
        return (dap == lr_lsum); // true == L-R feasible
    }
} flow;
```

### LR Flow 엘알플로우

정점 A에서 정점 B로, 하한 L, 상한 R인 간선이 있을 때 풀이법  

(1) [ A→B 유량 L, 비용 -1인 간선 ], [ A→B 유량 R-L, 비용 0인 간선 ] 이후 mincost-maxflow  
```cpp
void add_edge(int u, int v, int l, int r) {
    addEdge(u, v, l, -1);
    addEdge(u, v, r - l, 0);
}
```

(2) [ 새로운 source → B, 유량 L ], [ A → 새로운 sink, 유량 L ], [ A → B, 유량 R-L ], [ 기존 sink → 기존 source, 유량 무한 ] 이후, [ 새로운 source → 새로운 sink ]의 최대 유량이 L의 합이 되는지 확인  
```cpp
디닉 코드 참조
```

### MCMF 엠씨엠에프 (spfa)

`O((V+E)f)`  

```cpp
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int MAXN = 1111;
struct mcmf {
    int src, snk;
    int prv_v[MAXN], prv_e[MAXN], dst[MAXN], inq[MAXN];
    struct edg { int idx, cap, cst, rev; };
    vector<edg> gph[MAXN];
    void add_edge(int u, int v, int f, int c) {
        gph[u].push_back({v, f, c, gph[v].size()});
        gph[v].push_back({u, 0, -c, gph[u].size() - 1});
    }
    void init() {
        memset(prv_v, 0, sizeof(prv_v));
        memset(prv_e, 0, sizeof(prv_e));
        for (int i = 0; i < MAXN; i++) gph[i].clear();
        src = MAXN-2;
        snk = MAXN-1;
    }
    mcmf() {
        init();
    }
    bool spfa() {
        memset(dst, 0x3f, sizeof(dst));
        memset(inq, 0, sizeof(inq));
        queue<int> que;
        que.push(src);
        inq[src] = 1;
        dst[src] = 0;
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            inq[now] = 0;
            for (int i = 0; i < gph[now].size(); i++) {
                edg &nxt = gph[now][i];
                if (nxt.cap > 0 && dst[nxt.idx] > dst[now] + nxt.cst) {
                    dst[nxt.idx] = dst[now] + nxt.cst;
                    prv_v[nxt.idx] = now;
                    prv_e[nxt.idx] = i;
                    if (!inq[nxt.idx])
                        que.push(nxt.idx), inq[nxt.idx] = 1;
                }
            }
        }
        return dst[snk] != 0x3f3f3f3f;
    }
    pair<int, int> match() {
        int dap_cst = 0, dap_flw = 0;
        while (spfa()) {
            int mn_flw = 2e9;
            for (int now = snk; now != src; now = prv_v[now]) {
                int prv = prv_v[now], idx = prv_e[now];
                mn_flw = min(mn_flw, gph[prv][idx].cap);
            }
            for (int now = snk; now != src; now = prv_v[now]) {
                int prv = prv_v[now], idx = prv_e[now];
                gph[prv][idx].cap -= mn_flw;
                gph[now][gph[prv][idx].rev].cap += mn_flw;
                dap_cst += mn_flw * gph[prv][idx].cst;
            }
            dap_flw += mn_flw;
        }
        return make_pair(dap_flw, dap_cst);
    }
};
```

## 그래프 및 트리 Graph and Tree

### LCA 최소 공통 조상

```cpp
#include <algorithm>
#include <vector>
using namespace std;
const int n_ = 1e5 + 5;
const int d_ = 17; // 2^d > n
int n, m, d;
int dph[n_], par[n_][d_];
vector<int> gph[n_];
void setLCA(int now, int cnt) {
    dph[now] = cnt++;
    for (int i = 1; i <= d; i++)
        par[now][i] = par[par[now][i - 1]][i - 1];
    for (auto nxt : gph[now]) if (!dph[nxt])
        par[nxt][0] = now, setLCA(nxt, cnt);
}
int getLCA(int a, int b) {
    if (dph[a] < dph[b]) swap(a, b);
    for (int i = d; i >= 0; i--) if (dph[b] <= dph[par[a][i]])
        a = par[a][i];
    if (a == b) return a;
    for (int i = d; i >= 0; i--) if (par[a][i] != par[b][i])
        a = par[a][i], b = par[b][i];
    return par[a][0];
}
int main() {
    for (d = 1; (1 << d) <= n; d++); d--;
    setLCA(1, 1);
}
```

### LCA 트리에서 두 노드 사이의 거리

```cpp
#include <algorithm>
#include <vector>
using namespace std;
const int n_ = 1e5 + 5;
const int d_ = 17; // 2^d > n
int n, m, d;
int dph[n_], par[n_][d_];
vector<int> gph[n_];
void setLCA(int now, int cnt) {
    dph[now] = cnt++;
    for (int i = 1; i <= d; i++)
        par[now][i] = par[par[now][i - 1]][i - 1];
    for (auto nxt : gph[now]) if (!dph[nxt])
        par[nxt][0] = now, setLCA(nxt, cnt);
}
int dst(int a, int b) {
    int ret = 0;
    if (dph[a] < dph[b]) swap(a, b);
    for (int i = d; i >= 0; i--) if (dph[b] <= dph[par[a][i]]) {
        a = par[a][i];
        ret += (1<<i);
    }
    if (a == b) return ret;
    for (int i = d; i >= 0; i--) if (par[a][i] != par[b][i]) {
        a = par[a][i], b = par[b][i];
        ret += (1<<i)*2;
    }
    return ret+2;
}
int main() {
    for (d = 1; (1 << d) <= n; d++); d--;
    setLCA(1, 1);
}
```

### Cut Node 단절점

```cpp
#include <algorithm>
#include <vector>
using namespace std;

int cnt, chk[10001], isCutNode[10001];
vector<int> gph[10001];

void findCutNode(int now, int isRoot) {
    int vcnt = 0, vmin = n;
    chk[now] = ++cnt;
    for (int nxt : gph[now]) {
        if (!chk[nxt]) {
            findCutNode(nxt, 0);
            if (chk[nxt] == chk[now]) isCutNode[now] = 1;
            vcnt++;
        }
        vmin = min(vmin, chk[nxt]);
    }
    chk[now] = vmin;
    if (isRoot) isCutNode[now] = vcnt >= 2;
}

int main() {
    for (int i = 1; i <= n; i++) {
        if (!chk[i]) findCutNode(i, 1);
    }
}
```

### Cut Edge 단절선

```cpp
#include <vector>
#include <algorithm>
using namespace std;

int cnt, chk[100001];
vector<int> gph[100001];
vector<pair<int, int> > cutEdge;

int findCutEdge(int now, int par) {
    int ret = chk[now] = ++cnt;
    for (int nxt : gph[now]) {
        if (par == nxt) continue;
        if (!chk[nxt]) {
            int low = findCutEdge(nxt, now);
            if (low > chk[now]) {
                cutEdge.push_back({ min(now,nxt),max(now,nxt) });
            }
            ret = min(ret, low);
        }
        else {
            ret = min(ret, chk[nxt]);
        }
    }
    return ret;
}

int main() {
    findCutEdge(1, -1);
}
```

## DP Dynamic Programming 디피 동적계획법

### Convex Hull Trick CHT 컨벡스 헐 트릭

```cpp
TODO
```

## Math 수학

### Eratos Get Prime 에라토스테네스의 체 소수

```cpp
// [s, e] 구간의 소수들을 오름차순으로 리턴함
bool chkP[10000001]; // 배열 크기 주의
vector<ll> getPrimes(ll s, ll e) {
    vector<ll> ret;
    for (ll i = 2; i*i <= e; i++) if (!chkP[i])
        for (ll j = i*i; j <= e; j+=i) chkP[j] = 1;
    for (ll i = 2; i <= e; i++) if (!chkP[i] && s <= i && i <= e)
        ret.push_back(i);
    return ret;
}
```

### Prime Factorization Soinsu 소인수 분해

```cpp
// 밑만 리턴함, 중복 없음
vector<ll> getSoinsu(ll x) {
    ll y = x;
    vector<ll> ret;
    for (ll i = 2; i*i <= x; i++) {
        if (y%i == 0) {
            ret.push_back(i);
            while (y%i == 0) y /= i;
        }
    }
    if (y != 1) ret.push_back(y);
    return ret;
}
```

```cpp
// (밑, 지수) 쌍들을 리턴함, 밑에 대해서 오름차순으로 리턴함
vector<pair<ll, int> > getSoinsu(ll x) {
    ll y = x;
    vector<pair<ll, int> > ret;
    for (ll i = 2; i*i <= x; i++) {
        if (y%i == 0) {
            int cnt = 0;
            while (y%i == 0) y /= i, cnt++;
            ret.push_back({ i,cnt });
        }
    }
    if (y != 1) ret.push_back({ y,1 });
    return ret;
}
```

### GCD 최대공약수

```cpp
int gcd(int a, int b){ return b?gcd(b,a%b):a; }
```

### LCM 최소공배수

```cpp
int gcd(int a, int b){ return b?gcd(b,a%b):a; }
int lcm(int a, int b) {if(!a||!b)return a+b;return a*(b/gcd(a,b));}
```

### Extended GCD 확장 유클리드

`ax+by = gcd(a, b)`가 되는 정수쌍 `(x, y)`를 찾는다.

```cpp
pair<int,int> ext_gcd(int a, int b){
    if (b == 0) return { 1,0 };
    auto t = ext_gcd(b, a%b);
    return { t.second,t.first-(a/b)*t.second };
}
```

### Modular Inverse 모듈러 인버스

`ax mod M = 1`인 `x`를 찾는다.

```cpp
int mod_inv(int a, int M){
    return (ext_gcd(a, M).first + M) % M;
}
```

### Kitamasa 키타마사

선형점화식에서, `O(K^3logN)`의 행렬곱을 `O(K^2logN)`으로 떨군다.

```cpp
typedef long long lint;
const int mod = 1000000007;
int k, a[1004], w[1004];
 
int add(int x, int y) { return (x+y) % mod; }
int mul(int x, int y) { return (x*(lint)y) % mod; }
 
int kitamasa(lint n) {
    vector<int> c(k+1, 0); c[1] = 1;
 
    // n = 1 만들기
    int b = 62;
    while ((n>>b)%2==0) b--;
 
    for (b--; ~b; b--) {
        // c(n) -> c(2n)
        vector<int> d(2*k+1, 0);
        for (int i=1; i<=k; i++) for (int j=1; j<=k; j++) d[i+j] = add(d[i+j], mul(c[i], c[j]));
        for (int i=2*k; i>k; i--) for (int j=1; j<=k; j++) d[i-j] = add(d[i-j], mul(d[i], w[j]));
        d.resize(k+1);
        c = d;
        // c(n) -> c(n+1)
        if ((n>>b)&1) {
            vector<int> d(k+1, 0);
            d[1] = mul(c[k], w[k]);
            for (int i=2; i<=k; i++) d[i] = c[i-1] + mul(c[k], w[k+1-i]);
            c = d;
        }
    }
 
    int ans = 0;
    for (int i=1; i<=k; i++) ans = add(ans, mul(a[i], c[i]));
    return ans;
}
 
int main() {
    lint n;
    cin >> n >> k;
    for (int i=1; i<=k; i++) cin >> a[i]; // 첫 k개의 항
    for (int i=1; i<=k; i++) cin >> w[i]; // 점화식의 계수
 
    cout << kitamasa(n);
}
```

### FFT 빠른 푸리에 변환

`O(NlogN)`, `res[i] = for(j=0~i) a[j]*b[i-j]`, 

```cpp
#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;
typedef complex<double> base;
void fft(vector<base> &a, bool invert) {
    int n = a.size();
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
vector<int> multiply(const vector<int> &a,const vector<int> &b) {
    vector <base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(),b.size())) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    vector<int> res;
    res.resize(n);
    for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
    return res;
}
int main() {
    int n;                     // Rotating Multiply Example
    vector<int> a, b, res;
    scanf("%d", &n);
    a.resize(n*2); b.resize(n);
    for (int i=0;i<n;i++) {
        scanf("%d", &a[i]);
        a[i+n] = a[i];
    }
    for (int i=0;i<n;i++) {
        scanf("%d", &b[n-i-1]);
    }
    multiply(a, b, res);
    int ans = 0;
    for (int i=n;i<n*2;i++) {
        ans = max(ans, res[i]);
    }
    printf("%d", ans);
    return 0;
}
```

## String 문자열

### KMP 크누스 모리스 프랫

```cpp
#include <vector>
#include <string>
using namespace std;

vector<int> search(string str, string pattern) {
    vector<int> f;
    f.push_back(0);
    for (int i = 1, k = 0; i < pattern.size(); i++) {
        while (k != 0 && pattern[k] != pattern[i]) {
            k = f[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            f.push_back(++k);
        }
        else {
            f.push_back(0);
        }
    }
    int j = 0;
    vector<int> matches;
    for (int i = 0; i < str.size(); i++) {
        while (j != 0 && pattern[j] != str[i]) {
            j = f[j - 1];
        }
        if (pattern[j] == str[i]) {
            if (j + 1 == pattern.size()) {
                matches.push_back(i - (int) pattern.size() + 2);
                j = f[j];
            }
            else {
                j++;
            }
        }
    }
    return matches;
}
```

### Suffix Array 서픽스 어레이 접미사 배열

* `sa[n] = beginning index of N-th suffix (ordered, 1-indexed)`, `O(NlogN)`
* `lcp[n] = length of common prefix between sa[n-1] and sa[n]`, `O(N)`

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
vi SuffixArray(string &S) {
    int i,j,k;
    int m = 26; // 처음 알파벳 개수
    int N = S.length();
    vi SA(N+1,0), cnt(max(N,m)+1,0), x(N+1,0), y(N+1,0);
    for (i=1;i<=N;i++) cnt[x[i] = S[i]-'a'+1]++;
    for (i=1;i<=m;i++) cnt[i] += cnt[i-1];
    for (i=N;i;i--) SA[cnt[x[i]]--] = i;
    for (int len=1,p=1;p<N;len<<=1,m=p){
        for (p=0,i=N-len;++i<=N;) y[++p] = i;
        for (i=1;i<=N;i++) if (SA[i] > len) y[++p] = SA[i]-len;
        for (i=0;i<=m;i++) cnt[i] = 0;
        for (i=1;i<=N;i++) cnt[x[y[i]]]++;
        for (i=1;i<=m;i++) cnt[i] += cnt[i-1];
        for (i=N;i;i--) SA[cnt[x[y[i]]]--] = y[i];
        swap(x,y); p = 1; x[SA[1]] = 1;
        for (i=1;i<N;i++)
            x[SA[i+1]] = SA[i]+len <= N && SA[i+1]+len <= N && y[SA[i]] == y[SA[i+1]] && y[SA[i]+len] == y[SA[i+1]+len] ? p : ++p;
    }
    return SA;
}
vi GetLcp(string &S, vi &SA) {
    int i,j,k=0;
    int N = SA.size()-1;
    vi rank(N+1,0), lcp(N+1, 0);
    for (i=1;i<=N;i++) rank[SA[i]] = i;
    for (i=1;i<=N;lcp[rank[i++]]=k)
        for (k?k--:0,j=SA[rank[i]-1];S[i+k]==S[j+k];k++);
    return lcp;
}
int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int n;
    string str;
    cin >> n >> str;
    str = '$' + str;
    vi sa = SuffixArray(str);
    vi lcp = GetLcp(str, sa);
    cout << *max_element(lcp.begin()+1, lcp.end());
    return 0;
}
```

### Manacher 매내쳐

`p[i] = i-k, ..., i, ..., i+k까지 팰린드롬인 가장 큰 k`  
`O(N)`  

```cpp
// 답이 long long 범위를 벗어나지 않는지 유의할 것,
// manacher를 사용하는 경우, 대체로 제한이 크기 때문에 int 범위를 벗어나는 경우가 많음
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2000000 + 2;
int p[MAXN * 2 + 1];
char t[MAXN + 1], s[MAXN * 2 + 1];

void manacher(int n) {
    for (int i = 0; i < n; i++) {
        s[i * 2] = t[i];
        if (i != n - 1) s[i * 2 + 1] = '$';
    }
    n = n * 2 - 1;
    int r = -1, k = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min(r - i, p[2 * k - i]);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && s[i - p[i] - 1] == s[i + p[i] + 1])
            p[i]++;
        if (r < i + p[i]) r = i + p[i], k = i;
    }
}

int main() {
    scanf("%s", t);
    int n = strlen(t), dap = 0;
    manacher(n);
    for (int i = 0; i < n * 2; i++) {
        if (i % 2) dap += (p[i] + 1) / 2;
        else dap += p[i] / 2;
    }
    printf("%d\n", dap + n);
    return 0;
}
```

## Geometry 기하

### Convex Hull 컨벡스헐

```cpp
#include<cstdio>
#include<algorithm>
#include<tuple>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
struct POINT{
    int x, y;
    bool operator <(POINT a)const {
        return x == a.x ? y < a.y : x < a.x;
    }
    POINT operator -(POINT a)const {
        return { x-a.x,y-a.y };
    }
};
int N;
ll sq(int x){
    return (ll)x*x;
}
ll dst(POINT A, POINT B) {
    return sq(A.x-B.x)+sq(A.y-B.y);
}
int ccw(POINT A, POINT B, POINT C){
    ll r = A.x*B.y + B.x*C.y + C.x*A.y;
    r -= A.y*B.x + B.y*C.x + C.y*A.x;
    if (r > 0) return 1;
    if (r < 0) return -1;
    return 0;
}

vector<POINT> GetConvexHull(vector<POINT> &p) {
    swap(p[0], *min_element(p.begin(), p.end()));
    sort(p.begin()+1, p.end(), [&](const POINT &A, const POINT &B){
        if(ccw(p[0], A, B) != 0){
            return ccw(p[0], A, B) < 0;
        }
        return dst(A, p[0]) < dst(B, p[0]);
    });
    vector<POINT> hull;
    hull.push_back(p[0]);
    for(int i = 1; i < N; i++){
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), p[i]) >= 0){
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    return hull;
}

pii FarthestPair(vector<POINT> &hull) {
    pii ret;
    ll mx = -1;
    for (int i = 0, j = 0; i < hull.size(); i++) {
        while (j+1 < hull.size() && ccw({ 0,0 }, hull[i+1]-hull[i], hull[j+1]-hull[j]) <= 0) {
            if (mx < dst(hull[i], hull[j])) {
                mx = dst(hull[i], hull[j]);
                ret = { i,j };
            }
            j++;
        }
        if (mx < dst(hull[i], hull[j])) {
            mx = dst(hull[i], hull[j]);
            ret = { i,j };
        }
    }
    return ret;
}

int main(){
    scanf("%d", &N);
    vector<POINT> p(N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }

    vector<POINT> hull = GetConvexHull(p);
    int a, b; tie(a, b) = FarthestPair(hull);
    printf("%.8lf", sqrt(dst(hull[a], hull[b])));

    return 0;
}
```

### Point in Polygon

```cpp
#include <vector>
using namespace std;
struct point { int x, y; };
typedef vector<point> polygon;
bool isInside(point B, vector<point> &p) {
   int cross = 0;
   for (int i = 0; i < p.size(); i++){
       int j = (i+1) % p.size();
       if ((p[i].y > B.y) != (p[j].y > B.y)) {
           double atX = (p[j].x-p[i].x)*(B.y-p[i].y)/(p[j].y-p[i].y)+p[i].x;
           if (B.x < atX) cross++;
       }
   }
   return cross % 2 > 0;
}
```

### line intersect cross 선분 교차

```cpp
int ccw(point a, point b, point c) {
    // r 오버플로우 주의
    ll r = a.x * b.y + b.x * c.y + c.x * a.y;
    r -= a.y * b.x + b.y * c.x + c.y * a.x;
    if (r > 0) return 1;
    if (r < 0) return -1;
    return 0;
}

int isCross(point a, point b, point c, point d) {
    int ab = ccw(a, b, c)*ccw(a, b, d);
    int cd = ccw(c, d, a)*ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return c <= b && a <= d;
    }
    return ab <= 0 && cd <= 0;
}
```

## Magic 흑마법

### pbds BST

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
int main(){
    ordered_set X;
    X.insert(4);
    cout << *X.find_by_order(4) << endl;
    cout << X.order_of_key(3) << endl;
}
```

### 2D arrary rotation 배열 돌리기

```cpp
// Rotate n * m array A by clockwise and save in B (A: n * m, B: m * n)
void rotate90(int **A, int **B, int n, int m) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[n - j - 1][i];
}
```