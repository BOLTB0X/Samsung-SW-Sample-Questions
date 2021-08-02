#include <iostream>
using namespace std;

int n, m; //����,����
int map[8][8];
int tmp_map[8][8];

//�̵�����
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int answer=0;

int max(int a, int b) {
	return a > b ? a : b;
}

void virus(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		
		//�̵������� ������ �´´ٸ�
		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (tmp_map[nx][ny] == 0) {
				tmp_map[nx][ny] = 2;
				virus(nx, ny); //��� ȣ��
			}
		}
	}
}

int get_score() {
	int score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp_map[i][j] == 0)
				//�������� ī��Ʈ
				score += 1;
		}
	}
	return score;
}

void DFS(int cnt) {
	if (cnt == 3) {
		//��Ÿ�� 3�� �϶�, Ȯ���� ���� �ӽ÷� �ű�
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tmp_map[i][j] = map[i][j];
			}
		}
		//���̷��� ��ġ���� Ȯ�� ����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (tmp_map[i][j] == 2)
					virus(i, j); //��� ȣ��
			}
		}
		//�� ����ġ �� ���̷��� Ȯ�� ���̽����� üũ
		answer = max(get_score(), answer);
		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				cnt += 1;
				map[i][j] = 1;
				DFS(cnt); //���ȣ��
				//�ٽ� ��Ÿ�� ����
				cnt -= 1;
				map[i][j] = 0;
			}
		}
	}
}

int main(void) {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	DFS(0);
	cout << answer << '\n';
	return 0;
}