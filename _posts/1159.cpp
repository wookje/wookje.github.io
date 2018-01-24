#include <cstdio>
#include <map>
using namespace std;

int n;
char a[155];
map<char, int> s;

int main() {
	scanf("%d", &n);
	while (n--) scanf("%s", a), s[a[0]]++;
	for (auto it : s) if (it.second >= 5) putchar(it.first), n++;
	if (n == -1) printf("%s", "PREDAJA");
	return 0;
}