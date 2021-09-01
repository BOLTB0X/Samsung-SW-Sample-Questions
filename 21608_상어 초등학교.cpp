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

//1. �� ĭ �߿���, �����ϴ� �л��� ������ ĭ�� ���� ������ 1�������� ��ġ.
//2. 1�� ������ ���� ĭ�� �����Ѵٸ�, ������ ĭ�� �� ĭ�� ���� ������ 2�������� ��ġ.
//3. 2�� ������ ���� ĭ�� �����Ѵٸ�, ���� ���� ���� ĭ���� 3�������� ��ġ.
//4. 3�� ������ ���� ĭ�� �����Ѵٸ�, ���� ���� ���� ĭ���� ���������� ��ġ.

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

//�ڸ� ��ġ�� ���� �ʿ��� �������� ����ü 'pos'���� ���� ����.
//�� ����ü�� �ڷ������� ������ vector�� �����ؼ� ������ �ڸ��� ��ġ�� ��

int n, answer = 0;
int map[MAX][MAX];
shark_student student_arr[MAX * MAX];
vector<shark_student> student_v;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void simulation(void) {
	//���� ��ġ����
	for (int i = 0; i < student_v.size(); i++) {
		vector<pos> position;
		int student_idx = student_v[i].number;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				//��������
				if (map[r][c] != 0) 
					continue;
				int near_shark = 0;
				int near_emp = 0;
				//��ó Ž��
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

	//�Է�
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