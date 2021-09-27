#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//우선순위 큐를 위한 구조체
struct INFO {
	int y, x, block_cnt = 0, rainbow_cnt = 0;

	bool operator < (const INFO& i) const {
		if (block_cnt == i.block_cnt) {
			if (rainbow_cnt == i.rainbow_cnt) {
				if (y == i.y)
					return x < i.x;
				else
					return y < i.y;
			}
			else
				return rainbow_cnt < i.rainbow_cnt;
		}
		else
			return block_cnt < i.block_cnt;
	}
};

int n, m, result;
int board[20][20] = { 0, };

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//블록그룹 찾기
bool find_block(void) {
	bool block_visited[20][20] = { false, };
	priority_queue<INFO> pq;

	//블록 생성
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			//일반 블록 생성
			if (board[y][x] > 0 && !block_visited[y][x]) {
				bool rainbow_visited[20][20] = { false, };
				queue<pair<int, int>> q;
				q.push({ y,x });
				block_visited[y][x] = true;

				//잡은 블록으로 어느정도 블록그룹이 되는 지 확인
				int block_cnt = 1, rainbow_cnt = 0;
				while (!q.empty()) {
					int cy = q.front().first;
					int cx = q.front().second;
					q.pop();

					for (int dir = 0; dir < 4; dir++) {
						int ny = cy + dy[dir];
						int nx = cx + dx[dir];

						if (ny < 0 || nx < 0 || ny >= n || nx >= n
							|| block_visited[ny][nx] || rainbow_visited[ny][nx])
							continue;
						//레인보우 블록이면 
						if (board[ny][nx] == 0) {
							rainbow_visited[ny][nx] = true;
							q.push({ ny,nx });
							block_cnt++;
							rainbow_cnt++;
						}
						//일반블록이면
						else if (board[ny][nx] == board[y][x]) {
							block_visited[ny][nx] = true;
							q.push({ ny,nx });
							block_cnt++;
						}
					}
				}
				pq.push({ y,x,block_cnt,rainbow_cnt });
			}
		}
	}
	//블록 생성이 안된다면
	if (pq.empty())
		return false;
	//우선 순위큐로 가장 큰 순 블록그룹이 정렬됌
	int y = pq.top().y;
	int x = pq.top().x;
	int block_cnt = pq.top().block_cnt;

	// 블록길이가 2보다 작다면
	if (block_cnt < 2)
		return false;

	result += (block_cnt * block_cnt);

	//삭제
	queue<pair<int, int>> q;
	q.push({ y,x });
	int block_idx = board[y][x];
	board[y][x] = -2;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
				continue;
			}
			if (board[ny][nx] == 0 || board[ny][nx] == block_idx) {
				q.push({ ny,nx });
				board[ny][nx] = -2;
			}
		}
	}
	return true;
}

//아래로 떨어짐
void gravity(void) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			if (board[j][i] == -2) {
				int y = j;
				int x = i;
				while (y > 0 && board[y][x] == -2)
					y--;
				if (board[y][x] == -1)
					continue;
				board[j][i] = board[y][x];
				board[y][x] = -2;
			}
		}
	}
}

//반시계 90도 회전
void rotate(void) {
	int tempBoard[20][20];
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			tempBoard[y][x] = board[y][x];
		}
	}
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			board[y][x] = tempBoard[x][n - 1 - y];
		}
	}
}

//시뮬레이션
void simulation(void) {
	result = 0;
	while (true) {
		int check = find_block();
		if (!check)
			break;
		gravity();
		rotate();
		gravity();
	}
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> board[y][x];
		}
	}
	simulation();
	cout << result << '\n';
	return 0;
}