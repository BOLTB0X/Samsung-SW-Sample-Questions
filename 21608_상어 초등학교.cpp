#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

//학생들의 자리배치
//만족도 계산

struct INF {
	int y, x, blank_cnt = 0, friendly_cnt = 0;
	//우선순위 변경
	bool operator < (const INF& i) const {
		//친한넘들이 많은 쪽
		if (friendly_cnt == i.friendly_cnt) {
			//빈칸이 많은 쪽
			if (blank_cnt == i.blank_cnt) {
				//행
				if (y == i.y)
					return y > i.y;
				//열
				else
					return x > i.x;
			}
			else
				return blank_cnt < i.blank_cnt;
		}
		else
			return friendly_cnt < i.friendly_cnt;
	}
};

struct STUDENT {
	int student_idx;
	int love[4];
	int y, x;
};

int n;
int map[20][20] = { 0, };
int satisfy[5] = { 0,1,10,100,1000 };
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

int simulation(vector<STUDENT>& student) {
	//자리배치
	for (int sit = 0; sit < n * n; sit++) {
		//우선순위 큐
		priority_queue<INF> pq;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j] == 0) {
					int blank_cnt = 0, friendly_cnt = 0;
					for (int dir = 0; dir < 4; dir++) {
						int ny = i + dy[dir];
						int nx = j + dx[dir];

						if (nx < 0 || ny < 0 || ny > n-1 || nx > n-1)
							continue;
						if (map[ny][nx] == 0)
							blank_cnt++;
						else {
							for (int k = 0; k < 4; k++) {
								if (map[ny][nx] == student[sit].love[k]) {
									friendly_cnt++;
									break;
								}
							}
						}
					}
					pq.push({ i,j,blank_cnt,friendly_cnt });
				}
			}
		}
		if (!pq.empty()) {
			int y = pq.top().y;
			int x = pq.top().x;

			map[y][x] = student[sit].student_idx;
			student[sit].y = y;
			student[sit].x = x;
		}
	}
	//만족도 계산
	int result = 0;
	for (int sit = 0; sit < n * n; sit++) {
		int y = student[sit].y;
		int x = student[sit].x;

		int friendly = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (nx < 0 || ny < 0 || ny > n-1 || nx > n-1)
				continue;
			for (int k = 0; k < 4; k++) {
				if (map[ny][nx] == student[sit].love[k]) {
					friendly++;
					break;
				}
			}
		}
		result += satisfy[friendly];
	}
	return result;
}


int main(void) {
	scanf("%d", &n);
	vector<STUDENT> student(n * n);
	//입력
	for (int i = 0; i < n * n; i++) {
		int idx;
		scanf("%d", &idx);
		student[i].student_idx = idx;
		for (int j = 0; j < 4; j++) {
			int love;
			scanf("%d", &love);
			student[i].love[j] = love;
		}
	}
	int ret = simulation(student);
	printf("%d", ret);
	return 0;
}
