#include <iostream>
using namespace std;

int n;
int arr[11];
int max_value = -1000000000;
int min_value = 1000000000;

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void DFS(int add, int sub, int mul, int div, int tmp_value, int cnt) {
	if (cnt == n) {
		max_value = max(max_value, tmp_value);
		min_value = min(min_value, tmp_value);
		return;
	}
	else {
		if (add > 0) {
			DFS(add - 1, sub, mul, div, tmp_value + arr[cnt],cnt + 1);
		}
		if (sub > 0) {
			DFS(add, sub-1, mul, div, tmp_value - arr[cnt], cnt + 1);
		}
		if (mul > 0) {
			DFS(add, sub, mul-1, div, tmp_value * arr[cnt], cnt + 1);
		}
		if (div > 0) {
			DFS(add, sub, mul, div-1, (int)tmp_value / arr[cnt], cnt + 1);
		}

	}
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	
	int add, sub, mul, div;
	cin >> add >> sub >> mul >> div;
	DFS(add, sub, mul, div, arr[0], 1);

	cout << max_value << '\n' << min_value << '\n';
	return 0;
}
