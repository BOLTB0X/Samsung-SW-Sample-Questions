#include <iostream>
using namespace std;

int n;
int dp[15] = {0,};
int T[15];
int P[15];

int max(int a, int b) {
	return a > b ? a : b;
}

int solution() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> T[i] >> P[i];
	}
	dp[n] = 0;

	for (int i = n - 1; i >= 0; i--) {
		int next = i + T[i];

		if (next > n)
			dp[i] = dp[i+1];
		else
			dp[i] = max(dp[i+1], dp[next] + P[i]);
	}
	return dp[0];
}

int main(void) {
	cout << solution() << '\n';
	return 0;
}