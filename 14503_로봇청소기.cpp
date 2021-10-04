#include <iostream>
#include <queue>

using namespace std;

//로봇
struct ROBOT{
	int y, x, dir;
};

int n, m;
int board[50][50];

//동서남북
const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,1,0,-1 };

//왼쪽으로 회전
int turn_left(int dir) {
	if (dir == 0)
		return 3;
	return dir - 1;
}

//뒤로 회전
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

//범위 체크
bool is_range(int y, int x) {
	if (y < 0 || x < 0 || y >= n || x >= m)
		return false;
	return true;
}

//너비우선
int BFS(int y, int x, int dir) {
	queue<ROBOT> q;
	q.push({ y,x,dir });
	board[y][x] = 2;
	int result = 1;
	
	//큐가 빌때까지
	while (!q.empty()) {
		ROBOT cur = q.front();
		int tmp_dir = cur.dir;
		q.pop();
		//동서남북 ==> 4번 
		for (int dir = 0; dir < 4; dir++) {
			//왼쪽부터 차례로
			tmp_dir = turn_left(tmp_dir);
			int ny = cur.y + dy[tmp_dir];
			int nx = cur.x + dx[tmp_dir];
			if (is_range(ny, nx)) {
				if (board[ny][nx] == 0) {
					board[ny][nx] = 2;
					q.push({ ny,nx,tmp_dir });
					result++;
					break;
				}
				//다 진행했는데도 갈곳이 없다면
				else if (dir == 3) {
					int ny = cur.y + dy[turn_back(cur.dir)];
					int nx = cur.x + dx[turn_back(cur.dir)];
					if (is_range(ny, nx)) {
						if (board[ny][nx] == 1)
							return result;
						else
							q.push({ ny,nx,cur.dir });
					}
				}
			}
		}
	}
	return result;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//입력
	int y, x, dir;
	cin >> n >> m;
	cin >> y >> x >> dir;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> board[y][x];
		}
	}
	// BFS시뮬레이션 시작
	int ret = BFS(y, x, dir);
	cout << ret << '\n';
	return 0;
}
