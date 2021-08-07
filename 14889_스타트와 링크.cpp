#include <iostream>
#include <math.h>
using namespace std;

int n;
int map[21][21];
bool visited[22];
int min_value = 0x7fffffff;

void DFS(int cnt, int cur) {
	if (cnt == n/2) {
		int start=0;
		int link=0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (visited[i] && visited[j]) {
					start += map[i][j];
				}
				if (!visited[i] && !visited[j]) {
					link += map[i][j];
				}
			}
		}
		min_value = min(abs(start - link), min_value);
		return;
	}
	for (int i = cur; i < n; i++) {
		visited[i] = true;
		DFS(cnt + 1, i+1);
		visited[i] = false;
	}
}

int main(void) {
	cin >> n;

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> map[y][x];
		}
	}
	DFS(0, 1);
	cout << min_value << '\n';
	return 0;
}