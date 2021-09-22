#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

struct INF {
	int y, x, dist;
	
	bool operator < (const INF& i) const {
		//거리가 같은 경우
		if (dist == i.dist) {
			if (y == i.y)
				return x > i.x;
			return y > i.y;
		}
		return dist > i.dist;
	}
};

int n, m, fuel;
int taxi_y, taxi_x;
int flag, customer_idx, using_fuel;
int map[21][21];
bool visited[21][21];
int customer[401][4];

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//우선순위 큐와 BFS로 손님별 우선순위 구함
void find_customer(int start_y, int start_x, int dist) {
	priority_queue<INF> pq;
	pq.push({ start_y,start_x, dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int dist = pq.top().dist;
		//승객인지 확인
		for (int i = 1; i <= m; i++) {
			if (customer[i][0] !=-1 && cy == customer[i][0] && cx == customer[i][1]) {
				customer_idx = i;
				using_fuel = dist;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
		pq.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (map[ny][nx] == 0 && !visited[ny][nx]) {
				if (ny > 0 && nx > 0 && ny <= n && nx <= n) {
					visited[ny][nx] = true;
					pq.push({ ny,nx,dist + 1 });
				}
			}
		}
	}
	return;
}

//BFS를 이용하여 이동
void move(int start_y, int start_x, int dist) {
	priority_queue<INF> pq;
	pq.push({ start_y,start_x, dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int dist = pq.top().dist;

		if (cy == customer[customer_idx][2] && cx == customer[customer_idx][3]) {
			using_fuel = dist;
			flag = 1;
			break;
		}
		if (flag == 1)
			break;
		pq.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (map[ny][nx] == 0 && !visited[ny][nx]) {
				if (ny > 0 && nx > 0 && ny <= n && nx <= n) {
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
		flag = 0;
		memset(visited, false, sizeof(visited));
		find_customer(taxi_y, taxi_x, 0);
		taxi_y = customer[customer_idx][0];
		taxi_x = customer[customer_idx][1];
		customer[customer_idx][0] = -1;
		fuel -= using_fuel;
		if (fuel < 0 || flag == 0)
			break;
		memset(visited, false, sizeof(visited));
		flag = 0;
		move(taxi_y, taxi_x, 0);
		taxi_y = customer[customer_idx][2];
		taxi_x = customer[customer_idx][3];
		fuel -= using_fuel;
		if (fuel < 0 || flag == 0)
			break;

		fuel += using_fuel * 2;
	}
	if (fuel >= 0 && flag == 1)
		return fuel;
	return result;
}

int main(void) {
	scanf("%d %d %d", &n, &m, &fuel);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	scanf("%d %d", &taxi_y, &taxi_x);
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		customer[i][0] = a;
		customer[i][1] = b;
		customer[i][2] = c;
		customer[i][3] = d;
	}
	int ret = simulation();
	printf("%d", ret);
	return 0;
}