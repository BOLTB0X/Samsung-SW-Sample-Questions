#include <iostream>
using namespace std;

typedef struct {
	int y, x, type;
} INF;

int n, m, result;
int map[8][8];
INF cctvs[8];
int cctv_size;

const int angle_types[5] = { 4,2,4,4,1 };

//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//맵 복사
void map_copy(int(*from)[8], int(*to)[8]) {
	for (int c = 0; c < n; c++)
		for (int r = 0; r < m; r++)
			to[c][r] = from[c][r];
	return;
}

//카메라 타입,각도에 따른 시뮬레이션
void simulation(int dir, INF cctv) {
	dir = (dir % 4);

	if (dir == 0) {
		for (int x = cctv.x; x < m; x++) {
			if (map[cctv.y][x] == 6)
				break;
			map[cctv.y][x] = -1; //감시처리
		}
	}
	if (dir == 1) {
		for (int y = cctv.y; y >= 0; y--) {
			if (map[y][cctv.x] == 6)
				break;
			map[y][cctv.x] = -1; //감시처리
		}
	}
	if (dir == 2) {
		for (int x = cctv.x; x >= 0; x--) {
			if (map[cctv.y][x] == 6)
				break;
			map[cctv.y][x] = -1; //감시처리
		}
	}
	if (dir == 3) {
		for (int y = cctv.y; y < n; y++) {
			if (map[y][cctv.x] == 6)
				break;
			map[y][cctv.x] = -1; //감시처리
		}
	}
	return;
}

//DFS를 이용한 백트래킹
void DFS(int cctv_idx) {
	//재귀 탈출 조건
	if (cctv_idx == cctv_size) {
		int tmp_result = 0;
		for (int c = 0; c < n; c++) {
			for (int r = 0; r < m; r++) {
				if (map[c][r] == 0)
					tmp_result++;
			}
		}
		result = min(tmp_result, result);
		return;
	}
	//맵 복사용
	int backup[8][8];
	int cctv_type = cctvs[cctv_idx].type;
	//cctv종류따른 앵글각도
	for (int dir = 0; dir < angle_types[cctv_type]; dir++) {
		//맵복사
		map_copy(map, backup);
		if (cctv_type == 0) {
			simulation(dir, cctvs[cctv_idx]);
		}
		if (cctv_type == 1) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
		}
		if (cctv_type == 2) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
		}
		if (cctv_type == 3) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
		}
		if (cctv_type == 4) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
			simulation(dir + 3, cctvs[cctv_idx]);
		}
		DFS(cctv_idx + 1);
		map_copy(backup, map);
	}
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n >> m;
	for (int c = 0; c < n; c++) {
		for (int r = 0; r < m; r++) {
			cin >> map[c][r];
			if (map[c][r] >= 1 && map[c][r] <= 5) {
				cctvs[cctv_size].y = c;
				cctvs[cctv_size].x = r;
				cctvs[cctv_size].type = map[c][r] - 1;
				cctv_size++;
			}
		}
	}
	//최소 값을 위해 최대값 설정
	result = 0x7fffffff;
	//백트래킹 
	DFS(0);
	cout << result << '\n';
	return 0;
}
