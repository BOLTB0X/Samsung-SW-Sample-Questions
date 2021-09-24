#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//물고기 구조체
struct FISH {
	//죽었으면 0, 살아있으면1
	int y, x, dir, alive;
};

int result;
int board[5][5];
FISH fish[17];

//이동방향
const int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
const int dx[9] = { 0, 0,-1,-1,-1,0,1,1,1 };

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
	return;
}

//배열 복사
void fish_backup(FISH* from, FISH* to) {
	for (int i = 1; i <= 16; i++) {
		to[i] = from[i];
	}
	return;
}

//물고기들의 좌표를의 스와핑
void arr_swap(int a, int b) {
	FISH tmp = fish[a];
	fish[a].y = fish[b].y;
	fish[a].x = fish[b].x;
	fish[b].y = tmp.y;
	fish[b].x = tmp.x;
	return;
}

//맵상의 물고기들 이동
void fish_move(void) {
	//배열 탐색
	for (int i = 1; i <= 16; i++) {
		//죽어있다면
		if (fish[i].alive == 0)
			continue;
		//현재 물고기 정보
		int y = fish[i].y;
		int x = fish[i].x;
		int dir = fish[i].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];
		bool flag = false;

		//범위 내
		if (ny <= 4 && nx <= 4 && ny >= 1 && nx >= 1) {
			//이동 가능한 경우
			if (board[ny][nx] == 0) {
				flag = true;
				fish[i].y = ny;
				fish[i].x = nx;
				board[ny][nx] = i;
				//이동했으니 비어있는 공간
				board[y][x] = 0;
			}
			//다른 물고기가 있다면
			else if (board[ny][nx] != -1) {
				flag = true;
				//서로 위치 변경
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
						fish[i].y = ny;
						fish[i].x = nx;
						board[ny][nx] = i;
						//이동했으니 비어있는 공간
						board[y][x] = 0;
						fish[i].dir = nd;
						break;
					}
					//다른 물고기가 있다면
					else if (board[ny][nx] >= 1) {
						//서로 위치 변경
						arr_swap(i, board[ny][nx]);
						swap(board[ny][nx], board[y][x]);
						fish[i].dir = nd;
						break;
					}
				}
				//아닐수 차례로 돌린다.
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
		fish[fish_idx].alive = 0;
	}
	else {
		board[y][x] = -1;
		//상어 위치 그래도 위치
		board[ny][nx] = fish_idx;
		fish[fish_idx].alive = 1;
	}
	return;
}

//백트래킹을 위한 DFS
void DFS(int sy, int sx, int tot, int sdir) {
	result = max(result, tot);
	//백업용
	int c_board[5][5];
	FISH c_fish[17];
	board_backup(board, c_board);
	fish_backup(fish, c_fish);

	//물고기들 이동
	fish_move();
	//상어들 이동
	//고려할 것이 이동하면 물고기를 먹거나 안먹거나
	for (int i = 1; i <= 3; i++) {
		int ny = sy + dy[sdir] * i;
		int nx = sx + dx[sdir] * i;

		//범위 내
		if (ny <= 4 && nx <= 4 && ny >= 1 && nx >= 1) {
			if (board[ny][nx] == 0) continue;
			int fish_idx = board[ny][nx];
			int nd = fish[fish_idx].dir;

			//상어가 이동하며 먹는 경우와 안먹는 경우
			fish_state(sy, sx, ny, nx, fish_idx, true);
			DFS(ny, nx, tot + fish_idx, nd);
			fish_state(sy, sx, ny, nx, fish_idx, false);
		}
		else
			break;
	}
	board_backup(c_board, board);
	fish_backup(c_fish, fish);
}

//시뮬레이션 시작
void simulation(void) {
	//상어는 무조건 초기 (1,1)
	//방향은 잡아먹은 물고기 방향
	result = 0;
	int shark_idx = board[1][1];
	int shark_dir = fish[shark_idx].dir;
	fish[shark_idx].alive = 0;
	//상어는 -1로
	board[1][1] = -1;
	//백트래킹 시작
	DFS(1, 1, shark_idx, shark_dir);
	return;
}

int main(void) {
	//물고기 정보를 맵에 입력
	for (int y = 1; y <= 4; y++) {
		for (int x = 1; x <= 4; x++) {
			int idx, dir;
			scanf("%d %d", &idx, &dir);
			//맵에 해당 물고기 번호 삽입
			board[y][x] = idx;
			//배열에 물고기 정보입력
			fish[idx] = { y,x,dir,1 };
		}
	}
	simulation();
	printf("%d\n", result);
	return 0;
}
