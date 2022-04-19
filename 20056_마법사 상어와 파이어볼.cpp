#include<iostream>
#include<vector>
#include<cstring> 

using namespace std;

typedef struct {
	int y, x, m, s, d;
}Fire;

vector<Fire> board[51][51];
vector<Fire> ball;

const int dy[8] = { -1, -1, 0, 1, 1, 1, 0,-1 };
const int dx[8] = { 0, 1, 1, 1, 0, -1,-1,-1 };

// 초기화
void init(int N) {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			board[i][j].clear();
	}
	return;
}

// 3 -3 
bool is_odd_even(int y, int x) {
	bool o_flag = 0;
	bool e_flag = 0;

	for (Fire& b : board[y][x]) {
		if (b.d % 2 == 0)
			e_flag = 1;
		else
			o_flag = 1;
	}

	if ((e_flag && !o_flag) || (!e_flag && o_flag))
		return 1;
	else 
		return 0;
}

// 1번 조건
void move_fire(int N) {
	for (Fire& b : ball) {
		int cy = b.y;
		int cx = b.x;
		int m = b.m;
		int s = b.s;
		int d = b.d;

		int ny = cy + (dy[d] * s);
		int nx = cx + (dx[d] * s);

		while (ny < 1)
			ny += N;
		while (nx < 1)
			nx += N;
		while (ny > N)
			ny -= N;
		while (nx > N)
			nx -= N;

		board[ny][nx].push_back({ ny,nx,m,s,d });
	}
	return;
}

// 2번
void board_update(int N) {
	vector<Fire> tmp;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			// 없을 경우
			if (board[i][j].empty())
				continue;

			// 파이어볼이 하나일 경우
			if (board[i][j].size() == 1) 
				tmp.push_back(board[i][j][0]);
			
			// 2개 이상
			else if (board[i][j].size() >= 2) {
				int mtot = 0, stot = 0; // 총 질량과 속력

				for (auto& b : board[i][j]) {
					mtot += b.m;
					stot += b.s;
				}

				int avg_m = mtot / 5;
				int avg_s = stot / board[i][j].size();

				// 질량이 0인 경우
				if (avg_m == 0)
					continue;

				if (is_odd_even(i, j)) {
					tmp.push_back({ i,j,avg_m, avg_s, 0 });
					tmp.push_back({ i,j,avg_m, avg_s, 2 });
					tmp.push_back({ i,j,avg_m, avg_s, 4 });
					tmp.push_back({ i,j,avg_m, avg_s, 6 });
				}
				else {
					tmp.push_back({ i,j,avg_m, avg_s, 1 });
					tmp.push_back({ i,j,avg_m, avg_s, 3 });
					tmp.push_back({ i,j,avg_m, avg_s, 5 });
					tmp.push_back({ i,j,avg_m, avg_s, 7 });
				}
			}
		}
	}
	ball = tmp;
	return;
}

int solution(int N, int M, int K) {
	int answer = 0;

	while (K--) {
		init(N); // 맵 초기화
		move_fire(N); // 이동
		board_update(N); // 업데이트
	}

	// 남아있는 질량의 합
	for (Fire& b : ball)
		answer += b.m;
	return answer;
}

int main(void) {
	int N, M, K;

	cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) {
		int a, b, c, d, e;

		cin >> a >> b >> c >> d >> e;
		ball.push_back({ a,b,c,d,e });
	}
	
	int ret = solution(N, M, K);
	cout << ret;
	return 0;
}
