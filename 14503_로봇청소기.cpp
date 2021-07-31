#include <iostream>
#include <queue>
using namespace std;

int n, m;
queue<pair<pair<int,int>,int>> que;
int graph[51][51];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int turn_left(int value) {
	if (value == 0)
		return 3;
	else if (value == 1)
		return 0;
	else if (value == 2)
		return 1;
	else if (value == 3)
		return 2;
}

int turn_back(int value) {
	if (value == 0)
		return 2;
	else if (value == 1)
		return 3;
	else if (value == 2)
		return 0;
	else if (value == 3)
		return 1;
}

int BFS(int r, int c, int d) {
	int cnt = 1;
	graph[r][c] = 2; //방문 체크
	que.push(make_pair(make_pair(r, c), d));

	while (!que.empty()) {
		int cur_r = que.front().first.first;
		int cur_c = que.front().first.second;
		int cur_d = que.front().second;
		int tmp_d = cur_d;
		que.pop();

		for (int i = 0; i < 4; i++) {
			tmp_d = turn_left(tmp_d);
			int move_r = cur_r + dx[tmp_d];
			int move_c = cur_c + dy[tmp_d];

			if (0 <= move_c < m && 0 <= move_r < n && graph[move_r][move_c] == 0) {
				cnt += 1;
				graph[move_r][move_c] = 2;
				que.push(make_pair(make_pair(move_r, move_c), tmp_d));
				break; //1번으로 돌아감
			}

			else if (i == 3) {
				int move_r = cur_r + dx[turn_back(cur_d)];
				int move_c = cur_c + dy[turn_back(cur_d)];
				que.push(make_pair(make_pair(move_r, move_c), cur_d));
				
				if (graph[move_r][move_c] == 1)
					return cnt;
			}
		}
	}
}

int main() {
	cin >> n >> m;
	int row, col, dir;
	cin >> row >> col >> dir;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) 
			cin >> graph[i][j];
	}

	cout << BFS(row, col, dir) << '\n';
	return 0;
}