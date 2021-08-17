#include <iostream>
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

	bool operator < (const SHARK& s) const {
		if (dist == s.dist) {
			if (y == s.y) {
				return x > s.x; // x기준 오름차순
			}
			else return y > s.y;
		}
		else return dist > s.dist;
	}
};

priority_queue<SHARK> pq;
int baby_shark_size = 2;
int move_cnt = 0;
int eat_cnt = 0;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void BFS(void) {
	while (!pq.empty()) {
		int cur_dist = pq.top().dist;
		int cur_y = pq.top().y;
		int cur_x = pq.top().x;
		pq.pop();

		//현재 위치 파악
		if (map[cur_y][cur_x] > 0 && map[cur_y][cur_x] < baby_shark_size) {
			eat_cnt += 1;
			map[cur_y][cur_x] = 0;
			if (baby_shark_size == eat_cnt) {
				baby_shark_size += 1;
				eat_cnt = 0;
			}
			//아기상어가 얼마나 움직였는지 
			move_cnt += cur_dist; 

			//지금 위치부터 다음 물고기까지 거리를 재야함
			//즉 초기화
			cur_dist = 0;
			memset(visited, false, sizeof(visited));

			while (!pq.empty())
				pq.pop();
		}
		for (int i = 0; i < 4; i++) {
			int ny = cur_y + dy[i];
			int nx = cur_x + dx[i];

			//범위 초과할 경우
			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			//방문한 경우
			if (visited[ny][nx])
				continue;
			if (map[ny][nx] > baby_shark_size)
				continue;
			pq.push({ cur_dist + 1,ny,nx });
			visited[ny][nx] = true;
		}
	}
}

int main(void) {
	cin >> n;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
			if (map[y][x] == 9) {
				map[y][x] = 0; //위치를 알았으니
				pq.push({ 0,y,x });
			}
		}
	}
	BFS();
	cout << move_cnt << '\n';
	return 0;
}