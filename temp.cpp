#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int n;
int c[200002], v[200002], par[200002], dst[200002];
struct edg {
    int idx, dst;
};
vector<edg> gph[200002];

map<int, int> go(int cur) {
    map<int, int> res; // { dst: cnt }
    for (edg nxt : gph[cur]) {
        map<int, int> ret = go(nxt.idx);
        for (auto &it : ret) {
            int k = it.first;
            res[it.first+nxt.dst] += it.second;
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &par[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &dst[i]);
        gph[par[i]].push_back({ i,dst[i] });
    }

    go(1);

    return 0;
}
