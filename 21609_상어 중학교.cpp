#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//�켱���� ť�� ���� ����ü
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

//��ϱ׷� ã��
bool find_block(void) {
	bool block_visited[20][20] = { false, };
	priority_queue<INFO> pq;

	//��� ����
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			//�Ϲ� ��� ����
			if (board[y][x] > 0 && !block_visited[y][x]) {
				bool rainbow_visited[20][20] = { false, };
				queue<pair<int, int>> q;
				q.push({ y,x });
				block_visited[y][x] = true;

				//���� ������� ������� ��ϱ׷��� �Ǵ� �� Ȯ��
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
						//���κ��� ����̸� 
						if (board[ny][nx] == 0) {
							rainbow_visited[ny][nx] = true;
							q.push({ ny,nx });
							block_cnt++;
							rainbow_cnt++;
						}
						//�Ϲݺ���̸�
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
	//��� ������ �ȵȴٸ�
	if (pq.empty())
		return false;
	//�켱 ����ť�� ���� ū �� ��ϱ׷��� ���ĉ�
	int y = pq.top().y;
	int x = pq.top().x;
	int block_cnt = pq.top().block_cnt;

	// ��ϱ��̰� 2���� �۴ٸ�
	if (block_cnt < 2)
		return false;

	result += (block_cnt * block_cnt);

	//����
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

//�Ʒ��� ������
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

//�ݽð� 90�� ȸ��
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

//�ùķ��̼�
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
	//�ʱ�ȭ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//�Է�
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