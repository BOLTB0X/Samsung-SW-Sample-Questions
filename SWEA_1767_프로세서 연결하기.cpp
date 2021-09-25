#include <iostream>
#include <vector>

using namespace std;

//코어 정보
struct CORE {
	int y, x;
};

int n, max_connect, min_len;
int board[12][12];
vector<CORE> v;

//이동방향
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//DFS
void DFS(int idx, int len, int connect) {
	if (idx == v.size()) {
		if (connect > max_connect) {
			min_len = len;
			max_connect = connect;
		}
		else if (connect == max_connect)
			min_len = min(min_len, len);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int ny = v[idx].y;
		int nx = v[idx].x;
		int cnt = 0;
		//한 방향으로 쭈우욱 전선 연결
		while (true) {
			ny += dy[i];
			nx += dx[i];
			cnt++;
			//다른 코어나 전선을 만난다면
			if (board[ny][nx] == 1 || board[ny][nx] == 2) {
				cnt = 0;
				break;
			}
			if (board[ny][nx] == 0 && (nx == 0 || ny == 0 || nx == n - 1 || ny == n - 1))
				break;
		}
		//쭈우욱 전선 처리
		if (cnt > 0) {
			ny = v[idx].y;
			nx = v[idx].x;
			while (true) {
				ny += dy[i];
				nx += dx[i];
				if (nx < 0 || ny < 0 || nx > n - 1 || ny > n - 1)
					break;
				board[ny][nx] = 2;
			}
			DFS(idx + 1, len + cnt, connect + 1);
			ny = v[idx].y;
			nx = v[idx].x;
			while (true) {
				ny += dy[i];
				nx += dx[i];
				if (nx < 0 || ny < 0 || nx > n - 1 || ny > n - 1)
					break;
				board[ny][nx] = 0;
			}
		}
	}
	DFS(idx + 1, len, connect);
}

//시뮬레이션
void simulation(void) {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n;
		//맵초기화
		v.clear();
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				cin >> board[y][x];
				if (board[y][x] == 1) {
					if (y == 0 || x == 0 || y == n - 1 || x == n - 1)
						continue;
					//코어 벡터에 저장
					v.push_back({ y,x });
				}
			}
		}
		max_connect = 0;
		min_len = 0x7fffffff;
		DFS(0, 0, 0);
		cout << "#" << t << " " << min_len << '\n';
	}
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	simulation();
	return 0;
}