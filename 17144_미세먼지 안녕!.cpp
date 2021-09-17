#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

struct INF {
	int y, x;
};

int n, m, T;
int map[50][50];
int tmp_map[50][50];

//����û���� ��ġ�� ��� �迭
INF clean[2];
//��������
const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,1,0,-1 };

//�� ����
void map_copy(int(*from)[50], int(*to)[50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = from[i][j];
		}
	}
}

//�� ����
int get_score(void) {
	int tot = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (map[y][x] >= 1)
				tot += map[y][x];
		}
	}
	return tot;
}

//�̼����� Ȯ��
void diffusion(void) {
	map_copy(map,tmp_map);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			//���� ������ �ʱ� ��
			//tmp_map���� Ȯ��� ���� �͵� �����ϰ� ��
			//�� ���� �������� ������ ���� ������ �ڼ���
			if (map[y][x] != 0 && map[y][x] != -1) {
				//�̵��������� Ȯ��
				int d = map[y][x] / 5;
				//�������� Ƚ��
				int move_cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int ny = y + dy[dir];
					int nx = x + dx[dir];
					if (ny < 0 || nx < 0 || ny >= n || nx >= m)
						continue;
					if (map[ny][nx] == -1)
						continue;
					tmp_map[ny][nx] += d;
					move_cnt++;
				}
				//��������
				tmp_map[y][x] -= (d * move_cnt);
			}
		}
	}
	//�ӽø��� �ٽ� ������ ����
	map_copy(tmp_map, map);
}

//��ŸƮ
void clean_start(void) {
	for (int idx = 0; idx < 2; idx++) {
		//�ݽð�
		if (idx == 0) {
			//�� ���������� 0����
			for (int i = clean[idx].y - 1; i > 0; i--) {
				map[i][0] = map[i - 1][0];
			}
			// �� ���� ��ĭ�� ȸ��
			for (int i = 0; i < m - 1; i++) {
				map[0][i] = map[0][i + 1];
			}
			// �� ���� ������ ���� 
			for (int i = 1; i<= clean[idx].y;i++) {
				map[i-1][m-1] = map[i][m-1];
			}
			//�� ���������� 0���� ������ ����
			for (int i = m - 1; i > 1; i--) {
				map[clean[idx].y][i] = map[clean[idx].y][i - 1];
			}
			map[clean[idx].y][1] = 0;
		}
		//�ð����
		else {
			for (int i = clean[idx].y + 1; i < n - 1; i++) {
				map[i][0] = map[i + 1][0];
			}
			for (int i = 0; i < m - 1; i++) {
				map[n - 1][i] = map[n - 1][i + 1];
			}
			for (int i = n - 1; i >= clean[idx].y; i--) {
				map[i][m - 1] = map[i - 1][m - 1];
			}
			for (int i = m - 1; i > 1; i--) {
				map[clean[idx].y][i] = map[clean[idx].y][i-1];
			}
		}
		map[clean[idx].y][1] = 0;
	}
	return;
}

int simulation(void) {
	for (int i = 0; i < T; i++) {
		diffusion();
		clean_start();
	}
	int result = get_score();
	return result;
}

int main(void) {
	scanf("%d %d %d", &n, &m, &T);
	int idx = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
			//����û������ ���
			if (map[y][x] == -1) {
				clean[idx] = { y,x };
				idx++;
			}
		}
	}
	int ret = simulation();
	printf("%d", ret);
	return 0;
}