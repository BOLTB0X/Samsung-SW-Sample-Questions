#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	int y, x, type;
} INF;

int n, m,result;
int map[8][8];
INF cctvs_arr[8];
int cctvs_size = 0;
//�� cctv�� ȸ�� ���� ��
const int turn_type[5] = { 4,2,4,4,1 };

int min(int a, int b) {
	return a < b ? a : b;
}

void map_copy(int(*from)[8], int(*to)[8]) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}
//ȸ���� ���� ���ù��� üũ
void simulation(int dir, INF cctv) {
	//�� �� �� �� (�� ��) (�� ��)
	dir = (dir % 4);
	//��
	if (dir == 0) {
		for (int x = cctv.x; x < m; x++) {
			//���� ������ 
			if (map[cctv.y][x] == 6)
				break;
			//����ó��
			map[cctv.y][x] = -1;
		}
	}
	//��
	if (dir == 1) {
		for (int y = cctv.y; y >=0; y--) {
			//���� ������ 
			if (map[y][cctv.x] == 6)
				break;
			//����ó��
			map[y][cctv.x] = -1;
		}
	}
	//��
	if (dir == 2) {
		for (int x = cctv.x; x >= 0; x--) {
			//���� ������ 
			if (map[cctv.y][x] == 6)
				break;
			//����ó��
			map[cctv.y][x] = -1;
		}
	}
	//��
	if (dir == 3) {
		for (int y = cctv.y; y < n; y++) {
			//���� ������ 
			if (map[y][cctv.x] == 6)
				break;
			//����ó��
			map[y][cctv.x] = -1;
		}
	}
	return;
}

//�������� ã��
int get_score() {
	int cnt=0;
	for (int y = 0; y < n; y++) 
		for (int x = 0; x < m; x++) 
			if (map[y][x] == 0)
				cnt++;
	return cnt;
}

//DFS�� �̿��� ��Ʈ��ŷ
void DFS(int cctvs_idx) {
	//Ż������
	if (cctvs_idx == cctvs_size) {
		result = min(result, get_score());
		return;
	}
	//����� �ӽø�
	int backup_map[8][8];
	//�迭�� ��� cctv����
	int cctv_type = cctvs_arr[cctvs_idx].type;
	//cctv�� ȸ�������� ���� �迭�� ���̸�ŭ Ž������
	for (int dir = 0; dir < turn_type[cctv_type]; dir++) {
		map_copy(map, backup_map);
		//1�� ī�޶��� ���
		if (cctv_type == 0) {
			simulation(dir, cctvs_arr[cctvs_idx]);
		}
		//2�� ī�޶��� ���
		if (cctv_type == 1) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
		}
		//3�� ī�޶��� ���
		if (cctv_type == 2) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
		}
		//3�� ī�޶��� ���
		if (cctv_type == 3) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
		}
		//3�� ī�޶��� ���
		if (cctv_type == 4) {
			simulation(dir, cctvs_arr[cctvs_idx]);
			simulation(dir + 1, cctvs_arr[cctvs_idx]);
			simulation(dir + 2, cctvs_arr[cctvs_idx]);
			simulation(dir + 3, cctvs_arr[cctvs_idx]);
		}
		DFS(cctvs_idx + 1);
		map_copy(backup_map, map);
	}
	return;
}

int main(void) {
	//�� �Է�
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
			//cctv�� �Է¹�����
			if (map[y][x] >= 1 && map[y][x] <= 5) {
				cctvs_arr[cctvs_size].y = y;
				cctvs_arr[cctvs_size].x = x;
				//cctv��ȣ ȸ���迭�� ���߱� ����
				cctvs_arr[cctvs_size].type = map[y][x] - 1;
				cctvs_size++;
			}
		}
	}
	//��Ʈ��ŷ ����
	result = 0x7fffffff;
	DFS(0);
	printf("%d", result);
	return 0;
}