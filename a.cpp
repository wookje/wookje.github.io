#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;

int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

int n;
vector<int> l, r;
char dir[5555];
int res[5555];
int st = -1;
int ed = -1;

int calc(char c) {
    int temp = 0;
    if (c == 'R') {
        int lmax = -1;
        for (int i = ed; i >= st; i--) {
            if (dir[i] == 'L') {
                lmax = max(lmax, res[i]);
            }
            else {
                if (res[i] > lmax) {
                    temp++;
                }
            }
        }
    }
    else {
        int rmax = -1;
        for (int i = st; i <= ed; i++) {
            if (dir[i] == 'R') {
                rmax = max(rmax, res[i]);
            }
            else {
                if (res[i] > rmax) {
                    temp++;
                }
            }
        }
    }
    return temp + (n - ed + st - 1);
}

int main() {
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        char c;
        cin >> a >> c;
        if (c == 'L') l.push_back(a), dir[i] = 'L';
        else r.push_back(a), dir[i] = 'R';
    }

    if (r.size() == 0 || l.size() == 0) {
        cout << n << "\n";
        return 0;
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    for (int i = 1; i <= n; i++) {
        if (dir[i] == 'R') {
            st = i;
            break;
        }
    }
    for (int i = n; i >= 1; i--) {
        if (dir[i] == 'L') {
            ed = i;
            break;
        }
    }

    int lidx = 0;
    int ridx = r.size()-1;
    for (int i = st; i <= ed; i++) {
        if (dir[i] == 'R') {
            res[i] = r[ridx--];
        }
    }
    for (int i = ed; i >= st; i--) {
        if (dir[i] == 'L') {
            res[i] = l[lidx++];
        }
    }

    int dap = calc('R');

    memset(res, 0, sizeof(res));

    lidx = l.size()-1;
    ridx = 0;
    for (int i = st; i <= ed; i++) {
        if (dir[i] == 'R') {
            res[i] = r[ridx++];
        }
    }
    for (int i = ed; i >= st; i--) {
        if (dir[i] == 'L') {
            res[i] = l[lidx--];
        }
    }

    int dap2 = calc('L');
    
    dap = max(dap, dap2);

    cout << max(0, dap) << "\n";

    return 0;
}