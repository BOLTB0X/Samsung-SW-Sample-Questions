#include <iostream>
#include <queue>

using namespace std;

//구슬
typedef struct {
	int red_y;
	int red_x;
	int blue_y;
	int blue_x;
	int sec;
}BEAD;

int n, m;
char board[10][11];
//두개의 구슬, y,x이므로
bool visited[10][10][10][10];

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//절댓값
int abso(int a) {
	if (a < 0)
		return -a;
	return a;
}

//너비우선
int BFS(BEAD start) {
	queue<BEAD> q;
	q.push(start);
	//초기 방문처리
	visited[start.red_y][start.red_x][start.blue_y][start.blue_x] = true;
	int res = -1;

	while (!q.empty()) {
		BEAD cur = q.front();
		q.pop();

		//탈출조건 2개
		//1개 10초 초과인 경우
		if (cur.sec > 10) 
			break;
		//빨간구슬이 구멍에 빠질 경우 
		//파란 구슬은 애초에 구멍에 안가게 함
		if (board[cur.red_y][cur.red_x] == 'O' && board[cur.blue_y][cur.blue_x] != 'O') {
			res = cur.sec;
			break;
		}

		//상하좌우 차레로 탐색
		for (int dir = 0; dir < 4; dir++) {
			int nry = cur.red_y;
			int nrx = cur.red_x;
			int nby = cur.blue_y;
			int nbx = cur.blue_x;

			//기울기 이용이므로 무한이용
			//빨간구슬
			while (true) {
				//빈공간인 경우 
				if (board[nry][nrx] != 'O' && board[nry][nrx] != '#') {
					nry += dy[dir];
					nrx += dx[dir];
				}
				//그외 즉 구멍이던가 벽이던가
				else {
					if (board[nry][nrx] == '#') {
						nry -= dy[dir];
						nrx -= dx[dir];
					}
					break;
				}
			}
			//파란구슬
			while (true) {
				//빈공간
				if (board[nby][nbx] != 'O' && board[nby][nbx] != '#') {
					nby += dy[dir];
					nbx += dx[dir];
				}
				//그외
				else {
					if (board[nby][nbx] == '#') {
						nby -= dy[dir];
						nbx -= dx[dir];
					}
					break;
				}
			}
			//구슬이 겹쳤을 경우
			if (nby == nry && nbx == nrx) {
				//구멍이 아니라면
				if (board[nry][nrx] != 'O') {
					int r_dist = abso(nry - cur.red_y) + abso(nrx - cur.red_x);
					int b_dist = abso(nby - cur.blue_y) + abso(nbx - cur.blue_x);

					if (r_dist > b_dist) {
						nry -= dy[dir];
						nrx -= dx[dir];
					}

					else if (b_dist > r_dist) {
						nby -= dy[dir];
						nbx -= dx[dir];
					}
				}
			}
			//방문처리
			if (!visited[nry][nrx][nby][nbx]) {
				visited[nry][nrx][nby][nbx] = true;
				q.push({ nry,nrx,nby,nbx,cur.sec + 1 });
			}
		}
	}

	return res;
}

void simulation(void) {
	BEAD start;
	//입력
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			cin >> board[y][x];
			if (board[y][x] == 'R') {
				start.red_y = y;
				start.red_x = x;
			}
			else if (board[y][x] == 'B') {
				start.blue_y = y;
				start.blue_x = x;
			}
		}
	}
	start.sec = 0;

	int ret = BFS(start);
	cout << ret << '\n';
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	simulation();
	return 0;
}
