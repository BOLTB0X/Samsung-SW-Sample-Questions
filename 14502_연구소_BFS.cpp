#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[8][8]; 
int tmp_map[8][8]; //입력용
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int answer = 0;

//temp에 기존 map을 복사하는 함수
void copyMap(int(*from)[8], int(*to)[8]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = from[i][j];
		}
	}
}

void virus() {
	int result[8][8];
	copyMap(tmp_map, result);
	//바이러스가 있는 곳(2)의 사방을 전염시킨다.
	queue<pair<int, int>> que;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (result[i][j] == 2) {
				que.push({ i, j });
			}
		}
	}
	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if (result[nx][ny] == 0) {
					result[nx][ny] = 2;
					que.push({ nx, ny });
				}
			}
		}
	}
	//바이러스가 전염되지 않은 곳(0)을 세어준다.
	int noVirus = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (result[i][j] == 0) 
				noVirus++;
		}
	}
	answer = max(noVirus, answer);
}

//[브루트포스] 가능한 모든 경우의 수로 벽을 3개 세움, 재귀이용
void make_wall(int cnt) {
	if (cnt == 3) {
		virus();
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp_map[i][j] == 0) {
				tmp_map[i][j] = 1; //벽세우기
				make_wall(cnt + 1); //벽 세운 횟수를 +1
				tmp_map[i][j] = 0; //기존의 상태로 돌아가기(벽허물기)
			}
		}
	}
}
int main(void) {
	//맵 생성
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	//각 위치마다 벽을 세운다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				copyMap(map, tmp_map);
				tmp_map[i][j] = 1; // 벽세우기
				make_wall(1); //벽 하나 세웠으므로 cnt = 1
				tmp_map[i][j] = 0; //벽허물기(원래 상태로 돌아가기)
			}
		}
	}
	//output
	cout << answer <<'\n';
	return 0;
}