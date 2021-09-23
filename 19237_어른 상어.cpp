#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <vector>
#include <algorithm>

using namespace std; 

//상어 정의
struct SHARK { 
	int y; 
	int x; 
	int dir; 
	vector<int> priority[5]; 
	int alive; 
}; 

//맵의 한 블록
struct BLOCK { 
	vector<int> v;
	int smell_time;
	int smell_host;
}; 

int n, m, k; 
SHARK sharks[401]; 
BLOCK sea[21][21]; 

//이동방향
const int dy[5] = { 0,-1, 1, 0, 0 };
const int dx[5] = { 0,0, 0, -1, 1 };

//범위 내
bool check_range(int y, int x) {
	if (y >= 0 && x >= 0 && y < n && x < n)
		return true;
	return false;
}

bool check(void) {
	for (int i = 2; i <= m; i++) {
		if (sharks[i].alive == 1)
			return false;
	}
	return true;
}

void set_smell(int t) {
	for (int i = 1; i <= m; i++) {
		if (sharks[i].alive == 0)
			continue;

		int y = sharks[i].y;
		int x = sharks[i].x;
		sea[y][x].smell_time = t + k;
		sea[y][x].smell_host = i;
	}
	return;
}

void move_shark(int t) {
	//초기화
	for (int i = 1; i <= m; i++) {
		if (sharks[i].alive == 0)
			continue;
		int y = sharks[i].y;
		int x = sharks[i].x;
		sea[y][x].v.clear();
	}
	for (int i = 1; i <= m; i++) {
		if (sharks[i].alive == 0)
			continue;
		int y = sharks[i].y;
		int x = sharks[i].x;
		int dir = sharks[i].dir;
		int self_y, self_x, self_d;
		self_y = self_x = self_d = -1;
		bool flag = false;

		for (int j = 0; j < sharks[i].priority[dir].size(); j++) {
			int nd = sharks[i].priority[dir][j];
			int ny = y + dy[nd];
			int nx = x + dx[nd];

			if (check_range(ny, nx)) {
				if (sea[ny][nx].smell_time <= t) {
					flag = true;
					sea[ny][nx].v.push_back(i);
					sharks[i].y = ny;
					sharks[i].x = nx;
					sharks[i].dir = nd;
					break;
				}
				else {
					if (sea[ny][nx].smell_host == i) {
						if (self_y == -1) {
							self_y = ny;
							self_x = nx;
							self_d = nd;
						}
					}
				}
			}
		}
		if (flag == false) {
			sea[self_y][self_x].v.push_back(i);
			sharks[i].y = self_y;
			sharks[i].x = self_x;
			sharks[i].dir = self_d;
		}
	}
}

void eating(void) {
	for (int i = 1; i <= m; i++) {
		if (sharks[i].alive == 0) 
			continue;

		int y = sharks[i].y;
		int x = sharks[i].x;
		if (sea[y][x].v.size() >= 2) {
			sort(sea[y][x].v.begin(), sea[y][x].v.end());
			int alive_idx = sea[y][x].v[0];
			for (int j = 1; j < sea[y][x].v.size(); j++) {
				int shark_idx = sea[y][x].v[j];
				sharks[shark_idx].alive = 0;
			}
			sea[y][x].v.clear();
			sea[y][x].v.push_back(alive_idx);
			sea[y][x].smell_host = alive_idx;
		}
	}
}

void simulation(void) {
	for (int t = 0; t <= 1000; t++) {
		if (check()) {
			printf("%d\n", t);
			return;
		}
		set_smell(t);
		move_shark(t);
		eating();
	}
	printf("-1\n");
	return;
}

int main(void) {
	//맵 정보 입력
	scanf("%d %d %d", &n, &m, &k);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			int shark_idx;
			scanf("%d", &shark_idx);
			if (shark_idx > 0) {
				sea[y][x].v.push_back(shark_idx);
				sharks[shark_idx].y = y;
				sharks[shark_idx].x = x;
			}
			sea[y][x].smell_time = 0;
			sea[y][x].smell_host = 0;
		}
	}
	//각 상어들의 방향 우선순위 입력
	for (int i = 1; i <= m; i++) {
		int dir;
		scanf("%d", &dir);
		sharks[i].dir = dir;
		sharks[i].alive = 1;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= 4; j++) {
			int a[4];
			scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);	
			for (int k = 0; k < 4; k++) 
				sharks[i].priority[j].push_back(a[k]);
		}
	}
	simulation();
	return 0;
}