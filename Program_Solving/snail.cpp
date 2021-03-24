#include<iostream>
using namespace std;
#pragma warning(disable:4996);

int H, Up, Down, F;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("snail.inp", "r", stdin);
	freopen("snail.out", "w", stdout);

	while (1) {
		cin >> H >> Up >> Down >> F;
		if (H == 0 && Up == 0 && Down == 0 && F == 0)
			break;

		int day = 1;
		int now = 0;
		
		int Decrease_rate = Up * F;
		H *= 100;
		Up *= 100;
		Down *= 100;

		while (1) {
			now += Up;
			if (now > H) break;
			
			if (Up > 0) {
				Up -= Decrease_rate;
			}
			if (Up < 0) Up = 0;

			now -= Down;

			if (now <= 0) break;
			
			day++;
		}

		if (now <= 0) {
			cout << "failure on day " << day;
		}
		else {
			cout << "success on day " << day;
		}
		cout << '\n';
	}

	return 0;
}