#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
#pragma warning(disable:4996);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("10137.inp", "r", stdin);
	freopen("10137.out", "w", stdout);
	cout.setf(ios::showpoint);
	cout << fixed;
	cout.precision(2);

	int n, small, big, total;
	vector<int> student;


	while (1) {
		cin >> n;
		if (n == 0)
			break;

		small = big = total = 0;
		student.clear();
		for (int i = 0; i < n; i++) {
			double money;
			cin >> money;
			student.push_back(money * 100 + 0.5);
			total += student.back();
		}

		small = big = total / n;
		if (total % n != 0) {
			big++;
		}

		int big_gap, small_gap;

		big_gap = small_gap = 0;

		for (int i = 0; i < n; i++) {
			if (student[i] < small) {
				small_gap += small - student[i];
			}
			else if (big < student[i]) {
				big_gap += student[i] - big;
			}
		}

		int ret = max(big_gap, small_gap);
		cout << '$' << ret / 100.0 << '\n';
	}

	return 0;
}

