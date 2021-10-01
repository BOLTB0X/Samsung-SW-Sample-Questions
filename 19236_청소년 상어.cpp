#include <iostream>
#include <vector>

using namespace std;

//물고기들의 정보를 담는 구조체
struct FISH {
	//죽었으면 0, 살아있으면 1
	int y, x, dir, alive;
};

int result;
int board[5][5];
FISH fishs[17];

//이동방향 대각선 포함
const int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
const int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };

//최대
int max(int a, int b) {
	return a > b ? a : b;
}

//맵 복사
void board_backup(int(*from)[5], int(*to)[5]) {
	for (int y = 1; y <= 4; y++) {
		for (int x = 1; x <= 4; x++) {
			to[y][x] = from[y][x];
		}
	}
}

//배열 복사
void fish_backup(FISH *from, FISH *to) {
	for (int i = 1; i <= 16; i++) 
		to[i] = from[i];
}

//물고기들의 좌표를의 스와핑
void arr_swap(int a, int b) {
	FISH tmp = fishs[a];
	fishs[a].y = fishs[b].y;
	fishs[a].x = fishs[b].x;
	fishs[b].y = tmp.y;
	fishs[b].x = tmp.x;
	return;
}

//이동함수
void fishs_move(void) {
	//탐색
	for (int i = 1; i <= 16; i++) {
		if (fishs[i].alive == 0)
			continue;
		//현재 물고기 정보
		int y = fishs[i].y;
		int x = fishs[i].x;
		int dir = fishs[i].dir;

		//이동
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		bool flag = false;

		//범위 내
		if (ny <= 4 && nx <= 4 && ny >= 1 && nx >= 1) {
			//이동 가능한 경우
			if (board[ny][nx] == 0) {
				flag = true;
				fishs[i].y = ny;
				fishs[i].x = nx;
				board[ny][nx] = i;
				//이동했으니 비어있는 공간
				board[y][x] = 0;
			}
			//다른 물고기가 있다면
			else if (board[ny][nx] != -1) {
				flag = true;
				arr_swap(i, board[ny][nx]);
				swap(board[y][x], board[ny][nx]);
			}
		}
		//물고기들이 이동할 수 없을 경우
		if (!flag) {
			//45도 반시계방향 회전
			int nd = dir + 1;
			if (nd == 9)
				nd = 1;
			int ny = y + dy[nd];
			int nx = x + dx[nd];

			//360도로 돌기전까지
			while (nd != dir) {
				//범위 내
				if (ny <= 4 && nx <= 4 && ny >= 1 && nx >= 1) {
					//이동 가능한 경우
					if (board[ny][nx] == 0) {
						fishs[i].y = ny;
						fishs[i].x = nx;
						board[ny][nx] = i;
						//이동했으니 비어있는 공간
						board[y][x] = 0;
						fishs[i].dir = nd;
						break;
					}
					//다른 물고기가 있다면
					else if (board[ny][nx] >= 1) {
						//서로 위치 변경
						arr_swap(i, board[ny][nx]);
						swap(board[ny][nx], board[y][x]);
						fishs[i].dir = nd;
						break;
					}
				}
				nd++;
				if (nd == 9)
					nd = 1;
				ny = y + dy[nd];
				nx = x + dx[nd];
			}
		}
	}
	return;
}

//물고기들 상태
void fish_state(int y, int x, int ny, int nx, int fish_idx, bool flag) {
	if (flag == true) {
		board[y][x] = 0;
		//상어 위치
		board[ny][nx] = -1;
		fishs[fish_idx].alive = 0;
	}
	else {
		board[y][x] = -1;
		//상어 위치 그래도 위치
		board[ny][nx] = fish_idx;
		fishs[fish_idx].alive = 1;
	}
	return;
}

//백트래킹
void DFS(int sy, int sx, int tot, int dir) {
	result = max(result, tot);
	//백업용 
	int c_board[5][5];
	FISH c_fishs[17];
	board_backup(board, c_board);
	fish_backup(fishs, c_fishs);

	//물고기들 이동
	fishs_move();
}

//시뮬레이션
void simulation(void) {
	int shark_idx = board[1][1];
	int shark_dir = fishs[shark_idx].dir;
	fishs[shark_idx].alive = 0;

	board[1][1] = -1;
	DFS(1, 1, shark_idx, shark_dir);
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//물고기들의 정보를 맵과 생선배열에 입력
	for (int y = 1; y <= 4; y++) {
		for (int x = 1; x <= 4; x++) {
			int idx, dir;
			cin >> idx >> dir;
			board[y][x] = idx;
			fishs[idx] = { y,x,dir,1 };
		}
	}
	//result 초기화
	result = 0;
	//시뮬시작
	simulation();

	cout << result << '\n';
	return 0;
}
