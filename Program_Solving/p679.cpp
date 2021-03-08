#include<iostream>
using namespace std;
#pragma warning(disable:4996);

int Depth, i, repeat;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p679.inp", "r", stdin);
	freopen("p679.out", "w", stdout);

	cin >> repeat;

	while (repeat--) {
		cin >> Depth >> i;

		int idx = 1;
		Depth--;
		while (Depth--) {
			if (i % 2 == 1) {
				idx *= 2;
				i -= (i / 2);
			}
			else {
				idx = idx * 2 + 1;
				i /= 2;
			}
		}

		cout << idx << '\n';
	}
	cin >> repeat;

	return 0;
}
