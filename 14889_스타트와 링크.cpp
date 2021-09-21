#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int n;
int map[21][21];
bool visited[22];
int result = 0x7fffffff;

//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//절댓값
int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}

void DFS(int cnt, int cur) {
	if (cnt == n / 2) {
		int start = 0;
		int link = 0;
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
		result = min(abs(start - link), result);
		return;
	}
	for (int i = cur; i < n; i++) {
		visited[i] = true;
		DFS(cnt + 1, i + 1);
		visited[i] = false;
	}
}

int main(void) {
	scanf("%d", &n);

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &map[y][x]);
		}
	}
	DFS(0, 1);
	printf("%d", result);
	return 0;
}
