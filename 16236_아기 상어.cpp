#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

int n;
int map[20][20];
bool visited[20][20];

struct SHARK {
	int dist;
	int y;
	int x;
	//우선순위
	bool operator < (const SHARK& s) const {
		if (dist == s.dist) { //거리가 같다면
			if (y == s.y)
				return x > s.x; //x값 기준 오름차순
			else
				return y > s.y; //y값 기준 오름차순
		}
		else
			return dist > s.dist;
	}
};

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int babyshark_size = 2;
int babyshark_move = 0;
int babyshark_eat = 0;
priority_queue<SHARK> pq;

void BFS() {
	while (!pq.empty()) {
		int dist = pq.top().dist;
		int y = pq.top().y;
		int x = pq.top().x;
		pq.pop();
		//그 위치에서 먹을 수 있다면
		if (map[y][x] > 0 && map[y][x] < babyshark_size) {
			babyshark_eat++;
			map[y][x] = 0;
			//아기 상어의 크기와 먹은 횟수가 같다면
			if (babyshark_size == babyshark_eat) {
				babyshark_size++;
				babyshark_eat = 0; //먹은 횟수 초기화
			}
			//총 이동에 움직인 거리를 더해줌
			babyshark_move += dist;
			//이제 다시 처음부터 사냥감 찾아야함
			//초기화
			dist = 0;
			memset(visited, false, sizeof(visited));
			while (!pq.empty()) 
				pq.pop();
			
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			//범위에서 벗어난 경우
			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			//재방문인 경우
			if (visited[ny][nx])
				continue;
			//물고기가 있지만 아기상어보다 큰 경우
			if (map[ny][nx] > 0 && map[ny][nx] > babyshark_size)
				continue;
			pq.push({dist+1,ny,nx});
			visited[ny][nx] = true;
		}
	}
}

int main(void) {
	scanf("%d", &n);

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 9) {
				pq.push({ 0,y,x });
				map[y][x] = 0;
			}
		}
	}
	BFS();
	printf("%d", babyshark_move);
	return 0;
}
