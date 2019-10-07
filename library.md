---
layout: page
title: Tags
permalink: /library/
sitemap:
  priority: 0.7
---

알고리즘/자료구조 복붙용 라이브러리

수정 및 추가 제안, 오류 제보 환영합니다

wookje.happy@gmail.com 또는 개인적으로 연락 주세요

## Tree 트리

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

## Flow 플로우

### Dinic 디닉

`O(V^2E)`

```cpp
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int n_ = 700+7;

struct edg {
    int idx, cap, rev;
};
vector<edg> gph[n_];
int n, cur[n_], lvl[n_];

void addEdge(int u, int v, int k) {
    gph[u].push_back({ v,k,gph[v].size() });
    gph[v].push_back({ u,0,gph[u].size()-1 });
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

ll go(int src, int snk) {
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
```

### MCMF 엠씨엠에프 (spfa)

```cpp
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
const int src = 801;
const int snk = 802;

struct edg {
    int idx, cap, cst, rev;
};
vector<edg> gph[888];
int n, m;
int prv_v[888], prv_e[888];

void addEdge(int u, int v, int c) {
    gph[u].push_back({v, 1, c, gph[v].size()});
    gph[v].push_back({u, 0, -c, gph[u].size() - 1});
}

int dst[888], inq[888];
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

void gogogo() {
    int dap_cst = 0, dap_flw = 0;
    while (spfa()) {
        int mn_flw = 2e9;
        for (int now = snk; now != src; now = prv_v[now]) {
            int prv = prv_v[now];
            int idx = prv_e[now];
            mn_flw = min(mn_flw, gph[prv][idx].cap);
        }
        for (int now = snk; now != src; now = prv_v[now]) {
            int prv = prv_v[now];
            int idx = prv_e[now];
            gph[prv][idx].cap -= mn_flw;
            gph[now][gph[prv][idx].rev].cap += mn_flw;
            dap_cst += mn_flw * gph[prv][idx].cst;
        }
        dap_flw += mn_flw;
    }
    printf("%d\n%d\n", dap_flw, dap_cst);
}
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

## Math 수학

### GCD 최대공약수

```cpp
int gcd(int a, int b){ return b?gcd(b,a%b):a; }
```

### LCM 최소공배수

```cpp
int gcd(int a, int b){ return b?gcd(b,a%b):a; }
int lcm(int a, int b){ return a * b / gcd(a,b); }
```

### Extended GCD 확장 유클리드

`ax+by = gcd(a, b)`가 되는 정수쌍 `(x, y)`를 찾는다.

```cpp
pair<int,int> ext_gcd(int a, int b){
    if (b) {
        auto tmp = ext_gcd(b, a%b);
        return { tmp.second,tmp.first-(a/b)*tmp.second };
    }
    else {
      return { 1,0 };
    }
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

### pbds

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