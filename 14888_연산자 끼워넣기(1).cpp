#include <iostream>
using namespace std;

int n;
int numbers[101] = { 0, };
int max_value = -1000000001;
int min_value = 1000000001;

int max(int value1, int value2) {
	return value1 > value2 ? value1 : value2;
}

int min(int value1, int value2) {
	return value1 < value2 ? value1 : value2;
}

void DFS(int number, int idx, int add, int sub, int mul, int div) {
	if (idx == n) {
		max_value = max(number, max_value);
		min_value = min(number, min_value);
		return;
	}

	else {
		if (add > 0) {
			DFS(number + numbers[idx], idx + 1, add - 1, sub, mul, div);
		}
		if (sub > 0) {
			DFS(number - numbers[idx], idx + 1, add, sub-1, mul, div);
		}
		if (mul > 0) {
			DFS(number * numbers[idx], idx + 1, add, sub, mul-1, div);
		}
		if (div > 0) {
			DFS((int)(number / numbers[idx]), idx + 1, add, sub, mul, div-1);
		}
	}
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	}
	
	int add, sub, mul, div;

	cin >> add >> sub >> mul >> div;

	DFS(numbers[0], 1, add, sub, mul, div);

	cout << max_value << '\n';
	cout << min_value << '\n';

	return 0;
}