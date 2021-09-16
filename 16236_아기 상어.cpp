#include <cstdio>
#include <queue>

using namespace std;

//상어 정의
struct SHARK {
	int dist, y, x;
	//우선 순위
	bool operator < (const SHARK& s) const {
		//거리가 같을 경우
		if (dist == s.dist) {
			//위에도 많다면
			if (y == s.y) {
				//왼쪽
				return x > s.x; //x좌표기준 오름차순
			}
			else
				return y > s.y; //y좌표기준 오름차순
		}
		else
			return dist > s.dist; //가리기준
	}
};

int n;
int map[20][20];
bool visited[20][20];
//상하좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//초기화
void init(priority_queue<SHARK>& pq) {
	//방문 초기화
	for (int y = 0; y < n; y++) 
		for (int x = 0; x < n; x++) 
			visited[y][x] = false;
	//큐 초기화
	while (!pq.empty())
		pq.pop();
	return;
}

//BFS
int BFS(priority_queue<SHARK>& pq) {
	int shark_move = 0;
	int shark_size = 2;
	int shark_eat = 0;

	while (!pq.empty()) {
		SHARK cur = pq.top();
		pq.pop();

		//현재 위치에서 잡어먹을 수 있다면?
		if (shark_size > map[cur.y][cur.x] && map[cur.y][cur.x] > 0 ) {
			shark_eat ++;
			map[cur.y][cur.x] = 0;
			//사이즈업 조건
			if (shark_eat == shark_size) {
				shark_size++;
				shark_eat = 0;
			}
			//여태 진행 과정 더해줌
			shark_move += cur.dist;
			cur.dist = 0;
			//초기화
			init(pq);
		}
		//상하좌우기준 움직임
		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];
			//범위 out
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			//재방문 out
			if(visited[ny][nx])
				continue;
			//물고기가 크다면
			if (map[ny][nx] > 0 && map[ny][nx] > shark_size)
				continue;
			//이동경로 또는 잡아먹을 수 있는
			pq.push({ cur.dist + 1,ny,nx });
			visited[ny][nx] = true;
		}
	}
	return shark_move;
}

int main(void) {
	priority_queue<SHARK> pq;
	//행,열 입력
	scanf("%d", &n);
	//맵 입력
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				pq.push({ 0,i,j });
				map[i][j] = 0;
			}
		}
	}
	//BFS 시뮬레이션 시작
	int ret = BFS(pq);
	printf("%d", ret);
	return 0;
}
