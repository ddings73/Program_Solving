#include<iostream>
#include<algorithm>
#pragma warning(disable:4996);
using namespace std;

int solve(int num) {
	int cnt = 1;
	while (num > 1) {
		cnt++;
		if (num % 2 == 0) {
			num /= 2;
		}
		else {
			num = num * 3 + 1;
		}
	}

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p100.inp", "r", stdin);
	freopen("p100.out", "w", stdout);

	int i, j, length;

	while (cin >> i && cin >> j) {
		length = 0;


		int here = min(i, j);
		while (here <= max(i,j)) {
			length = max(length, solve(here));
			here++;
		}
		
		cout << i << " " << j << " " << length << "\n";
	}

	return 0;
}