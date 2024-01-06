#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
using namespace std;

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int n, m, k;
long long x;
long long a[555][555], b[555][555];
queue<pair<int, int> > q;

// g++ temp.cpp -o ex --std=c++11

bool go(long long mid) {
    int cnt = k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            b[i][j] = a[i][j];
        }
    }
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int d = 0; d < 4; d++) {
                int nx = i+dx[d], ny = j+dy[d];
                if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
                    if (b[i][j] <= b[nx][ny] && b[nx][ny]-b[i][j] > mid) {
                        q.push({ i,j });
                        break;
                    }
                }
            }
        }
    }
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int i = cur.first, j = cur.second;
        if (b[i][j] == x) continue;
        b[i][j] = x;
        cnt--;
        if (cnt < 0) {
            return 0;
        }
        for (int d = 0; d < 4; d++) {
            int nx = i+dx[d], ny = j+dy[d];
            if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
                if (b[i][j]-b[nx][ny] > mid) {
                    q.push({ nx,ny });
                }
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d %d %d %lld", &n, &m, &k, &x);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    long long l = 0, r = 1e18, mid, dap = 0;
    while (l <= r) {
        mid = (l+r)/2;
        if (go(mid)) {
            r = mid-1;
            dap = mid;
        }
        else {
            l = mid+1;
        }
    }

    printf("%lld\n", dap);

    return 0;
}