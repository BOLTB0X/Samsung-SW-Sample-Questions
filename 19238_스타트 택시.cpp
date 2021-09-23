#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

//변수 및 우선순위 큐를 위한 연산자 수정
struct INF {
	int y, x, dist;

	bool operator < (const INF& i) const {
		if (dist == i.dist) {
			if (y == i.y) 
				return x > i.x;
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
//체크, 소모된 연료, 손님 번호
int flag, used_fuel,customer_idx;
//상하좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//방문초기
void visit_init(void) {
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			visited[y][x] = false;
		}
	}
	return;
}

//범위 체크
bool check_range(int y, int x) {
	if (y >= 1 && x >= 1 && y <= n && x <= n)
		return true;
	return false;
}

//손님 찾기
void find_customer(int y, int x, int dist) {
	priority_queue<INF> pq;
	pq.push({ y,x,dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int cd = pq.top().dist;

		//승객위치에 도달했다면
		//승객배열 탐색
		for (int i = 1; i <= m; i++) {
			if (customer[i][0] != -1
				&& customer[i][0] == cy && customer[i][1] == cx) {
				customer_idx = i; //승객 번호 할당
				flag = 1;
				used_fuel = cd;
				break;
			}
		}
		if (flag == 1)
				break;
		pq.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			if (check_range(ny, nx)) {
				if (!visited[ny][nx] && map[ny][nx] == 0) {
					visited[ny][nx] = true;
					pq.push({ ny,nx,cd + 1 });
				}
			}
		}
	}
	return;
}

void taxi_move(int y, int x, int dist) {
	priority_queue<INF> pq;
	pq.push({ y,x,dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int cd = pq.top().dist;

		//승객위치에 도달했다면
		if (customer[customer_idx][2] == cy && customer[customer_idx][3] == cx) {
			flag = 1;
			used_fuel = cd;
			break;
		}
		if (flag == 1)
				break;
		pq.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			if (check_range(ny, nx)) {
				if (!visited[ny][nx] && map[ny][nx] == 0) {
					visited[ny][nx] = true;
					pq.push({ ny,nx,cd + 1 });
				}
			}
		}
	}
	return;
}

//시뮬레이션
int simulation(void) {
	int result = -1;
	//손님 숫자만큼 반복 시작
	for (int i = 1; i <= m; i++) {
		//손님찾기
		flag = 0;
		visit_init();
		//택시 위치에서 가장 가까운 승객 찾기
		find_customer(taxi_y, taxi_x, 0);
		taxi_y = customer[customer_idx][0];
		taxi_x = customer[customer_idx][1];
		//이 승객은 탑승했다는 기록
		customer[customer_idx][0] = -1;
		fuel -= used_fuel;
		//한 번 더 검사
		if (fuel < 0 || flag == 0)
			break;
		//손님 데리고 이동하기
		flag = 0;
		visit_init();
		//목적지 위치로 이동
		taxi_move(taxi_y, taxi_x, 0);
		//택시위치 목적지로 변경
		taxi_y = customer[customer_idx][2];
		taxi_x = customer[customer_idx][3];
		//이 승객은 탑승했다는 기록
		fuel -= used_fuel;
		//한번 더 검사
		if (fuel < 0 || flag == 0)
			break;
		//안전하게 도착했으니 연료 충전
		fuel += (used_fuel * 2);
	}
	if (fuel >= 0 && flag == 1) 
		result = fuel;
	return result;
}

int main(void) {
	//맵 정보 입력
	scanf("%d %d %d", &n, &m, &fuel);
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &map[y][x]);
		}
	}
	scanf("%d %d", &taxi_y, &taxi_x);
	//각 승객 정보입력
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		customer[i][0] = a;
		customer[i][1] = b;
		customer[i][2] = c;
		customer[i][3] = d;
	}

	//시뮬레이션 시작
	int ret = simulation();
	printf("%d\n", ret);
	return 0;
}
