#include <iostream>
using namespace std;

typedef struct {
	int y, x, type;
} INF;

int n, m, result;
int map[8][8];
INF cctvs[8];
int cctv_size;

const int angle_types[5] = { 4,2,4,4,1 };

//�ּ�
int min(int a, int b) {
	return a < b ? a : b;
}

//�� ����
void map_copy(int(*from)[8], int(*to)[8]) {
	for (int c = 0; c < n; c++)
		for (int r = 0; r < m; r++)
			to[c][r] = from[c][r];
	return;
}

//ī�޶� Ÿ��,������ ���� �ùķ��̼�
void simulation(int dir, INF cctv) {
	dir = (dir % 4);

	if (dir == 0) {
		for (int x = cctv.x; x < m; x++) {
			if (map[cctv.y][x] == 6)
				break;
			map[cctv.y][x] = -1; //����ó��
		}
	}
	if (dir == 1) {
		for (int y = cctv.y; y >= 0; y--) {
			if (map[y][cctv.x] == 6)
				break;
			map[y][cctv.x] = -1; //����ó��
		}
	}
	if (dir == 2) {
		for (int x = cctv.x; x >= 0; x--) {
			if (map[cctv.y][x] == 6)
				break;
			map[cctv.y][x] = -1; //����ó��
		}
	}
	if (dir == 3) {
		for (int y = cctv.y; y < n; y++) {
			if (map[y][cctv.x] == 6)
				break;
			map[y][cctv.x] = -1; //����ó��
		}
	}
	return;
}

//DFS�� �̿��� ��Ʈ��ŷ
void DFS(int cctv_idx) {
	//��� Ż�� ����
	if (cctv_idx == cctv_size) {
		int tmp_result = 0;
		for (int c = 0; c < n; c++) {
			for (int r = 0; r < m; r++) {
				if (map[c][r] == 0)
					tmp_result++;
			}
		}
		result = min(tmp_result, result);
		return;
	}
	//�� �����
	int backup[8][8];
	int cctv_type = cctvs[cctv_idx].type;
	//cctv�������� �ޱ۰���
	for (int dir = 0; dir < angle_types[cctv_type]; dir++) {
		//�ʺ���
		map_copy(map, backup);
		if (cctv_type == 0) {
			simulation(dir, cctvs[cctv_idx]);
		}
		if (cctv_type == 1) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
		}
		if (cctv_type == 2) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
		}
		if (cctv_type == 3) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
		}
		if (cctv_type == 4) {
			simulation(dir, cctvs[cctv_idx]);
			simulation(dir + 1, cctvs[cctv_idx]);
			simulation(dir + 2, cctvs[cctv_idx]);
			simulation(dir + 3, cctvs[cctv_idx]);
		}
		DFS(cctv_idx + 1);
		map_copy(backup, map);
	}
}

int main(void) {
	//�ʱ�ȭ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//�Է�
	cin >> n >> m;
	for (int c = 0; c < n; c++) {
		for (int r = 0; r < m; r++) {
			cin >> map[c][r];
			if (map[c][r] >= 1 && map[c][r] <= 5) {
				cctvs[cctv_size].y = c;
				cctvs[cctv_size].x = r;
				cctvs[cctv_size].type = map[c][r] - 1;
				cctv_size++;
			}
		}
	}
	//�ּ� ���� ���� �ִ밪 ����
	result = 0x7fffffff;
	//��Ʈ��ŷ 
	DFS(0);
	cout << result << '\n';
	return 0;
}
