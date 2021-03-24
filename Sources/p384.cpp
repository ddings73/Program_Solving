#include<iostream>
using namespace std;
#pragma warning(disable:4996);

bool isSlump(string str) {

	int size = str.length();

	if (str[0] != 'D' && str[0] != 'E' || str[size - 1] != 'G') return false;

	for (int i = 1; i < size; i++) {
		if (str[i] == 'D' || str[i] == 'E') {
			if (str[i - 1] != 'F') return false;
			string sub_slump = str.substr(i, size);
			if (isSlump(sub_slump)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (str[i] != 'F' && str[i] != 'G') return false;
		else if (str[i] == 'G') {
			if (i != size - 1 || str[i - 1] != 'F') 
				return false;
		}
	}

	return true;
}

bool isSlimp(string str) {

	int size = str.length();

	if (str[0] != 'A' || size == 1) return false;
	
	if (size == 2) {
		if (str == "AH") return true;
		else return false;
	}


	if (str[1] == 'B') {
		string sub_slimp = str.substr(2, size - 3);
		if (isSlimp(sub_slimp) && str[size - 1] == 'C') {
			return true;
		}
	}
	else if (str[1] == 'D' || str[1] == 'E') {
		string sub_slump = str.substr(1, size - 2);
		if (isSlump(sub_slump) && str[size - 1] == 'C') {
			return true;
		}
	}
	
	return false;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("p384.inp", "r", stdin);
	freopen("p384.out", "w", stdout);

	int TestCase;
	cin >> TestCase;

	cout << "SLURPYS OUTPUT\n";
	while (TestCase--) {
		string str;
		cin >> str;

		string slimp, slump;

		for (int i = 0; i < str.length(); i++) {

			if (str[i] == 'D' || str[i] == 'E') {
				if (i == 0) break;
				if (str[i - 1] == 'C' || str[i - 1] == 'H') {
					slimp = str.substr(0, i);
					slump = str.substr(i, str.length());
					break;
				}
			}
		}

		if (slump.empty() || slimp.empty()) {
			cout << "NO\n";
		}
		else if (isSlimp(slimp) && isSlump(slump)) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}

		
	}
	cout << "END OF OUTPUT\n";
	return 0;
}