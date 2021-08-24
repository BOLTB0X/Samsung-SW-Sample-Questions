#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int T;
deque<int> dq[5]; //���� ��Ϲ��� ȸ����
queue<pair<int, int>> q; //ȸ�� ������ ���� ť

void gear_rotate() {
	//ȸ�� ������ ��� ť�� ����������� ��
	while (!q.empty()) {
		int cur_num = q.front().first; //���� ȸ���� ��Ϲ���
		int rotate = q.front().second; //�ð�������� �ݽð��������
		q.pop();
		//�ð������ ���
		if (rotate == 1) {
			//���� �ϴܿ� �ִ� �� �ֻ������ �̵� 
			int tmp = dq[cur_num].back();
			dq[cur_num].pop_back();
			dq[cur_num].push_front(tmp);
		}
		//�ݽð������ ���
		else {
			//���� ��ܿ� �ִ��� ���ϴ����� �̵�
			int tmp = dq[cur_num].front();
			dq[cur_num].pop_front();
			dq[cur_num].push_back(tmp);
		}
	}
	return;
}

void gear_rotate_check(int gear_num, int gear_dir) {
	int idx = gear_num;
	int tmp_dir = gear_dir;
	//ť ����
	q.push({ idx,tmp_dir });

	//����Ȯ��
	while (true) {
		if (idx == 4) 
			break;
		idx++;
		tmp_dir *= -1;
		// ȸ���� �Ұ�� ���� ������ ť�� ����
		if (dq[idx - 1][2] != dq[idx][6])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	idx = gear_num;
	tmp_dir = gear_dir;
	//�� Ȯ��
	while (true) {
		if (idx == 1) 
			break;

		idx--;
		tmp_dir *= -1;
		//ȸ���� ��� ť�� ������ ����
		if (dq[idx + 1][6] != dq[idx][2]) //ȸ�� ����
			q.push({ idx,tmp_dir }); 
		else
			break;
	}
	//��¥ ��Ϲ��� ȸ������
	gear_rotate();
	return;
}

int get_score() {
	int score = 0;
	int check = 1;
	//��Ϲ��� ��ȣ�� �ö󰥼��� ==> 2^n-1
	for (int i = 1; i < 5; i++) {
		if (dq[i][0] == 1) 
			score += check;
		check *= 2;
	}
	return score;
}

int main(void) {
	//�ʱ�ȭ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//��Ϲ��� �Է�
	for (int i = 1; i < 5; i++) {
		string tmp_gear;
		cin >> tmp_gear;
		//��Ϲ����� ���� ��ť�� ����
		//��Ϲ��� ������ 01234567, N = 0, S = 1
		for (int j = 0; j < tmp_gear.length(); j++) 
			dq[i].push_back(tmp_gear[j] - '0');
	}
	//�׽�Ʈ ����
	cin >> T;
	while (T--) {
		int gear_num, gear_dir;
		cin >> gear_num >> gear_dir;
		//��¥ �������� ���ǿ� �´� �� üũ
		gear_rotate_check(gear_num, gear_dir);
		//q �ʱ�ȭ
		while (!q.empty()) 
			q.pop();
	}
	//����Ȯ��
	int ret = get_score();
	cout << ret << '\n';
	return 0;
}