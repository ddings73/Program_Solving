#include<iostream>
#include<algorithm>
using namespace std;
#pragma warning(disable:4996);

typedef struct Point {
	int x, y;
};

typedef struct Line {
	Point here, there;
};

typedef struct Polygon {
	Point p[10001];
};

int x, y;

int isCCW(Point A, Point B) {
	return A.x * B.y - B.x * A.y;
}

Polygon InputPolygon(int size) {
	
	Polygon now;

	for (int i = 0; i < size; i++) {
		cin >> x >> y;
		now.p[i] = { x,y };
	}

	return now;
}

Polygon getOuterPolygon(Polygon target) {


}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("tangent.inp", "r", stdin);
	freopen("tangent.out", "w", stdout);
	cout.setf(ios::showpoint);
	cout << fixed;
	cout.precision(1);

	int t, n, m;

	cin >> t;
	while (t--) {
		
		cin >> n;
		Polygon A = InputPolygon(n);

		cin >> m;
		Polygon B = InputPolygon(m);

		Polygon OuterA = getOuterPolygon(A);

		Polygon OuterB = getOuterPolygon(B);
		
		



	}
	return 0;
}