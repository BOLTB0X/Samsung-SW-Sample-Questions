#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

//CCTV 정보
typedef struct {
	int y, x, type;
} INF;

int n, m, result;
int map[8][8];
//각 CCTV정보를 담는 배열
INF cctv_arr[8];
int cctv_arr_length = 0;

const int turn_types[5] = { 4,2,4,4,1 };

int min(int a, int b) {
	return a < b ? a : b;
}

//맵 복사
void copy_map(int(*from)[8], int(*to)[8]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = from[i][j];
		}
	}
	return;
}
//방향에 따른 감시영역 업데이트
void update(int dir, INF cctv) {
	//동북서남
	dir = dir % 4;
	//동쪽인 경우
	if (dir == 0) {
		for (int x = cctv.x; x < m; x++) {
			//벽을 만나면
			if (map[cctv.y][x] == 6) 
				break;
			//감시처리
			map[cctv.y][x] = -1;
		}
	}
	//북쪽인 경우
	if (dir == 1) {
		for (int y = cctv.y; y >= 0; y--) {
			//벽을 만나면
			if (map[y][cctv.x] == 6) 
				break;
			//감시처리
			map[y][cctv.x] = -1;
		}
	}
	//서쪽인 경우
	if (dir == 2) {
		for (int x = cctv.x; x >= 0; x--) {
			//벽을 만나면
			if (map[cctv.y][x] == 6) 
				break;
			//감시처리
			map[cctv.y][x] = -1;
		}
	}
	//남쪽인 경우
	if (dir == 3) {
		for (int y = cctv.y; y < n; y++) {
			//벽을 만나면
			if (map[y][cctv.x] == 6) 
				break;
			//감시처리
			map[y][cctv.x] = -1;
		}
	}
}

int get_score() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0)
				cnt++;
		}
	}
	return cnt;
}

//DFS를 이용한 백트래킹
void DFS(int cctv_arr_idx) {
	//탈출조건
	if (cctv_arr_idx == cctv_arr_length) {
		result = min(result, get_score());
		return;
	}
	//재귀로 시뮬레이션을 돌리는 거니 맵 백업이 필요
	int backup_map[8][8];
	int cctv_type = cctv_arr[cctv_arr_idx].type;
	//각 진행방향 for문 시작
	for (int dir = 0; dir < turn_types[cctv_type]; dir++) {
		//기존 맵 백업
		copy_map(map, backup_map);
		//CCTV별 회전방향이 다르므로
		//1번 일 경우
		if (cctv_type == 0) {
			//다시 재귀로 감시범위 업데이트
			update(dir, cctv_arr[cctv_arr_idx]);
		}
		//2번
		if (cctv_type == 1) {
			//다시 재귀로 감시범위 업데이트
			update(dir, cctv_arr[cctv_arr_idx]);
			update(dir+2, cctv_arr[cctv_arr_idx]);
		}
		//3번
		if (cctv_type == 2) {
			//다시 재귀로 감시범위 업데이트
			update(dir, cctv_arr[cctv_arr_idx]);
			update(dir+1, cctv_arr[cctv_arr_idx]);
		}
		//4번
		if (cctv_type == 3) {
			//다시 재귀로 감시범위 업데이트
			update(dir, cctv_arr[cctv_arr_idx]);
			update(dir+1, cctv_arr[cctv_arr_idx]);
			update(dir+2, cctv_arr[cctv_arr_idx]);
		}
		//5번
		if (cctv_type == 4) {
			//다시 재귀로 감시범위 업데이트
			update(dir, cctv_arr[cctv_arr_idx]);
			update(dir+1, cctv_arr[cctv_arr_idx]);
			update(dir+2, cctv_arr[cctv_arr_idx]);
			update(dir+3, cctv_arr[cctv_arr_idx]);
		}
		DFS(cctv_arr_idx + 1);
		copy_map(backup_map, map);
	}
	return;
}

int main(void) {
	//입력
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			//cctv가 입력받으면
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				cctv_arr[cctv_arr_length].y = i;
				cctv_arr[cctv_arr_length].x = j;
				//회전정보배열과 맞춘다.
				cctv_arr[cctv_arr_length].type = map[i][j] - 1;
				cctv_arr_length++;
			}
		}
	}
	//백트래킹 시작
	result = 0x7fffffff;
	DFS(0);
	printf("%d", result);
	return 0;
}
