#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int s, d, z; //�ӷ�, �̵�����, ũ��
}shark;

typedef struct {
	int r, c, s, d, z;
	//row,col,speed,dir,size;
}shark_inf;

int r, c, k;
vector<shark> map[101][101];
//��� �������� �����ϴ� ����
vector<shark_inf> moving_shark;
//���� �� �����ϴ� ����
vector<shark> caught;
//�� �Ʒ� �� ��
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,1,-1 };

bool is_range(int nr, int nc) {
	if (nr < 0 || nc < 0 || nr >= r || nc >= c)
		return false;
	return true;
}

int turn_dir(int d) {
	if (d == 0) return 1;
	else if (d == 1) return 0;
	else if (d == 2) return 3;
	else if (d == 3) return 2;
}

void catch_shark(int king_cur) {
	shark tmp_shark;
	//���ÿ��� �ִ� ���� ����� ������ Ȯ��
	for (int i = 0; i < r; i++) {
		if (!map[i][king_cur].empty()) {
			tmp_shark = map[i][king_cur][0];
			map[i][king_cur].clear(); //������� ����
			caught.push_back(tmp_shark);
			break;
		}
	}
}

//�� ����� ������ ����̿�
shark_inf moving_single_shark(int row, int col, shark cur_shark) {
	shark_inf tmp_inf;

	int nr = row;
	int nc = col;
	int cnt;

	if (cur_shark.d == 0 || cur_shark.d == 1)
		cnt = cur_shark.s % ((r - 1) * 2);
	else 
		cnt = cur_shark.s % ((c - 1) * 2);

	for (int i = 0; i < cnt; i++) {
		nr += dr[cur_shark.d];
		nc += dc[cur_shark.d];

		if (!is_range(nr, nc)) {
			cur_shark.d = turn_dir(cur_shark.d);
			nr = nr + dr[cur_shark.d] * 2;
			nc = nc + dc[cur_shark.d] * 2;
		}
	}
	tmp_inf = { nr,nc,cur_shark.s,cur_shark.d,cur_shark.z };
	return tmp_inf;
}

//ū���� ����
shark shark_crash(vector<shark> crash) {
	int max_z = 0;
	shark tmp_shark = crash[0];

	for (int i = 0; i < crash.size(); i++) {
		if (max_z < crash[i].z) {
			tmp_shark = crash[i];
			max_z = crash[i].z;
		}
	}
	return tmp_shark;
}

void move_shark(void) {
	//ȣ���Ҷ� ����� �̵��� �������Ƿ� �ʱ�ȭ
	moving_shark.clear();

	shark_inf tmp_inf;
	shark tmp_shark;

	//�����̴� ������ moving_shark ���Ϳ� ����
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			//������ �ش���ġ �ʿ� ������
			if (!map[i][j].empty()) {
				tmp_inf = moving_single_shark(i, j, map[i][j][0]);
				map[i][j].pop_back();
				moving_shark.push_back(tmp_inf);
			}
		}
	}
	//moving_shark���Ϳ� ������Ʈ������ ���������� �ʿ� ����
	for (int i = 0; i < moving_shark.size(); i++) {
		tmp_inf = moving_shark[i];
		tmp_shark = { tmp_inf.s,tmp_inf.d,tmp_inf.z };
		map[tmp_inf.r][tmp_inf.c].push_back(tmp_shark);
	}

	//���࿡ �� ���� �θ��� �̻��� ���
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j].size() >1) {
				tmp_shark = shark_crash(map[i][j]);
				map[i][j].clear();
				map[i][j].push_back(tmp_shark);
			}
		}
	}
	return;
}

void simulation(void) {
	//���ÿ��� �׻� ���������� �̵���
	for (int king = 0; king < c; king++) {
		// ��ĭ �� �̵��ϸ� 
		catch_shark(king); //���� ���ִ� ��
		move_shark(); //������ ������
	}
	return;

}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> r >> c >> k;
	shark tmp_shark;

	int tmp_r, tmp_c, tmp_s, tmp_d, tmp_z;
	int answer = 0;
	//�ʻ��� �� ��� �����Է�
	for (int i = 0; i < k; i++) {
		cin >> tmp_r >> tmp_c >> tmp_s >> tmp_d >> tmp_z;
		tmp_shark = { tmp_s,tmp_d - 1,tmp_z };
		map[tmp_r - 1][tmp_c - 1].push_back(tmp_shark);
	}
	//�ùķ��̼� ����
	simulation();
	// ���� ��� ũ���� ���� ���
	for (int i = 0; i < caught.size(); i++) {
		answer += caught[i].z;
	}
	cout << answer << '\n';
	return 0;
}