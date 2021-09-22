#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

//위치와 거리를 담는 구조체
struct INF {
	int y, x, dist;

	//거리 조건
	bool operator < (const INF& i) const {
		if (dist == i.dist) {
			if (y == i.y) {
				return x > i.x;
			}
			return y > i.y;
		}
		return dist > i.dist;
	}
};

int n, m, fuel;
int map[21][21];
bool visited[21][21];
int taxi_y, taxi_x;
int customer[401][4];
int customer_idx, flag, used_fuel;

//상하좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//범위 체크
bool check_range(int y, int x) {
	if (y >= 1 && x >= 1 && y <= n && x <= n)
		return true;
	return false;
}

//우선순위 큐와 BFS 탐색으로 고객을 찾음
void find_customer(int sy, int sx, int dist) {
	priority_queue<INF> pq;
	pq.push({ sy,sx,dist });

	//큐가 빌때까지
	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int dist = pq.top().dist;

		//만약 손님의 위치면
		for (int i = 1; i <= m; i++) {
			if (customer[i][0] != -1 && cy == customer[i][0] && cx == customer[i][1]) {
				customer_idx = i;
				used_fuel = dist;
				//체크
				flag = 1;
				break;
			}
		}
		//체크되었으면 탈출
		if (flag == 1)
			break;
		pq.pop();
		//이동하면서 손님위치 탐색
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (map[ny][nx] == 0 && !visited[ny][nx]) {
				if (check_range(ny, nx)) {
					visited[ny][nx] = true;
					pq.push({ ny,nx,dist + 1 });
				}
			}
		}
	}
	return;
}

void move(int sy, int sx, int dist) {
	priority_queue<INF> pq;
	pq.push({ sy,sx,dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int dist = pq.top().dist;
		//목적지에 도달했으면
		if (cy == customer[customer_idx][2] && cx == customer[customer_idx][3]) {
			used_fuel = dist;
			flag = 1;
			break;
		}
		//체크
		if (flag == 1)
			break;
		pq.pop();
		//이동하면서 목적지위치 최단거리 탐색
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (map[ny][nx] == 0 && !visited[ny][nx]) {
				if (check_range(ny, nx)) {
					visited[ny][nx] = true;
					pq.push({ ny,nx,dist + 1 });
				}
			}
		}
	}
	return;
}

int simulation(void) {
	int result = -1;
	for (int i = 1; i <= m; i++) {
		//제일 먼저 가장 가까운 고객탐색
		flag = 0;
		memset(visited, false, sizeof(visited));
		find_customer(taxi_y, taxi_x, 0);
		taxi_y = customer[customer_idx][0];
		taxi_x = customer[customer_idx][1];
		customer[customer_idx][0] = -1;
		fuel -= used_fuel;
		//없거나 연료가 바닥나면
		if (fuel < 0 || flag == 0)
			break;
		//그 고객을 실고 목적지까지 이동
		flag = 0;
		memset(visited, false, sizeof(visited));
		move(taxi_y, taxi_x, 0);
		taxi_y = customer[customer_idx][2];
		taxi_x = customer[customer_idx][3];
		fuel -= used_fuel;
		if (fuel < 0 || flag == 0)
			break;
		fuel += (used_fuel * 2);
	}
	//마지막 까지 조건 체크
	if (fuel >= 0 && flag == 1)
		result = fuel;
	return result;
}

int main(void) {
	//맵 입력
	scanf("%d %d %d", &n, &m, &fuel);
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &map[y][x]);
		}
	}
	//택시위치
	scanf("%d %d", &taxi_y, &taxi_x);
	//손님정보
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		customer[i][0] = a;
		customer[i][1] = b;
		customer[i][2] = c;
		customer[i][3] = d;
	}
	//시뮬레이션 실행
	int ret = simulation();
	printf("%d", ret);
	return 0;
}
