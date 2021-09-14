#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	int y, x, type;
} INF;

int n, m,result;
int map[8][8];
INF cctvs_arr[8];
int cctvs_size = 0;
//각 cctv별 회전 가지 수
const int turn_type[5] = { 4,2,4,4,1 };

int min(int a, int b) {
	return a < b ? a : b;
}

void map_copy(int(*from)[8], int(*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}
//회전의 따른 감시범위 체크
void simulation(int dir, INF cctv) {
	//동 서 북 남 (동 북) (서 남)
	dir = (dir % 4);
	//동
	if (dir == 0) {
		for (int x = cctv.x; x < m; x++) {
			//벽을 만나면 
			if (map[cctv.y][x] == 6)
				break;
			//감시처리
			map[cctv.y][x] = -1;
		}
	}
	//서
	if (dir == 1) {
		for (int y = cctv.y; y >=0; y--) {
			//벽을 만나면 
			if (map[y][cctv.x] == 6)
				break;
			//감시처리
			map[y][cctv.x] = -1;
		}
	}
	//남
	if (dir == 2) {
		for (int x = cctv.x; x >= 0; x--) {
			//벽을 만나면 
			if (map[cctv.y][x] == 6)
				break;
			//감시처리
			map[cctv.y][x] = -1;
		}
	}
	//북
	if (dir == 3) {
		for (int y = cctv.y; y < n; y++) {
			//벽을 만나면 
			if (map[y][cctv.x] == 6)
				break;
			//감시처리
			map[y][cctv.x] = -1;
		}
	}
	return;
}

//안전갯수 찾기
int get_score() {
	int cnt=0;
	for (int y = 0; y < n; y++) 
		for (int x = 0; x < m; x++) 
			if (map[y][x] == 0)
				cnt++;
	return cnt;
}

//DFS를 이용한 백트래킹
void DFS(int cctvs_idx) {
	//탈출조건
	if (cctvs_idx == cctvs_size) {
		result = min(result, get_score());
		return;
	}
	//백업용 임시맵
	int backup_map[8][8];
	//배열에 담긴 cctv종류
	int cctv_type = cctvs_arr[cctvs_idx].type;
	//cctv의 회전가지를 담은 배열의 길이만큼 탐색시작
	for (int dir = 0; dir < turn_type[cctv_type]; dir++) {
		map_copy(map, backup_map);
		//1번 카메라인 경우
		if (cctv_type == 0) {
			simulation(dir, cctvs_arr[cctvs_idx]);
		}
		//2번 카메라인 경우
		if (cctv_type == 1) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
		}
		//3번 카메라인 경우
		if (cctv_type == 2) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
		}
		//3번 카메라인 경우
		if (cctv_type == 3) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
		}
		//3번 카메라인 경우
		if (cctv_type == 4) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
			simulation(dir + 3, cctvs_arr[cctvs_idx]);
		}
		DFS(cctvs_idx + 1);
		map_copy(backup_map, map);
	}
	return;
}

int main(void) {
	//맵 입력
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
			//cctv가 입력받으면
			if (map[y][x] >= 1 && map[y][x] <= 5) {
				cctvs_arr[cctvs_size].y = y;
				cctvs_arr[cctvs_size].x = x;
				//cctv번호 회전배열과 맞추기 위해
				cctvs_arr[cctvs_size].type = map[y][x] - 1;
				cctvs_size++;
			}
		}
	}
	//백트래킹 시작
	result = 0x7fffffff;
	DFS(0);
	printf("%d", result);
	return 0;
}