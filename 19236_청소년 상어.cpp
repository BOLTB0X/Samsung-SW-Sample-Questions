#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//물고기 자료형
struct FISH {
	int y, x, dir, alive; //1 살아있음, 0 죽음
};

int map[4][4];
FISH fish[17];

//이동방향
const int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
const int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int result;

//최대
int max(int a, int b) {
	return a > b ? a : b;
}

//맵 복사
void map_backup(int(*from)[4], int(*to)[4]) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}

//배열 복사
void arr_backup(FISH* from, FISH* to) {
	for (int i = 1; i <= 16; i++) {
		to[i] = from[i];
	}
	return;
}

//물고기들의 좌표를의 스와핑
void fish_swap(int a, int b) {
	FISH tmp = fish[a];
	fish[a].y = fish[b].y;
	fish[a].x = fish[b].x;
	fish[b].y = tmp.y;
	fish[b].x = tmp.x;
	return;
}

//물고기들의 이동 
void move_fish(void) {
	//물고기들 작은 순번부터
	for (int i = 1; i <= 16; i++) {
		//죽었다면
		if (fish[i].alive == 0)
			continue;
		int y = fish[i].y;
		int x = fish[i].x;
		int dir = fish[i].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];
		bool flag = false;
		//범위 내고
		if (ny >= 0 && nx >= 0 && ny < 4 && nx < 4) {
			//이동 가능 하면
			if (map[ny][nx] == 0) {
				flag = true;
				fish[i].y = ny;
				fish[i].x = nx;
				map[ny][nx] = i;
				map[y][x] = 0;
			}
			//다른 물고기가 있으면
			else if (map[ny][nx] != -1) {
				flag = true;
				fish_swap(i, map[ny][nx]);
				swap(map[y][x], map[ny][nx]);
			}
		}
		//여기까지 와서 flag가 거짓인 경우
		//물고기들은 현재방향으로 진행불능
		if (flag==false) {
			int nd = dir + 1;
			if (nd == 9)
				nd = 1;
			int ny = y + dy[nd];
			int nx = x + dx[nd];

			while (nd != dir) {
				if (ny >= 0 && nx >= 0 && ny < 4 && nx < 4) {
					if (map[ny][nx] == 0) {
						fish[i].y = ny;
						fish[i].x = nx;
						map[ny][nx] = i;
						map[y][x] = 0;
						fish[i].dir = nd;
						break;
					}
					else if (map[ny][nx] != -1) {
						fish_swap(i, map[ny][nx]);
						swap(map[y][x], map[ny][nx]);
						fish[i].dir = nd;
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
}

//물고기들 상태
void fish_state(int y, int x, int ny, int nx, int fish_idx, bool flag) {
	if (flag == true) {
		map[y][x] = 0;
		//상어 위치
		map[ny][nx] = -1;
		fish[fish_idx].alive = 0;
	}
	else {
		map[y][x] = -1;
		//상어 위치 그래도 위치
		map[ny][nx] = fish_idx;
		fish[fish_idx].alive = 1;
	}
	return;
}

//상어로 백트래킹
void DFS(int shark_y, int shark_x, int tot, int shark_dir) {
	result = max(result, tot);
	//백트래킹이므로 tmp선언
	int c_map[4][4];
	FISH c_fish[17];
	//백업시켜두기
	map_backup(map, c_map);
	arr_backup(fish, c_fish);
	
	//물고기들 이동
	move_fish();

	//상어 이동
	for (int i = 1; i <= 3; i++) {
		int ny = shark_y + dy[shark_dir] * i;
		int nx = shark_x + dx[shark_dir] * i;

		if (ny >= 0 && nx >= 0 && ny < 4 && nx < 4) {
			if (map[ny][nx] == 0)
				continue;
			int fish_idx = map[ny][nx];
			int nd = fish[fish_idx].dir;

			//상어가 이동하며 먹은 경우와 안먹은 경우
			fish_state(shark_y, shark_x, ny, nx, fish_idx, true);
			DFS(ny, nx, tot + fish_idx, nd);
			fish_state(shark_y, shark_x, ny, nx, fish_idx, false);
		}
		else
			break;
	}
	map_backup(c_map, map);
	arr_backup(c_fish, fish);
}

//시뮬
void simulation(void) {
	//초기 상어가 (0,0)물고기 잡아먹음
	int fish_idx = map[0][0];
	int fish_dir = fish[fish_idx].dir;
	fish[fish_idx].alive = 0;
	//상어 위치 
	map[0][0] = -1; 
	//백트래킹 
	DFS(0, 0, fish_idx, fish_dir);
	return;
}
int main(void) {
	//물고기 정보 입력
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int idx, dir;
			scanf("%d %d", &idx, &dir);
			map[y][x] = idx;
			fish[idx] = { y,x,dir,1 };
		}
	}
	simulation();
	printf("%d\n", result);
	return 0;
}
