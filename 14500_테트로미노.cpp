#include <iostream>
#include <cstring>

using namespace std;

int n, m, result;
int board[501][501];
bool visited[501][501] = { false, };

const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//최대
int max(int a, int b) {
	return a > b ? a : b;
}

//입력
void input(void) {
	cin >> n >> m;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < m; ++x) {
			cin >> board[y][x];
		}
	}
}

//ㅜ모양 회전하면서 찾기
void find_special_shape(int y, int x) {
	// ㅜ
	if (y + 1 < n && x + 2 < m)
		result = max(result, board[y][x] + board[y][x + 1] + board[y][x + 2] + board[y + 1][x + 1]);
	// ㅏ
	if (y + 2 < n && x + 1 < m)
		result = max(result, board[y][x] + board[y + 1][x] + board[y + 1][x + 1] + board[y + 2][x]);
	// ㅗ
	if (y - 1 >= 0 && x + 2 < m)
		result = max(result, board[y][x] + board[y][x + 1] + board[y][x + 2] + board[y - 1][x + 1]);
	// ㅓ
	if (y + 2 < n && x - 1 >= 0)
		result = max(result , board[y][x] + board[y + 1][x] + board[y + 1][x - 1] + board[y + 2][x]);
}

//나머지 모양 다 깊이가 3임
void find_normal_shape(int y, int x, int tot, int depth) {
	if (depth == 3) {
		result = max(result, tot);
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= m)
			continue;
		if (visited[ny][nx])
			continue;
		visited[ny][nx] = true;
		find_normal_shape(ny, nx, tot + board[ny][nx], depth + 1);
		visited[ny][nx] = false;
	}
}

//모양 찾기
void find_shape(int y, int x) {
	find_special_shape(y, x);

	visited[y][x] = true;
	find_normal_shape(y, x, board[y][x], 0);
	visited[y][x] = false;
}

//시뮬
void simulation(void) {
	result = -1;
	//입력
	input();
	//탐색 시작
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < m; ++x) {
			memset(visited, false, sizeof(visited));
			find_shape(y, x);
		}
	}
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//시뮬레이션
	simulation();
	cout << result << '\n';
	return 0;
}