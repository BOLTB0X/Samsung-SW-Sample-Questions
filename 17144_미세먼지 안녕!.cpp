#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

struct INF {
	int y, x;
};

int n, m, T;
int map[50][50];
int tmp_map[50][50];

//공기청정기 위치를 잡는 배열
INF clean[2];
//서남동북
const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,1,0,-1 };

//맵 복사
void map_copy(int(*from)[50], int(*to)[50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = from[i][j];
		}
	}
}

//양 측정
int get_score(void) {
	int tot = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] >= 1)
				tot += map[y][x];
		}
	}
	return tot;
}

//미세먼지 확산
void diffusion(void) {
	map_copy(map,tmp_map);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			//먼지 기준은 초기 맵
			//tmp_map으로 확산시 퍼진 것도 포함하게 됨
			//즉 원래 기준으로 퍼지는 먼지 기준이 뒤섞임
			if (map[y][x] != 0 && map[y][x] != -1) {
				//이동방향으로 확산
				int d = map[y][x] / 5;
				//퍼져나간 횟수
				int move_cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m)
						continue;
					if (map[ny][nx] == -1)
						continue;
					tmp_map[ny][nx] += d;
					move_cnt++;
				}
				//문제조건
				tmp_map[y][x] -= (d * move_cnt);
			}
		}
	}
	//임시맵을 다시 맵으로 복사
	map_copy(tmp_map, map);
}

//스타트
void clean_start(void) {
	for (int idx = 0; idx < 2; idx++) {
		//반시계
		if (idx == 0) {
			//행 위에서부터 0까지
			for (int i = clean[idx].y - 1; i > 0; i--) {
				map[i][0] = map[i - 1][0];
			}
			// 열 윗줄 한칸식 회전
			for (int i = 0; i < m - 1; i++) {
				map[0][i] = map[0][i + 1];
			}
			// 열 윗줄 뒤집은 방향 
			for (int i = 1; i<= clean[idx].y;i++) {
				map[i-1][m-1] = map[i][m-1];
			}
			//행 위에서부터 0까지 뒤집은 방향
			for (int i = m - 1; i > 1; i--) {
				map[clean[idx].y][i] = map[clean[idx].y][i - 1];
			}
			map[clean[idx].y][1] = 0;
		}
		//시계방향
		else {
			for (int i = clean[idx].y + 1; i < n - 1; i++) {
				map[i][0] = map[i + 1][0];
			}
			for (int i = 0; i < m - 1; i++) {
				map[n - 1][i] = map[n - 1][i + 1];
			}
			for (int i = n - 1; i >= clean[idx].y; i--) {
				map[i][m - 1] = map[i - 1][m - 1];
			}
			for (int i = m - 1; i > 1; i--) {
				map[clean[idx].y][i] = map[clean[idx].y][i-1];
			}
		}
		map[clean[idx].y][1] = 0;
	}
	return;
}

int simulation(void) {
	for (int i = 0; i < T; i++) {
		diffusion();
		clean_start();
	}
	int result = get_score();
	return result;
}

int main(void) {
	scanf("%d %d %d", &n, &m, &T);
	int idx = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
			//공기청정기일 경우
			if (map[y][x] == -1) {
				clean[idx] = { y,x };
				idx++;
			}
		}
	}
	int ret = simulation();
	printf("%d", ret);
	return 0;
}