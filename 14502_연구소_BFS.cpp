#include <iostream>
#include <queue>
using namespace std;

int n, m;
int map[8][8]; 
int tmp_map[8][8]; //�Է¿�
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int answer = 0;

//temp�� ���� map�� �����ϴ� �Լ�
void copyMap(int(*from)[8], int(*to)[8]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = from[i][j];
		}
	}
}

void virus() {
	int result[8][8];
	copyMap(tmp_map, result);
	//���̷����� �ִ� ��(2)�� ����� ������Ų��.
	queue<pair<int, int>> que;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (result[i][j] == 2) {
				que.push({ i, j });
			}
		}
	}
	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if (result[nx][ny] == 0) {
					result[nx][ny] = 2;
					que.push({ nx, ny });
				}
			}
		}
	}
	//���̷����� �������� ���� ��(0)�� �����ش�.
	int noVirus = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (result[i][j] == 0) 
				noVirus++;
		}
	}
	answer = max(noVirus, answer);
}

//[���Ʈ����] ������ ��� ����� ���� ���� 3�� ����, ����̿�
void make_wall(int cnt) {
	if (cnt == 3) {
		virus();
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp_map[i][j] == 0) {
				tmp_map[i][j] = 1; //�������
				make_wall(cnt + 1); //�� ���� Ƚ���� +1
				tmp_map[i][j] = 0; //������ ���·� ���ư���(���㹰��)
			}
		}
	}
}
int main(void) {
	//�� ����
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	//�� ��ġ���� ���� �����.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				copyMap(map, tmp_map);
				tmp_map[i][j] = 1; // �������
				make_wall(1); //�� �ϳ� �������Ƿ� cnt = 1
				tmp_map[i][j] = 0; //���㹰��(���� ���·� ���ư���)
			}
		}
	}
	//output
	cout << answer <<'\n';
	return 0;
}