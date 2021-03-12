#include<iostream>
using namespace std;
#pragma warning(disable:4996);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("10469.inp", "r", stdin);
	freopen("10469.out", "w", stdout);

	unsigned int n, m;
	while (cin >> n  && cin >> m) {
		unsigned int ans = n ^ m;
		cout << ans << '\n';
	}

	return 0;
}