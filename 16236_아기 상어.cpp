#include <iostream>
#include <queue>

using namespace std;

struct SHARK {
	int y, x, dist;

	bool operator < (const SHARK& s) const {
		if (dist == s.dist) {
			if (y == s.y) {
				return x > s.x;
			}
			return y > s.y;
		}
		return dist > s.dist;
	}
};

int n, result;
int board[20][20];
bool visited[20][20];
//아기상어의 움직임을 담는 우선순위 큐
priority_queue<SHARK> pq;

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//입력
void input(void) {
	cin >> n;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			cin >> board[y][x];
			//아기 상어가 입력된다면
			if (board[y][x] == 9) {
				pq.push({ y,x,0 });
				board[y][x] = 0;
			}
		}
	}
	return;
}

//우선순위 큐와 방문리스트 초기화
void init(void) {
	while (!pq.empty()) {
		pq.pop();
	}
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			visited[y][x] = false;
		}
	}
	return;
}

//너비 우선 탐색
void BFS(void) {
	int shark_size = 2;
	int shark_move = 0;
	int eating_cnt = 0;

	//큐가 빌때까지
	while (!pq.empty()) {
		SHARK cur = pq.top();
		pq.pop();
		
		//물고기가 있다면
		if (board[cur.y][cur.x] > 0) {
			//잡아먹을 수 있다면
			//상어 사이즈보다 미만인 경우
			if (shark_size > board[cur.y][cur.x]) {
				eating_cnt++;
				board[cur.y][cur.x] = 0;
				//사이즈 업이 가능하다면
				if (eating_cnt == shark_size) {
					shark_size++;
					eating_cnt = 0;
				}
				//이동거리가 즉 소요시간
				shark_move += cur.dist;
				//pq및 방문리스트 초기화
				init();
				cur.dist = 0;
			}

		}
		//상하좌우 탐색
		for (int dir = 0; dir < 4; ++dir) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			//범위 초과
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			//재방문이고 상어사이즈보다 큰 물고기가 있다면
			if (visited[ny][nx] || board[ny][nx] > shark_size)
				continue;
			//현재 위치 우선순위 삽입
			pq.push({ ny,nx,cur.dist + 1 });
			visited[ny][nx] = true;
		}
	}
	result = shark_move;
	return;
}

//시뮬레이션 시작
void simulation(void) {
	input();
	BFS();
	cout << result << '\n';
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//시뮬 시작
	simulation();
	return 0;
}
