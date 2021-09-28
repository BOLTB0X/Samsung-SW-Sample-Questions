#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct INFO {
	int y;
	int x;
	int blank_cnt;
	int love_cnt;

	bool operator < (const INFO& i) const {
		if (love_cnt == i.love_cnt) {
			if (blank_cnt == i.blank_cnt) {
				if (y == i.y)
					return x > i.x;
				return y > i.y;
			}
			return blank_cnt < i.blank_cnt;
		}
		return love_cnt < i.love_cnt;
	}
};

struct STUDENT {
	int studnet_idx;
	int love[4];
	int y, x;
};

int n, result;
int board[20][20];

const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };
const int satisfy[5] = { 0,1,10,100,1000 };

void setting_sit(vector<STUDENT>& students) {
	for (int i = 1; i <= n * n; i++) {
		priority_queue<INFO> pq;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				//비어있는 칸을 발견하면
				int near_blank = 0, near_love = 0;
				if (board[y][x] == 0) {
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];

						if (ny < 0 || nx < 0 || ny >= n || nx >= n)
							continue;
						if (board[ny][nx] == 0)
							near_blank++;
						else {
							for (int j = 0; j < 4; j++) {
								if (students[i].love[j] == board[ny][nx]) {
									near_love++;
									break;
								}
							}
						}
					}
					pq.push({ y,x,near_blank,near_love });
				}
			}
		}
		if (!pq.empty()) {
			int y = pq.top().y;
			int x = pq.top().x;
			int student_idx = students[i].studnet_idx;
			board[y][x] = student_idx;
			students[i].y = y;
			students[i].x = x;
		}
	}
	return;
}

void get_satisfy_score(vector<STUDENT>& students) {
	for (int i = 1; i <= n * n; i++) {
		int y = students[i].y;
		int x = students[i].x;
		
		int cnt = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			if (board[ny][nx] != 0) {
				for (int j = 0; j < 4; j++) {
					if (students[i].love[j] == board[ny][nx]) {
						cnt++;
						break;
					}
				}
			}
		}
		result += satisfy[cnt];
	}
}

void simulation(vector<STUDENT> &students) {
	setting_sit(students);
	get_satisfy_score(students);
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	vector<STUDENT> students((n * n) + 1);
	for (int i = 1; i <= n * n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		students[i].studnet_idx = a;
		students[i].love[0] = b;
		students[i].love[1] = c;
		students[i].love[2] = d;
		students[i].love[3] = e;
	}
	result = 0;
	simulation(students);
	cout << result << '\n';
	return 0;
}
