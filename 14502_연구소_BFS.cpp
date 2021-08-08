#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[8][8];
int tmp_map[8][8];
int virus_map[8][8];

int result = 0;

int max(int a, int b) {
	return a > b ? a : b;
}


int get_score() {
	int score = 0;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (virus_map[y][x] == 0)
				score += 1;
		}
	}
	return score;
}

void copy_map(int(*from)[8], int(*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
}

void virus() {
	copy_map(tmp_map, virus_map);

	int dy[4] = { -1,0,1,0 };
	int dx[4] = { 0,1,0,-1 };

	queue<pair<int, int>> que;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (virus_map[y][x] == 2) {
				que.push({ y,x });
			}
		}
	}
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
	
	result = max(result, get_score());
}

void make_wall(int cnt) {
	if (cnt == 3) {
		virus();
		return;
	}
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (tmp_map[y][x] == 0) {
				tmp_map[y][x] = 1;
				make_wall(cnt + 1);
				tmp_map[y][x] = 0;
			}
		}
	}
}

int main(void) {
	cin >> n >> m;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> map[y][x];
		}
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 0) {
				copy_map(map, tmp_map);
				tmp_map[y][x] = 1;
				make_wall(1);
				tmp_map[y][x] = 0;
			}
		}
	}

	cout << result << '\n';
	return 0;
}
