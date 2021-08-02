#include <iostream>
using namespace std;

int n, m; //세로,가로
int map[8][8];
int tmp_map[8][8];

//이동방향
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int answer=0;

int max(int a, int b) {
	return a > b ? a : b;
}

void virus(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		
		//이동방향이 범위에 맞는다면
		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (tmp_map[nx][ny] == 0) {
				tmp_map[nx][ny] = 2;
				virus(nx, ny); //재귀 호출
			}
		}
	}
}

int get_score() {
	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp_map[i][j] == 0)
				//안전영역 카운트
				score += 1;
		}
	}
	return score;
}

void DFS(int cnt) {
	if (cnt == 3) {
		//울타리 3개 일때, 확인을 위해 임시로 옮김
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tmp_map[i][j] = map[i][j];
			}
		}
		//바이러스 위치에서 확산 시작
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (tmp_map[i][j] == 2)
					virus(i, j); //재귀 호출
			}
		}
		//각 벽설치 후 바이러스 확산 케이스마다 체크
		answer = max(get_score(), answer);
		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				cnt += 1;
				map[i][j] = 1;
				DFS(cnt); //재귀호출
				//다시 울타리 제거
				cnt -= 1;
				map[i][j] = 0;
			}
		}
	}
}

int main(void) {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	DFS(0);
	cout << answer << '\n';
	return 0;
}