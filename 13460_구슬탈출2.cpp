#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct bead {
	int ry, rx, by, bx, cnt;
};

bead start;
char map[10][11]; //버퍼때문


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

		if (cur.cnt > 10)
			break;

		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O') {
			ret = cur.cnt;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int move_ry = cur.ry;
			int move_rx = cur.rx;
			int move_by = cur.by;
			int move_bx = cur.bx;

			// 계속 움직여야하므로
			while (true) {
				// 빨간공 움직임
				//움직이기 가능한 경우
				if (map[move_ry][move_rx] != '#' && map[move_ry][move_rx] != 'O') {
					move_ry += dy[i];
					move_rx += dx[i];
				}
				else {
					//벽을 만난경우
					if (map[move_ry][move_rx] == '#') {
						move_ry -= dy[i];
						move_rx -= dx[i];
					}
					break;
				}
			}
			while (true) {
				// 파란공 움직임
				//움직이기 가능한 경우
				if (map[move_by][move_bx] != '#' && map[move_by][move_bx] != 'O') {
					move_by += dy[i];
					move_bx += dx[i];
				}
				else {
					//벽을 만난경우
					if (map[move_by][move_bx] == '#') {
						move_by -= dy[i];
						move_bx -= dx[i];
					}
					break;
				}
			}

			if (move_rx == move_bx && move_by == move_ry) {
				if (map[move_ry][move_rx] != 'O') {
					int red_dist = abs(move_ry - cur.ry) + abs(move_rx - cur.rx);
					int blue_dist = abs(move_by - cur.by) + abs(move_bx - cur.bx);

					if (red_dist > blue_dist) {
						move_ry -= dy[i];
						move_rx -= dx[i];
					}
					else {
						move_by -= dy[i];
						move_bx -= dx[i];
					}
				}
			}

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
	int n, m;
	scanf("%d %d", &n, &m);

	//맵 생성
	for (int i = 0; i < n; i++) {
		scanf("%s", map[i]);
	}
	// 구슬 위치 찾기
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] == 'R') {
				start.ry = y;
				start.rx = x;
			}

			if (map[y][x] == 'B') {
				start.bx = x;
				start.by = y;
			}
		}
	}
	start.cnt = 0;

	int ret = BFS();
	printf("%d\n", ret);
	return 0;
}
