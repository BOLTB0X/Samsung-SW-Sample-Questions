#include <iostream>
#include <vector>
using namespace std;

vector<int> numbers;
vector<int> oper;
int n;
int max_value = -1000000000;
int min_value = 1000000000;

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void solution(int number, vector<int> oper, int idx) {
	if (idx == n) {
		max_value = max(number, max_value);
		min_value = min(number, min_value);
		return;
	}
	else {
		if (oper[0] > 0) {
			oper[0]--;
			solution(number + numbers[idx], oper, idx + 1);
			oper[0]++;
		}
		if (oper[1] > 0) {
			oper[1]--;
			solution(number - numbers[idx], oper, idx + 1);
			oper[1]++;
		}
		if (oper[2] > 0) {
			oper[2]--;
			solution(number * numbers[idx], oper, idx + 1);
			oper[2]++;
		}
		if (oper[3] > 0) {
			oper[3]--;
			solution((int)(number / numbers[idx]), oper, idx + 1);
			oper[3]++;
		}
	}
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		numbers.push_back(tmp);
	}

	for (int i = 0; i < 4; i++) {
		int tmp;
		cin >> tmp;
		oper.push_back(tmp);
	}

	solution(numbers[0], oper, 1);
	cout << max_value << '\n';
	cout << min_value << '\n';

	return 0;
}