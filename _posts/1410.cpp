#include <iostream>
#include <string>
using namespace std;

const int mod = 1000003;

int n, k;
int dp[50][1 << 15];
string str[15];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    
    cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> str[i];

	int len = str[0].size();
	for (int i = 0; i < len; ++i) {
		for (char c = 'a'; c <= 'z'; c++) {
			int v = 0;
			for (int j = 0; j < n; j++) {
				if (str[j][i] == c || str[j][i] == '?') {
					v |= (1 << j);
				}
			}
			if (!i) {
				dp[i][v]++;
			}
			else {
				for (int j = 0; j < (1 << n); j++) {
					dp[i][j&v] = (dp[i][j&v] + dp[i - 1][j]) % mod;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		int bit = 0;
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) {
				bit++;
			}
		}
		if (bit == k) {
			ans = (ans + dp[len - 1][i]) % mod;
		}
	}

    cout << ans;

	return 0;
}