#include<iostream>
#include<algorithm>
using namespace std;
#pragma warning(disable:4996);

struct Point {
	// x1 : 현재 x좌표
	// y2 - y1 : y크기
	// value : 시작선 +1, 끝선 -1
	int x, y1, y2, value;
};

Point rect[20001];
int seg[65536], cnt[65536];

bool cmp(Point a, Point b) {
	return a.x < b.x;
}

/*
now = 현재 범위의 루트
start, end = 현재 탐색범위
left, right = 목표 범위
value = 목표범위의 좌표에 더할 값.
*/
void update(int root, int start, int end, int left, int right, int value) {
	if (end < left || right < start) return; // 범위 벗어나면 리턴

	if (left <= start && end <= right) {
		cnt[root] += value;
	}
	else {

		int mid = start + (end - start) / 2;

		// 왼쪽 서브트리
		update(root * 2, start, mid, left, right, value);

		// 오른쪽 서브트리
		update(root * 2 + 1, mid + 1, end, left, right, value);
	}

	if (cnt[root]) 
		seg[root] = end - start + 1;
	else {
		if (start == end)seg[root] = 0;
		else seg[root] = seg[root * 2] + seg[root * 2 + 1];
	}
}

int solve(int size) {
	long long int ret = 0;

	for (int i = 0, xPrev; i < size * 2; i++) {
		Point now = rect[i];
		
		if (i > 0) {
			//now의 x가 항상 더 크거나 같음 ( 정렬했기때문에 )
			ret += (now.x - xPrev) * seg[1];

		} // 면적 추가하기

		update(1, -10000, 22767, now.y1, now.y2, now.value);
		// 새그 업데이트.

		xPrev = now.x;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("rectangle.inp", "r", stdin);
	freopen("rectangle.out", "w", stdout);

	int n;
	cin >> n;

	for (int i = 0,a,b,c,d; i < n; i++) {
		cin >> a >> b >> c >> d;
		

		rect[i] = { a,b,d - 1,1 };
		rect[i + n] = { c,b,d - 1,-1 };
	}
	
	sort(rect, rect + n + n, cmp);

	cout << solve(n);
	
	return 0;
}