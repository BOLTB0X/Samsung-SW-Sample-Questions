#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 25

using namespace std;

struct shark_student {
	int number;
	int friendly_student[4];
};

struct pos {
	int r, c;
	int nearly_empty;
	int nearly_friendly_student;
};

//1. 빈 칸 중에서, 좋아하는 학생이 인접한 칸에 많은 곳으로 1차적으로 배치.
//2. 1번 조건을 여러 칸이 만족한다면, 인접한 칸에 빈 칸이 많은 곳으로 2차적으로 배치.
//3. 2번 조건을 여러 칸이 만족한다면, 행이 가장 작은 칸으로 3차적으로 배치.
//4. 3번 조건을 여러 칸이 만족한다면, 열이 가장 작은 칸으로 최종적으로 배치.

bool compare(pos a, pos b) {
	if (a.nearly_friendly_student >= b.nearly_friendly_student) {
		if (a.nearly_friendly_student == b.nearly_friendly_student) {
			if (a.nearly_empty >= b.nearly_empty) {
				if (a.nearly_empty == b.nearly_empty) {
					if (a.r <= b.r) {
						if (a.r == b.r) {
							if (a.c < b.c) {
								return true;
							}
							return false;
						}
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

//자리 배치를 위해 필요한 정보들을 구조체 'pos'으로 만들어서 관리.
//이 구조체를 자료형으로 가지는 vector를 선언해서 실제로 자리를 배치할 것

int n, answer = 0;
int map[MAX][MAX];
shark_student student_arr[MAX * MAX];
vector<shark_student> student_v;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void simulation(void) {
	//먼저 위치선정
	for (int i = 0; i < student_v.size(); i++) {
		vector<pos> position;
		int student_idx = student_v[i].number;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				//차있으니
				if (map[r][c] != 0) 
					continue;
				int near_shark = 0;
				int near_emp = 0;
				//근처 탐색
				for (int dir = 0; dir < 4; dir++) {
					int nr = r + dr[dir];
					int nc = c + dc[dir];
					
					if (nr < 0 || nc < 0 || nr >= n || nc >= n)
						continue;
					if (map[nr][nc] == 0)
						near_emp++;
					else {
						for (int d = 0; d < 4; d++) {
							int friend_num = student_v[i].friendly_student[d];
							if (map[nr][nc] == friend_num) {
								near_shark++;
								break;
							}
						}
					}
				}
				position.push_back({ r,c,near_emp,near_shark });
			}
		}
		sort(position.begin(), position.end(), compare);
		int pos_r = position[0].r;
		int pos_c = position[0].c;
		map[pos_r][pos_c] = student_idx;
	}
}

int check_calculate(int f) {
	if (f == 0) 
		return 0;
	if (f == 1)
		return 1;
	if (f == 2)
		return 10;
	if (f == 3)
		return 100;
	if (f == 4)
		return 1000;
}

void satisfy_check() {
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int student_idx = map[r][c];
			int friendly_student = 0;

			for (int dir = 0; dir < 4; dir++) {
				int nr = r + dr[dir];
				int nc = c + dc[dir];

				if (nr < 0 || nc < 0 || nr >= n || nc >= n)
					continue;
				for (int d = 0; d < 4; d++) {
					int friendly_student_idx = student_arr[student_idx].friendly_student[d];
					if (map[nr][nc] == friendly_student_idx) {
						friendly_student++;
						break;
					}
				}
			}
			answer += check_calculate(friendly_student);
		}
	}
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n;
	for (int i = 0; i < n * n; i++) {
		int num, n1, n2, n3, n4;
		cin >> num >> n1 >> n2 >> n3 >> n4;
		student_v.push_back({ num,{n1,n2,n3,n4} });
		student_arr[num].number = num;
		student_arr[num].friendly_student[0] = n1;
		student_arr[num].friendly_student[1] = n2;
		student_arr[num].friendly_student[2] = n3;
		student_arr[num].friendly_student[3] = n4;
	}
	simulation();
	satisfy_check();
	cout << answer << '\n';
	return 0;
}