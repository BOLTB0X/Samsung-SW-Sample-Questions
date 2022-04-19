#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int result = 1e9; // 최소를 위한
int N, M, K;
int board[50][50];
int cboard[50][50];
int cmd[6][3];
bool visited[6];
vector<int> per;

// 동서남북
const int dy[4] = { 0, 0, 1, -1 };
const int dx[4] = { 1, -1, 0,0 };

int Min(int a, int b) {
	return a < b ? a : b;
}

int turn_dir(int dir) {
	if (dir == 0)
		return 3;
	else if (dir == 1)
		return 2;
	else if (dir == 2)
		return 0;
	else if (dir == 3)
		return 1;
}

void board_rotate(int sy, int sx, int ey, int ex) {
	int max_cnt = (ex - sx) / 2;

	for (int cnt = 0; cnt < max_cnt; ++cnt) {
		int y = sy, x = sx;
		int tmp = board[y][x];
		int d = 2;

		while (1) {
			int ny = y + dy[d];
			int nx = x + dx[d];

			if (ny == sy && nx == sx) {
				board[y][x] = tmp;
				break;
			}

			if (sy <= ny && ny <= ey - cnt && sx <= nx && nx <= ex - cnt) {
				board[y][x] = board[ny][nx];
				y = ny, x = nx;
			}

			else 
				d = turn_dir(d);
		}
		sy++;
		sx++;
	}

	return;
}

void simulation(void) {
	for (int i = 0; i < K; ++i) {
		int idx = per[i];
		int sy = cmd[idx][0] - cmd[idx][2] - 1;
		int sx = cmd[idx][1] - cmd[idx][2] - 1;

		int ey = cmd[idx][0] + cmd[idx][2] - 1;
		int ex = cmd[idx][1] + cmd[idx][2] - 1;

		board_rotate(sy, sx, ey, ex);
	}

	int min_value = 1e9;
	for (int i = 0; i < N; ++i) {
		int tot = 0;
		for (int j = 0; j < M; ++j)
			tot += board[i][j];

		min_value = Min(min_value, tot);
	}

	result = Min(result, min_value);
	return;
}

// 순열
void DFS(int level) {
	if (level == K) {
		memcpy(cboard, board, sizeof(board));
		simulation();
		memcpy(board, cboard, sizeof(cboard));
		return;
	}

	for (int i = 0; i < K; ++i) {
		if (visited[i])
			continue;
		visited[i] = 1;
		per.push_back(i);
		DFS(level + 1);
		per.pop_back();
		visited[i] = 0;
	}

	return;
}

int solution(void) {
	int answer = 0;

	DFS(0);
	answer = result;
	return answer;
}

int main(void) {
	cin >> N >> M >> K;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			cin >> board[i][j];
	}

	for (int i = 0; i < K; ++i)
		cin >> cmd[i][0] >> cmd[i][1] >> cmd[i][2];

	int ret = solution();
	cout << ret;
	return 0;
}