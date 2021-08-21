#include <iostream>
#include <queue>
using namespace std;

struct pos {
	int r;
	int c;
	int dir;
};

int n, m;
int map[51][51];
queue<pos> q;
//  0
// 3 1
//  2
int turn_left(int d) {
	if (d == 0)
		return 3;
	else if (d == 1)
		return 0;
	else if (d == 2)
		return 1;
	else if (d == 3)
		return 2;
}

int turn_back(int d) {
	if (d == 0)
		return 2;
	else if (d == 1)
		return 3;
	else if (d == 2)
		return 0;
	else if (d == 3)
		return 1;
}

int BFS(int row, int col, int direction) {
	int dr[4] = { -1,0,1,0 };
	int dc[4] = { 0,1,0,-1 };
	pos start;
	start.r = row;
	start.c = col;
	start.dir = direction;
	q.push(start);
	int result = 1;
	map[start.r][start.c] = 2;
	//2번
	while (!q.empty()) {
		pos cur;
		cur.r = q.front().r;
		cur.c = q.front().c;
		cur.dir = q.front().dir;
		int tmp_dir = cur.dir;
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			tmp_dir = turn_left(tmp_dir);
			int nr = cur.r + dr[tmp_dir];
			int nc = cur.c + dc[tmp_dir];

			//2번의 a
			if (0 <= nr && nr < n && 0 <= nc && nc < m && map[nr][nc] == 0) {
				pos next;
				next.r = nr;
				next.c = nc;
				next.dir = tmp_dir;
				map[next.r][next.c] = 2;
				q.push(next);
				result += 1;
				break;
			}
			//if에 안걸리면 2번의 b
			
			//2번의 c
			else if (i == 3) {
				pos back;
				back.r = cur.r + dr[turn_back(cur.dir)];
				back.c = cur.c + dc[turn_back(cur.dir)];
				back.dir = cur.dir;
				q.push(back);

				if (map[back.r][back.c] == 1) {
					return result;
				}
			}
		}
	}
	return result;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	int row, col, direction;
	cin >> row >> col >> direction;

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			cin >> map[r][c];
		}
	}
	
	int ret = BFS(row,col,direction);

	cout << ret << '\n';
	return 0;
}
