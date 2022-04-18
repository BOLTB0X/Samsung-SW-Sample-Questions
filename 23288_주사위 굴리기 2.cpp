#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int board[21][21];
int dice[7] = { 0,1,2,3,4,5,6 };

// �� �� �� ��
const int dx[5] = { 0, 0, 0, 1, -1 };
const int dy[5] = { 0, 1, -1, 0, 0 };

// �ݴ����
int reverse_dir(int d) {
	if (d == 1)
		return 2;

	else if (d == 2)
		return 1;

	else if (d == 3)
		return 4;

	else if (d == 4)
		return 3;
}

// �ð� ����
int turn_right(int d) {
	// �� -> ��
	if (d == 1)
		return 3;

	// �� -> ��
	else if (d == 2)
		return 4;
	
	// �� -> ��
	else if (d == 3)
		return 2;
	
	// �� -> ��
	else if (d == 4)
		return 1;
}

// �ݽð� ����
int turn_left(int d) {
	// �� -> ��
	if (d == 1)
		return 4;

	// �� -> ��
	else if (d == 2)
		return 3;
	
	// �� -> ��
	else if (d == 3)
		return 1;
	
	// �� -> ��
	else if (d == 4)
		return 2;
}


void dice_rolling(int dir) {
	int tmp = dice[1];

	// ��
	if (dir == 1) {
		dice[1] = dice[4];
		dice[4] = dice[6];
		dice[6] = dice[3];
		dice[3] = tmp;
	}

	// ��
	else if (dir == 2) {
		dice[1] = dice[3];
		dice[3] = dice[6];
		dice[6] = dice[4];
		dice[4] = tmp;
	}

	// ��
	else if (dir == 3) {
		dice[1] = dice[2];
		dice[2] = dice[6];
		dice[6] = dice[5];
		dice[5] = tmp;
	}

	// ��
	else if (dir == 4) {
		dice[1] = dice[5];
		dice[5] = dice[6];
		dice[6] = dice[2];
		dice[2] = tmp;
	}

	return;
}

// �ʺ�켱Ž��
int BFS(int n, int m, int x, int y) {
	queue<pair<int,int>> que;
	bool visited[21][21];
	int step = 1;

	memset(visited, 0, sizeof(visited)); 
	que.push({ x,y });
	visited[x][y] = 1;

	while (!que.empty()) {
		int cx = que.front().first;
		int cy = que.front().second;
		que.pop();

		for (int dir = 1; dir <= 4; ++dir) {
			int nx = cx + dx[dir];
			int ny = cy + dy[dir];

			if (ny < 1 || nx < 1 || ny > m || nx > n)
				continue;

			if (visited[nx][ny] == 1)
				continue;

			if (board[x][y] != board[nx][ny])
				continue;

			visited[nx][ny] = 1;
			step++;
			que.push({ nx,ny });
		}
	}
	return step;
}

int solution(int n, int m, int k) {
	int answer = 0;
	int x = 1, y = 1, d = 1;
	int step = 0, A = 0, B = 0;

	for (int i = 0; i < k; ++i) {
		// 1��
		int nx = x + dx[d];
		int ny = y + dy[d];

		// ������ �Ѿ��
		if (nx < 1 || ny < 1 || nx > n || ny > m) {
			d = reverse_dir(d);
			nx = x + dx[d];
			ny = y + dy[d];
		}

		// 2��
		B = board[nx][ny];
		step = BFS(n, m, nx, ny);
		answer += (step * B); // ��������

		// 3��
		dice_rolling(d);
		A = dice[6];

		if (A > B)
			d = turn_right(d);
		else if (A < B)
			d = turn_left(d);
	
		x = nx, y = ny;
	}

	return answer;
}

int main(void) {
	int n, m, k;

	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			cin >> board[i][j];
	}

	int ret = solution(n, m, k);
	cout << ret;
	return 0;
}