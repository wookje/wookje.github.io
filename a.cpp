#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cassert>
#include <set>
#include <unordered_set>
using namespace std;
typedef long long ll;

int n, c;
ll a[200002];

bool feasible(int dst) {
    int prv = 1, cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i]-a[prv] >= dst) {
            cnt++;
            prv =  i;
        }
    }
    return cnt >= c;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a+1, a+n+1);

    int lft = 1, rgt = a[n]-a[1];
    int ans = -1;
    while (lft <= rgt) {
        int mid = (lft+rgt+1)/2;
        if (feasible(mid)) {
            ans = mid;
            lft = mid+1;
        }
        else {
            rgt = mid-1;
        }
    }

    cout << ans << "\n";

    return 0;
}