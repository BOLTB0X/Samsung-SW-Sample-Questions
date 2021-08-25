#include <cstdio>
#include <queue>
using namespace std;

struct imf {
	int r;
	int c;
	int dir;
};

int n;
int map[17][17];
int result = 0;
//�������
const int dr[3] = { 0,1,1 };
const int dc[3] = { 1,1,0 };

bool check(int row, int col, int direction) {
	//������ ������ ���
	if (direction == 0) {
		for (int i = 0; i < 1; i++) {
			int nr = row + dr[i];
			int nc = col + dc[i];

			if (nr <= 0 || nr > n || nc <= 0 || nc > n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	//������ �밢���� ���
	else if (direction == 1) {
		for (int i = 0; i < 3; i++) {
			int nr = row + dr[i];
			int nc = col + dc[i];

			if (nr <= 0 || nr > n || nc <= 0 || nc > n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	//������ ���
	else if (direction == 2) {
		for (int i = 2; i < 3; i++) {
			int nr = row + dr[i];
			int nc = col + dc[i];

			if (nr <= 0 || nr > n || nc <= 0 || nc > n)
				return false;
			if (map[nr][nc] != 0)
				return false;
		}
	}
	return true;
}

void BFS(int r, int c, int direction) {
	queue<imf> q;
	q.push({ r,c,direction });
	while (!q.empty()) {
		 int cur_r = q.front().r;
		 int cur_c = q.front().c;
		 int cur_dir = q.front().dir;
		 q.pop();

		 if (cur_r == n && cur_c == n) {
			 result += 1;
			 continue;
		 }
		 //������ ������ ���
		 if (direction == 0) {
			 //������ �� �ִ� ������ ����, �밢
			 for (int i = 0; i < 2; i++) {
				 //������ �����ϴٸ�
				 if (check(r, c, i))
					 BFS(r + dr[i], c + dc[i], i);
			 }
		 }
		 //������ �밢���� ���
		 // Ʈ���� ����ó�� ����̹Ƿ� else if
		 else if (direction == 1) {
			 //������ �� �ִ� ������ ����, �밢, ����
			 for (int i = 0; i < 3; i++) {
				 //������ �����ϴٸ�
				 if (check(r, c, i))
					 BFS(r + dr[i], c + dc[i], i);
			 }
		 }
		 //������ ������ ���
		 // Ʈ���� ����ó�� ����̹Ƿ� else if
		 else if (direction == 2) {
			 //������ �� �ִ� ������ �밢, ����
			 for (int i = 1; i < 3; i++) {
				 //������ �����ϴٸ�
				 if (check(r, c, i))
					 BFS(r + dr[i], c + dc[i], i);
			 }
		 }
	}
}

int main(void) {
	//�Է�
	scanf("%d", &n);

	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			scanf("%d", &map[r][c]);
		}
	}
	BFS(1, 2, 0);
	printf("%d", result);
	return 0;
}