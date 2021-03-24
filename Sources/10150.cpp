#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
#pragma warning(disable:4996);

int idx;
int Parent[25143];
string StartWord, EndWord;
string WordDictionary[25143];
vector<string> OUTPUT;

bool HasInclude(string now, int size) {
	for (int i = 0; i < size;i++) {
		if (now == WordDictionary[i]) return true;
	}
	return false;
}
int isDoublet(string Comparator, string Target) {
	int counter = 0;

	for (int i = 0; i < Comparator.size(); i++) {
		if (Comparator[i] != Target[i]) counter++;
	}

	return counter;
}


void solve(int DictionarySize) {
	if (StartWord.length() != EndWord.length()) return;
	if (HasInclude(StartWord, DictionarySize) == false || HasInclude(EndWord, DictionarySize) == false) return;

	queue<int>Sub_Dictionary;

	int StartWordIdx;


	// 길이가 동일한 단어 솎아내기
	for (int i = 0; i < DictionarySize; i++) {
		string item = WordDictionary[i];

		if (item == StartWord) {
			StartWordIdx = i;
		}


		if (item.length() == StartWord.length()) {
			Sub_Dictionary.push(i);
		}
	}
	
	Parent[StartWordIdx] = -1;
	queue<int> words;

	words.push(StartWordIdx);
	while (!words.empty()) {
		int now = words.front();
		words.pop();

		string value = WordDictionary[now];

		if (isDoublet(value, EndWord) < 2) {
			OUTPUT.push_back(EndWord);

			while (Parent[now] != -1) {
				string value = WordDictionary[now];
				OUTPUT.push_back(value);
				now = Parent[now];
			}

			OUTPUT.push_back(StartWord);
			break;
		}

		int size = Sub_Dictionary.size();

		for (int i = 0; i < size; i++) {
			int nxt = Sub_Dictionary.front();
			Sub_Dictionary.pop();

			string nxt_value = WordDictionary[nxt];
			if (value == nxt_value) continue;

			if (isDoublet(value, nxt_value) < 2) {
				Parent[nxt] = now;
				words.push(nxt);
				continue;
			}

			Sub_Dictionary.push(nxt);
		}

	}
}
	


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("10150.inp", "r", stdin);
	freopen("10150.out", "w", stdout);

	string str;

	int end = 0;
	int count = 0;
	while (getline(cin, str)) {
		
		int space = str.find(" ");

		if (space < str.length()) {
			if (count > 0) {
				cout << '\n';
			}

			EndWord = str.substr(space + 1, str.length());
			StartWord = str.substr(0, space);
			
			OUTPUT.clear();

			solve(end);

			if(OUTPUT.size() < 2){
				cout << "No solution.\n";
			}
			else {
				while (!OUTPUT.empty()) {
					cout << OUTPUT.back() << '\n';

					OUTPUT.pop_back();
				}
				
			}

			count++;
		}
		else {
			WordDictionary[end] = str;
			end++;
		}
	}


	return 0;
}