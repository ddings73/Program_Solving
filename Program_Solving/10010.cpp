#include<iostream>
#include<vector>
using namespace std;
#pragma warning(disable:4996);

int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
char grid[50][50];
int n, m;

bool solve(string str, int x, int y) {
	for (int i = 0; i < 8; i++) {
		int count = 0;
		int nx = x, ny = y;
		while (count < str.length()) {
			if (grid[nx][ny] != str[count]) break;
			if (nx < 0 || n <= nx || ny < 0 || m <= ny) break;

			nx = nx + dx[i];
			ny = ny + dy[i];
			count++;
			
			if (count == str.length()) {
				cout << x + 1 << " " << y + 1 << '\n';
				return true;
			}

		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("10010.inp", "r", stdin);
	freopen("10010.out", "w", stdout);

	int repeat;
	string str;
	vector<string> strings;

	cin >> repeat;
	while (repeat--) {
		cin >> n >> m;
		
		for (int i = 0; i < n; i++) {
			cin >> grid[i];
			for (int j = 0; j < m; j++) {
				if (grid[i][j] < 97)
					grid[i][j] += 32;
			}
		}

		int k;
		cin >> k;
		while (k--) {
			cin >> str;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] < 97)
					str[i] += 32;
			}

			bool flag = false;
			for (int i = 0; i < n && !flag; i++) {
				for (int j = 0; j < m && !flag; j++) {
					if (str[0] == grid[i][j]) {
						if (solve(str, i, j))
							flag = true;
					}
				}
			}
		}
		if(repeat > 0)
			cout << "\n";
	}
	
	return 0;
}