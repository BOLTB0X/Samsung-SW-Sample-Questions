#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[8][8];
int tmp_map[8][8];
int virus_map[8][8];
int result = 0;

int max(int value1, int value2) {
	return value1 > value2 ? value1 : value2;
}

void copy_map(int(*from)[8], int(*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
}

int get_score() {
	int score = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (virus_map[y][x] == 0) {
				score += 1;
			}
		}
	}
	return score;
}

//바이러스 확산 함수
void virus() {
	copy_map(tmp_map, virus_map);
	queue<pair<int, int>>  que;

	//바이러스 위치 찾기
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (virus_map[y][x] == 2) {
				que.push({ y,x });
			}
		}
	}
	
	int dy[4] = { -1, 0, 1, 0 };
	int dx[4] = { 0, 1, 0, -1 };

	while (!que.empty()) {
		int cur_y = que.front().first;
		int cur_x = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cur_y + dy[i];
			int nx = cur_x + dx[i];

			if (0 <= ny && ny < n && 0 <= nx && nx < m) {
				if (virus_map[ny][nx] == 0) {
					virus_map[ny][nx] = 2;
					que.push({ ny,nx });
				}
			}
		}
	}
	//매 벽을 세운 시뮬마다 최댓값 찾기
	result = max(result, get_score());
	return;
}
//벽 세우기 재귀 이용
void make_wall(int cnt) {
	//탈출 조건 벽이 3개 일때
	if (cnt == 3) {
		virus();
		return;
	}
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (tmp_map[y][x] == 0) {
				tmp_map[y][x] = 1;
				make_wall(cnt+1);
				tmp_map[y][x] = 0;
			}
		}
	}
}

int main(void) {
	//input 공간
	cin >> n >> m;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> map[y][x];
		}
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 0) { //빈공간 발견
				copy_map(map, tmp_map); //벽을 세워야 하니 임시공간 생성
				tmp_map[y][x] = 1; //벽세우기
				make_wall(1); //재귀함수 호출
				tmp_map[y][x] = 0; //벽 허물기
			}
		}
	}

	cout << result << '\n';
	return 0;
}
