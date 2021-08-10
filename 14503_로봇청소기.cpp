#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[51][51];
queue<pair<pair<int, int>, int>> que;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,- 1 };
//방향
//  0
// 3 1
//  2
// 좌회전
int turn_left(int dir) {
	if (dir == 0)
		return 3;
	else if (dir == 3)
		return 2;
	else if (dir == 1)
		return 0;
	else if (dir ==2)
		return 1;
}
//후진
int turn_back(int dir) {
	if (dir == 0)
		return 2;
	else if (dir == 3)
		return 1;
	else if (dir == 1)
		return 3;
	else if (dir == 2)
		return 0;
}
//시뮬레이션 BFS이용
int BFS(int r, int c, int d) {
	que.push({ {r,c},d });
	int result = 1;
	map[r][c] = 2; //1.현재위치 청소
	
	while (!que.empty()) {
		int cur_r = que.front().first.first;
		int cur_c = que.front().first.second;
		int cur_d = que.front().second;
		int tmp_d = cur_d; //방향을 자주 바꿔야 하므로
		que.pop();
		 
		//2.현재 위치에서 현재 방향을 기준으로 왼쪽 방향부터 차례대로 인접한 칸을 탐색
		for (int i = 0; i < 4; i++) {
			//2.b
			tmp_d = turn_left(tmp_d);
			int move_r = cur_r + dr[tmp_d];
			int move_c = cur_c + dc[tmp_d];
			//2.a
			if (0 <= move_r && move_r < n
				&& 0 <= move_c && move_c < m
				&& map[move_r][move_c] == 0) {
				map[move_r][move_c] = 2;
				que.push({ {move_r,move_c},tmp_d });
				result += 1;
				break;
			}
			//2.c
			else if (i == 3) {
				int back_r = cur_r + dr[turn_back(cur_d)];
				int back_c = cur_c + dc[turn_back(cur_d)];
				que.push({ {back_r,back_c},cur_d });
				//2.d
				if (map[back_r][back_c] == 1) {
					return result;
				}
			}
		}
	}
}
int main(void) {
	cin >> n >> m;

	int direction, row, col;
	cin >> row >> col >> direction;

	//맵생성
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			cin >> map[r][c];
		}
	}
	cout << BFS(row, col, direction) << '\n';
	return 0;
}
