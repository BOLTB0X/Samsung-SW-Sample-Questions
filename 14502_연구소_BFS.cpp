#include <iostream>
#include <queue>

using namespace std;

int n, m;
int board[8][8];
int result = -1;

//최대
int max(int a, int b) {
	return a > b ? a : b;
}

//입력
void input(void) {
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> board[y][x];
		}
	}
	return;
}

//백업용
void backup(int (*from)[8], int (*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}

//바이러스 위치 탐색
void find_virus(queue<pair<int, int>> &q, bool (*visited)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (board[y][x] == 2) {
				q.push({ y,x });
				visited[y][x] = true;
			}
		}
	}
	return;
}

//너비 우선을 이용하여 바이러스 확산
void virus_spread(queue<pair<int, int>> &q, bool (*visited)[8]) {
	//상하좌우
	const int dy[4] = { 1,-1,0,0 };
	const int dx[4] = { 0,0,-1,1 };

	//큐가 비어질때까지
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		
		//4방향 탐색
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			//범위 초과
			if (ny < 0 || nx < 0 || ny >= n || nx >= m)
				continue;
			//벽이거나 바이러스이거나 재방문인 경우
			if (board[ny][nx] == 1 || board[ny][nx] == 2 || visited[ny][nx])
				continue;
			
			//전염처리
			board[ny][nx] = 2;			
			q.push({ ny,nx });
			visited[ny][nx] = true;
		}
	}
}

//안전지역 계산
int get_safe_area(void) {
	int cnt = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (board[y][x] == 0)
				cnt++;
		}
	}
	return cnt;
}

//백트래킹을 이용한 벽 짓기
void make_wall(int cnt) {
	//탈출 조건
	if (cnt == 3) {
		//백업용 맵
		int cboard[8][8];
		backup(board, cboard);
		queue<pair<int, int>> q;
		bool visited[8][8] = { false, };
		
		//바이러스 위치 탐색
		find_virus(q,visited);
		//바이러스 BFS로 확산
		virus_spread(q,visited);
		//최대값인지 확인
		result = max(result, get_safe_area());
		//다시 백업
		backup(cboard, board);
		return;
	}
	
	//완점탐색 시작
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			//빈공간 발견
			if (board[y][x] == 0) {
				//벽 짓기
				board[y][x] = 1;
				cnt++;
				//호출
				make_wall(cnt);
				//다시 허물기
				cnt--;
				board[y][x] = 0;
			}
		}
	}
}

//시뮬레이션
void simulation(void) {
	input();
	make_wall(0);
	cout << result << '\n';
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	simulation();
	return 0;
}
