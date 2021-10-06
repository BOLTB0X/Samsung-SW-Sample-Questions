#include <iostream>
#include <queue>

using namespace std;

struct INFO {
	int y, x, dist;

	bool operator < (const INFO& i) const {
		if (dist == i.dist) {
			if (y == i.y) {
				return x > i.x;
			}
			return y > i.y;
		}
		return dist > i.dist;
	}
};

int n, m, fuel, result;
int board[21][21];
int customer[401][4];

int taxi_y, taxi_x;
bool flag;
int used_fuel, customer_idx;

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//입력
void input(void) {
	cin >> n >> m >> fuel;
	for (int y = 1; y <= n; ++y) {
		for (int x=1; x<=n; ++x) {
			cin >> board[y][x];
		}
	}

	cin >> taxi_y >> taxi_x;
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		customer[i][0] = a;
		customer[i][1] = b;
		customer[i][2] = c;
		customer[i][3] = d;
	}
}

void visited_init(bool (*visited)[21]) {
	for (int y = 1; y <= n; ++y) {
		for (int x = 1; x <= n; ++x) {
			visited[y][x] = false;
		}
	}
	return;
}

void find_customer(bool(*visited)[21], int ty, int tx, int dist) {
	priority_queue<INFO> pq;
	pq.push({ ty,tx,dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int cdist = pq.top().dist;

		//현 위치에 승객이 있다면
		for (int i = 1; i <= m; ++i) {
			if (customer[i][0] != -1 && customer[i][0] == cy && customer[i][1] == cx) {
				customer_idx = i;
				flag = true;
				used_fuel = cdist;
				break;
			}
		}
		//탈출 조건이 된다면
		if (flag)
			break;
		pq.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];
			//범위 초과
			if (ny < 1 || nx < 1 || nx>n || ny >n)
				continue;
			//재방문 및 빈공간이 아니면
			if (visited[ny][nx] || board[ny][nx] != 0)
				continue;
			visited[ny][nx] = true;
			pq.push({ ny,nx,cdist + 1 });
		}
	}
	return;
}

//목적지를 향한 택시이동
void taxi_move(bool(*visited)[21], int ty, int tx, int dist) {
	priority_queue<INFO> pq;
	pq.push({ ty,tx,dist });

	while (!pq.empty()) {
		int cy = pq.top().y;
		int cx = pq.top().x;
		int cdist = pq.top().dist;

		//승객의 목적지에 도달했다면
		if (customer[customer_idx][2] == cy && customer[customer_idx][3] == cx) {
			flag = true;
			used_fuel = cdist;
			break;
		}

		if (flag)
			break;
		pq.pop();
		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];
			//범위 초과
			if (ny < 1 || nx < 1 || nx>n || ny >n)
				continue;
			//재방문 및 빈공간이 아니면
			if (visited[ny][nx] || board[ny][nx] != 0)
				continue;
			visited[ny][nx] = true;
			pq.push({ ny,nx,cdist + 1 });
		}

	}
}

void simulation(void) {
	input();
	result = -1;
	//진짜 시뮬시작
	for (int i = 1; i <= m; ++i) {
		//제일 먼저 손님 탐색
		flag = false;
		bool visited[21][21] = { false, };
		
		//현 택시위치에서 가장 가까운 승객 탐색
		find_customer(visited, taxi_y, taxi_x, 0);
		//택시 위치 초기화
		taxi_y = customer[customer_idx][0];
		taxi_x = customer[customer_idx][1];
		//승객이 탑승했다는 기록
		customer[customer_idx][0] = -1;
		fuel -= used_fuel;

		//한번 더 검사
		if (!flag || fuel < 0)
			break;
		
		//목적지 이동
		flag = false;
		//방문초기화
		visited_init(visited);
		//손님 목적지 이동
		taxi_move(visited, taxi_y, taxi_x, 0);
		//택시 위치 변경
		taxi_y = customer[customer_idx][2];
		taxi_x = customer[customer_idx][3];
		// 연료 소비
		fuel -= used_fuel;

		//한번 더 검사
		if (!flag || fuel < 0)
			break;

		//여기까지 안전하게 왔으면
		fuel += (used_fuel * 2);
	}
	//마지막 검사
	if (flag && fuel >= 0)
		result = fuel;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	simulation();
	cout << result << '\n';
	return 0;
}
