#include <iostream>
#include <queue>

using namespace std;

//우선순위 큐를 위한 
struct INFO {
	int y, x, block, rainbow;

	bool operator < (const INFO& i) const {
		if (block == i.block) {
			if (rainbow == i.rainbow) {
				if (y == i.y)
					return x < i.x;
				return y < i.y;
			}
			return rainbow < i.rainbow;
		}
		return block < i.block;
	}
};

int n, m, result;
int board[20][20];

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,1,-1 };

//블록그룹을 정하기 위한 너비우선탐색
pair<int, int> BFS(int y, int x, bool (*block_visited)[20]) {
	queue<pair<int, int>> q;
	bool rainbow_visited[20][20] = { false, };
	q.push({ y,x });
	block_visited[y][x] = true;
	
	//블록은 1 레인보우는 아직 0
	int block_cnt = 1, rainbow_cnt = 0;
	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		//상하좌우 탐색
		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			//범위초과
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			//재방문 및 블랙이면 
			if (block_visited[ny][nx] || rainbow_visited[ny][nx] || board[ny][nx] < 0)
				continue;

			//레인보우 블록인 경우
			if (board[ny][nx] == 0) {
				rainbow_visited[ny][nx] = true;
				//카운트
				block_cnt++;
				rainbow_cnt++;
				q.push({ ny,nx });
			}
			//일반블록인 경우
			else if (board[ny][nx] == board[y][x]) {
				block_visited[ny][nx] = true;
				block_cnt++;
				q.push({ ny,nx });
			}
		}
	}
	//카운트 된 횟수들 반환
	return { block_cnt,rainbow_cnt };
}

//블록 삭제 함수
void remove_block(int y, int x) {
	queue<pair<int, int>> q;
	q.push({ y,x });
	//블록그룹에서 사용된 번호 저장
	int block_idx = board[y][x];
	//삭제 처리
	board[y][x] = -2;
	
	//BFS 이용하여 탐색
	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];

			//범위 초과
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;

			//레인보우 or 일반블록이면
			if (board[ny][nx] == 0 || board[ny][nx] == block_idx) {
				q.push({ ny,nx });
				//삭제처리
				board[ny][nx] = -2;
			}
		}
	}
	return;
}

//블록찾기
bool find_block(void) {
	priority_queue<INFO> pq;
	bool block_visited[20][20] = { false, };

	//완전탐색으로 블록그룹이 가능 한지 탐색
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			//일반 블록
			if (board[y][x] > 0 && !block_visited[y][x]) {
				pair<int, int> ret = BFS(y, x, block_visited);
				pq.push({ y,x,ret.first,ret.second });
			}
		}
	}
	//우선순위큐가 비어있다면
	if (pq.empty())
		return false;
	//가장 최 상단 원소
	int y = pq.top().y;
	int x = pq.top().x;
	int block_size = pq.top().block;

	//그룹의 사이즈가 1이하면
	if (block_size < 2)
		return false;

	//점수득점
	result += (block_size * block_size);	
	//블록삭제
	remove_block(y, x);
	//여기까지 오면 참
	return true;
}

//중력 아래로 떨어짐
void gravity(void) {
	//삭제된 칸 탐색
	for (int i = 0; i < n; i++) {
		for (int j = n-1; j >= 0; j--) {
			//열이 이동이 아닌 행을 이동으로
			if (board[j][i] == -2) {
				int y = j;
				int x = i;
				//역으로 돌렸으니 못 내릴때가지 반복문으로 줄임
				while (y>0 && board[y][x] == -2) 
					y--;
				//검은 블록이면 패스
				if (board[y][x] == -1)
					continue;
				//기존 삭제된 칸 땡기기
				board[j][i] = board[y][x];
				board[y][x] = -2;
			}
		}
	}
	return;
}

//반시계 90도 회전
void board_rotate(void) {
	int cboard[20][20];
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			cboard[y][x] = board[y][x];

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			board[y][x] = cboard[x][n -1- y];
		}
	}
	return;
}

//시뮬레이션
void simulation(void) {
	result = 0;
	while (true) {
		bool flag = find_block();
		if (!flag)
			break;
		gravity();
		board_rotate();
		gravity();
	}
	return;
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
