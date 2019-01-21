#include <cstdio>
int n, d[1001];
int main() {
    scanf("%d", &n);
    d[1] = d[3] = d[4] = 1;
    for (int i = 5; i <= n; i++) {
        if (!(d[i-1] && d[i-3] && d[i-4])) {
            d[i] = 1;
        }
    }
    puts(d[n] ? "SK" : "CY");
    return 0;
}