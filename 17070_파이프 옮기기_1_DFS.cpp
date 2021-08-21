#include <iostream>
using namespace std;

int n;
int map[17][17];

//���� �밢�� ����
int dr[3] = { 0,1,1 };
int dc[3] = { 1,1,0 };
int result;

bool check(int r, int c, int dir) {
	//���η� ������ ���
	if (dir==0) {
		for (int i = 0; i < 1; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr<1 || nr>n || nc<1 || nc>n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	//�밢������ ������ ���
	else if (dir == 1) {
		for (int i = 0; i < 3; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr<1 || nr>n || nc<1 || nc>n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	//�������� ������ ���
	else if (dir == 2) {
		for (int i = 2; i < 3; i++) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr<1 || nr>n || nc<1 || nc>n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	return true;
}

void DFS(int r, int c, int dir) {
	if (r == n && c == n) {
		result++;
		return;
	}
	//������ �����϶�
	if (dir == 0) {
		// 0,1 ���� �밢��
		for (int i = 0; i < 2; i++) {
			if (check(r, c, i)) {
				DFS(r + dr[i], c + dc[i], i);
			}
		}
	}
	//�밢���϶�
	else if (dir == 1) {
		// 0,1,2 ���� �밢�� ����
		for (int i = 0; i < 3; i++) {
			if (check(r, c, i)) {
				DFS(r + dr[i], c + dc[i], i);
			}
		}
	}
	//�����϶�
	else if (dir == 2) {
		// 1,2 ���� �밢�� ����
		for (int i = 1; i < 3; i++) {
			if (check(r, c, i)) {
				DFS(r + dr[i], c + dc[i], i);
			}
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			cin >> map[r][c];
		}
	}

	DFS(1, 2, 0);
	cout << result << '\n';
	return 0;
}