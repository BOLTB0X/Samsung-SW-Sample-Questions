#include <iostream>
#include <queue>
using namespace std;

int n, m;
queue<pair<pair<int, int>, int>> que;
int map[50][50];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

//좌회전
int turn_left(int d) {
	if (d == 0)
		return 3;
	else if (d == 1)
		return 0;
	else if (d == 2)
		return 1;
	else if (d == 3)
		return 2;
}
//후진 
int turn_back(int d) {
	if (d == 0)
		return 2;
	else if (d == 1)
		return 3;
	else if (d == 2)
		return 0;
	else if (d == 3)
		return 1;
}

int BFS(int r, int c, int d) {
	int ret = 1;
	//1.현재 위치를 청소
	map[r][c] = 2; //청소처리
	que.push({ {r, c}, d });

	while (!que.empty()) {
		int cur_r = que.front().first.first;
		int cur_c = que.front().first.second;
		int cur_d = que.front().second;
		int tmp_d = cur_d;
		que.pop();

		//2.왼쪽방향부터 차례대로 탐색
		for (int i = 0; i < 4; i++) {
			//2.b 조건
			tmp_d = turn_left(tmp_d);
			int move_r = cur_r + dy[tmp_d];
			int move_c = cur_c + dx[tmp_d];

			//2.a 조건
			if (0 <= move_c && move_c < m && 0 <= move_r && 
				move_r < n && map[move_r][move_c] == 0) {
				ret += 1;
				map[move_r][move_c] = 2; //1.현재 위치 청소
				que.push({ {move_r, move_c}, tmp_d });
				break;
			}
			//2.c 조건
			else if (i == 3) {
				int move_r = cur_r + dy[turn_back(cur_d)];
				int move_c = cur_c + dx[turn_back(cur_d)];
				que.push({ {move_r, move_c}, cur_d });
				//2.d 조건
				if (map[move_r][move_c] == 1)
					return ret;
			}
		}
	}
}

int main() {
	//입력
	cin >> n >> m;
	int row, col, dir;
	cin >> row >> col >> dir;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cin >> map[i][j];
	}

	cout << BFS(row, col, dir) << '\n';
	return 0;
}
