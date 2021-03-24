#include<iostream>
using namespace std;
#pragma warning(disable:4996);

typedef struct Point {
	int x, y;

	Point operator-(Point B) {
		return { x - B.x, y - B.y };
	}

	bool operator==(Point B) {
		return x == B.x && y == B.y;
	}
};

int n, m, x, y;
Point p[5001];

int isCCW(Point A, Point B) {
	return A.x * B.y - B.x * A.y;
}

bool isInside(Point target) {

	int Counter = 0;
	for (int i = 0; i < n; i++) {

		if (p[i] == target) 
			return true;

		Point A = p[i] - target;
		Point B = i < n - 1 ? p[i + 1] - target : p[0] - target;

		// x축과 평행하면 건너뛰기
		if (A.y == 0 && B.y == 0)
			continue;

		if (A.y < 0 && B.y >= 0 && isCCW(A, B) > 0
			|| A.y >= 0 && B.y < 0 && isCCW(B, A) > 0)
			Counter++;

	}

	return Counter % 2 ? true : false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("point.inp", "r", stdin);
	freopen("point.out", "w", stdout);

	
	cin >> n; // n각형

	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p[i] = { x,y };
	}

	cin >> m;

	while (m--) {

		cin >> x >> y;
		
		Point target = { x,y };

		isInside(target) ? cout << 1 << '\n' : cout << 0 << '\n';
	}

	return 0;
}