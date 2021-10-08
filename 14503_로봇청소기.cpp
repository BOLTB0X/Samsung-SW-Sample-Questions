#include <iostream>
#include <queue>

using namespace std;

//로봇
struct ROBOT {
	int y, x, dir;
};

int n, m;
int board[51][51];
bool visited[51][51];
ROBOT robot;

//입력
void input() {
	int ry, rx, dir;
	cin >> n >> m;
	cin >> ry >> rx >> dir;

	robot.y = ry;
	robot.x = rx;
	robot.dir = dir;

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < m; ++x) {
			cin >> board[y][x];
		}
	}
	return;
}

//왼쪽으로 회전
int turn_left(int dir) {
	if (dir == 0)
		return 3;
	return dir - 1;
}

//후진
int turn_back(int dir) {
	if (dir == 0)
		return 2;
	else if (dir == 2)
		return 0;
	else if (dir == 3)
		return 1;
	else if (dir == 1)
		return 3;
}

//너비우선
int BFS(queue<ROBOT>& q) {
	//동서남북
	const int dy[4] = { -1,0,1,0 };
	const int dx[4] = { 0,1,0,-1 };
	//청소처리
	board[q.front().y][q.front().x] = 2;

	int result = 1;

	while (!q.empty()) {
		ROBOT cur = q.front();
		int tmp_dir = cur.dir;
		q.pop();

		//동서남북 차례로 탐색
		for (int dir = 0; dir < 4; ++dir) {
			tmp_dir = turn_left(tmp_dir);
			int ny = cur.y + dy[tmp_dir];
			int nx = cur.x + dx[tmp_dir];

			if (ny < 0 || nx < 0 || ny >=n || nx >= m)
				continue;
			if (board[ny][nx] == 0) {
				board[ny][nx] = 2;
				q.push({ ny,nx,tmp_dir });
				result++;
				break;
			}
			//여기까지 온 거면 갈곳이 없다는 것
			else if (dir == 3) {
				int ny = cur.y + dy[turn_back(cur.dir)];
				int nx = cur.x + dx[turn_back(cur.dir)];

				if (ny < 0 || nx < 0 || ny >=n || nx >= m)
					continue;
				if (board[ny][nx] == 1)
					return result;
				else
					q.push({ ny,nx,cur.dir });
			}
		}
	}
	return result;
}

//시뮬레이션
void simulation(void) {
	
	input();
	queue<ROBOT> q;
	q.push(robot);

	int ret = BFS(q);
	cout << ret << '\n';
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//시뮬레이션
	simulation();
	return 0;
}
