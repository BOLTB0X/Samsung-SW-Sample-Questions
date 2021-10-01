#include <iostream>
#include <queue>

using namespace std;

//행 열 결과
int n, m, result;
//맵
int board[8][8];

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//최대
int max(int a, int b) {
	return a > b ? a : b;
}

//백업
void backup(int(*from)[8], int(*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}

//너비우선 탐색
void BFS(queue<pair<int, int>>& q) {
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		//상하좡 이동
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			
			//범위초과
			if (ny >= n || nx >= m || ny < 0 || nx < 0)
				continue;
			//예외 케이스
			if (board[ny][nx] == 2 || board[ny][nx] == 1)
				continue;
			//바이러스 처리
			board[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}
}

//점수 득점
int get_score() {
	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 0)
				score++;
		}
	}
	return score;
}

//벽세우기 --> 백트래킹
void make_wall(int cnt) {
	//3번 다채움 --> 정지 조건
	if (cnt == 3) {
		int cboard[8][8];
		queue<pair<int, int>> q;
		//백업
		backup(board, cboard);
		//바이러스 탐색
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] == 2) {
					q.push({ i,j });
				}
			}
		}
		//너비우선 탐색
		BFS(q);
		//최댓값 참기
		result = max(result, get_score());
		backup(cboard, board);
		return;
	}
	//벽세우기 
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (board[y][x] == 0) {
				cnt++;
				board[y][x] = 1;
				make_wall(cnt);
				cnt--;
				board[y][x] = 0;
			}
		}
	}
}

//시뮬
void simulation(void) {
	make_wall(0);
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> board[y][x];
		}
	}
	//시뮬레이션
	simulation();
	//출력
	cout << result << '\n';
	return 0;
}
