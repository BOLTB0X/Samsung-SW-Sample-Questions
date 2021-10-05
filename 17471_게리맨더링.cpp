#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int arr[11], A[11][11];
bool visited[11];

int min(int a, int b) {
	return a < b ? a : b;
}

int DFS(int v, vector<int>& per, int type) {
	int cnt = 1;
	visited[v] = true;

	for (int i = 1; i <= n; i++) {
		if (per[i - 1] == type && A[v][i] == 1 && visited[i] == false)
			cnt += DFS(i, per, type);
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	for (int i = 1, m; i <= n; i++) {
		cin >> m;
		for (int j = 0, v; j < m; j++) {
			cin >> v;
			A[i][v] = 1;
		}
	}
	int ans = 987654321;
	for (int k = 1; k <= n - 1; k++) {
		vector<int> per(k, 0);
		for (int i = k + 1; i <= n; i++)
			per.push_back(1);

		do {
			int area0_idx = -1, area1_idx = -1;
			for (int i = 0; i < n; i++) {
				if (per[i] == 0) 
					area0_idx = i;
				else 
					area1_idx = i;

				if (area0_idx != -1 && area1_idx != -1)
					break;
			}
			int a0_cnt, a1_cnt, res0, res1;
			a0_cnt = a1_cnt = res0 = res1 = 0;

			memset(visited, 0, sizeof(visited));
			a0_cnt = DFS(area0_idx + 1, per, 0);
			memset(visited, 0, sizeof(visited));
			a1_cnt = DFS(area1_idx + 1, per, 1);

			if (a0_cnt == k && a1_cnt == n - k) {
				for (int i = 0; i < n; i++) {
					if (per[i] == 0) 
						res0 += arr[i + 1];
					else res1 += arr[i + 1];
				}

				int sub = abs(res0 - res1);
				if (ans > sub)
					ans = sub;
			}
		} while (next_permutation(per.begin(), per.end()));
	}
	if (ans == 987654321)
		cout << -1 << '\n';
	else
		cout << ans << '\n';
	return 0;
}