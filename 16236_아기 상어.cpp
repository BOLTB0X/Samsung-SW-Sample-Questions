#include <iostream>
#include <queue>

using namespace std;

//상어 정보를 담는 구조체
struct SHARK {
	int dist, y, x;

	//문제조건
	bool operator < (const SHARK& s) const {
		if (dist == s.dist) {
			if (y == s.y)
				return x > s.x;
			return y > s.y;
		}
		return dist > s.dist;
	}
};

int n;
int board[20][20];
bool visited[20][20];

//하상좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//초기화
void init(priority_queue<SHARK>& pq) {
	//방문 초기화
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			visited[y][x] = false;
	while (!pq.empty())
		pq.pop();
	return;
}

//BFS
int BFS(priority_queue<SHARK>& pq) {
	//초기값 세팅
	int move = 0;
	int shark_size = 2;
	int eat_cnt = 0;

	while (!pq.empty())	{
		SHARK cur = pq.top();
		pq.pop();
		
		//잡아 먹을 수 있다면 0보다 큰 조건을 걸지 않으면 빈칸도 잡아버림
		if (shark_size > board[cur.y][cur.x] && board[cur.y][cur.x] > 0) {
			eat_cnt++;
			board[cur.y][cur.x] = 0;
			//사이즈업 조건
			if (shark_size == eat_cnt) {
				shark_size++;
				eat_cnt = 0;
			}
			//거리가 즉 총 걸린 시간이므로 더해주고
			move += cur.dist;
			//다 초기화
			cur.dist = 0;
			init(pq);
		}
		//cur위치에서 새로운 물고기를 잡기 위해 BFS탐색
		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];
			
			//범위 초과
			if (ny >= n || nx >= n || ny < 0 || nx < 0)
				continue;
			//재방문
			if (visited[ny][nx])
				continue;
			//몸집이 크면
			if (board[ny][nx] > shark_size)
				continue;
			//pq삽입
			pq.push({ cur.dist + 1,ny,nx });
			visited[ny][nx] = true;
		}
	}
	return move;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n;
	priority_queue<SHARK> pq;
	//맵 생성
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> board[y][x];
			//상어 위치 찾기
			if (board[y][x] == 9) {
				pq.push({ 0,y,x});
				board[y][x] = 0;
			}
		}
	}
	//BFS시작
	int ret = BFS(pq);
	cout << ret << '\n';
	return 0;
}
