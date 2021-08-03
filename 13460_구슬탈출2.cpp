#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct bead {
	int ry, rx, by, bx, cnt;
};

bead start;
int n, m;
char map[10][11];

int BFS() {
	const int dx[4] = { -1,0,1,0 };
	const int dy[4] = { 0,1,0,-1 };
	bool visited[10][10][10][10] = { false, };
	queue<bead> que;
	que.push(start);
	visited[start.ry][start.rx][start.by][start.bx] = true;

	int ret = -1;
	while (!que.empty()) {
		bead cur = que.front();
		que.pop();

		if (cur.cnt > 10) {
			break;
		}

		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O') {
			ret = cur.cnt;
			break;
		}

		for (int dir = 0; dir < 4; dir++) {
			int move_ry = cur.ry;
			int move_rx = cur.rx;
			int move_by = cur.by;
			int move_bx = cur.bx;

			//공움직임
			while (true) {
				//빨간공 움직임
				if (move_ry >= 0 && move_ry < n && move_rx >= 0 && move_rx < m) {
					if (map[move_ry][move_rx] != '#' && map[move_ry][move_rx] != 'O') {
						move_ry += dy[dir];
						move_rx += dx[dir];
					}
					else {
						if (map[move_ry][move_rx] == '#') {
							move_ry -= dy[dir];
							move_rx -= dx[dir];
						}
						break;
					}
				}
			}
			while (true) {
				//파란공 움직임
				if (move_by >= 0 && move_by < n && move_bx >= 0 && move_bx < m) {
					if (map[move_by][move_bx] != '#' && map[move_by][move_bx] != 'O') {
						move_by += dy[dir];
						move_bx += dx[dir];
					}
					else {
						if (map[move_by][move_bx] == '#') {
							move_by -= dy[dir];
							move_bx -= dx[dir];
						}
						break;
					}
				}
			}
			//공의 위치가 겹칠 경우
			if (move_ry == move_by && move_rx == move_bx) {
				if (map[move_ry][move_rx] != 'O') {
					int r_dist = abs(move_ry - cur.ry) + abs(move_rx - cur.rx);
					int b_dist = abs(move_by - cur.by) + abs(move_bx - cur.bx);

					if (r_dist > b_dist) {
						move_ry -= dy[dir];
						move_rx -= dx[dir];
					}
					else {
						move_by -= dy[dir];
						move_bx -= dx[dir];
					}
				}
			}
			//이동을 다 했으니 방문 처리
			if (visited[move_ry][move_rx][move_by][move_bx] == false) {
				visited[move_ry][move_rx][move_by][move_bx] = true;
				bead move;
				move.ry = move_ry;
				move.rx = move_rx;
				move.by = move_by;
				move.bx = move_bx;
				move.cnt = cur.cnt + 1;
				que.push(move);
			}
		}
	}
	return ret;
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%s", map[i]);
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			//빨간 공 찾기
			if (map[y][x] == 'R') {
				start.ry = y;
				start.rx = x;
			}
			//파란 공 찾기
			if (map[y][x] == 'B') {
				start.by = y;
				start.bx = x;
			}
		}
	}
	start.cnt = 0;

	int ret = BFS();
	printf("%d\n", ret);
	return 0;
}
