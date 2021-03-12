#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#pragma warning(disable:4996);

int Distance[25143];
string WordDictionary[25143];
vector<string> OUTPUT;

bool isDoublet(string Comparator, string Target) {
	int length_diff = Comparator.length() - Target.length();
		
	length_diff = abs(length_diff);

	if (length_diff > 0) return false;

	for (int i = 0; i < Comparator.size(); i++) {
		if (i > Target.length()) break;
		if (Comparator[i] != Target[i]) length_diff++;
	}

	if (length_diff > 1) return false;

	return true;
}

void DistanceSetting(int DictionarySize) {
	for (int i = 0; i < DictionarySize; i++) {
		Distance[i] = 26000;
	}
}

bool cmp(string Comparator, string Target) {
	if (Comparator.length() < Target.length())
		return true;
	return false;
}

bool DoubletCmp(int Comparator, int Target){
	if (Distance[Comparator] < Distance[Target])
		return true;
	return false;
}

void solve(string StartWord, string EndWord, int DictionarySize) {
	vector<int> Doublet[25143];

	int Start_pos = -1, End_pos = -1;

	sort(WordDictionary, WordDictionary + DictionarySize - 1, cmp);

	for (int i = 0; i < DictionarySize; i++) {
		if (WordDictionary[i] == StartWord) 
			Start_pos = i;

		if (WordDictionary[i] == EndWord)
			End_pos = i;

		for (int j = i + 1; j < DictionarySize; j++) {
			if (WordDictionary[i].length() != WordDictionary[j].length()) 
				break;

			if (isDoublet(WordDictionary[i], WordDictionary[j])) {
				Doublet[i].push_back(j);
				Doublet[j].push_back(i);
			}
		}
	}


	if (Start_pos == -1 || End_pos == -1) 
		return;

	queue<int> q;
	q.push(End_pos);
	
	DistanceSetting(DictionarySize);

	Distance[End_pos] = 0;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == Start_pos) continue;

		for (int nxt : Doublet[now]) {
			if (Distance[nxt] > Distance[now] + 1) {
				Distance[nxt] = Distance[now] + 1;
				q.push(nxt);
			}
		}
	}

	for (int i = 0; i < DictionarySize; i++) {
		sort(Doublet[i].begin(), Doublet[i].end(), DoubletCmp);
	}

	q.push(Start_pos);
	OUTPUT.push_back(StartWord);

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == End_pos || Doublet[now].size() == 0) break;

		int nxt = Doublet[now][0];
		if (Distance[nxt] != Distance[Doublet[nxt][0]] + 1) break;

		OUTPUT.push_back(WordDictionary[nxt]);
		q.push(nxt);
	}
	OUTPUT.push_back(EndWord);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("10150.inp", "r", stdin);
	freopen("10150.out", "w", stdout);

	string str;

	int end = 0;
	while (getline(cin, str)) {
		
		int space = str.find(" ");

		if (space < str.length()) {

			string str2 = str.substr(space + 1, str.length());
			str = str.substr(0, space);
			
			OUTPUT.clear();

			solve(str, str2, end);

			if(OUTPUT.size() <= 2){
				cout << "No solution.\n";
			}
			else {
				for (string str : OUTPUT)
					cout << str << '\n';
			}
			cout << '\n';
		}
		else {
			WordDictionary[end] = str;
			end++;
		}
	}

	return 0;
}