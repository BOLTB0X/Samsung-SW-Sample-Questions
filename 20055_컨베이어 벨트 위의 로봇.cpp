#include <iostream>

using namespace std;

//��Ʈ�� �� ���
struct BLOCK {
	int d;
	bool is_robot;
};

//������ ������Ű���� �Ǵ�
bool is_break(int n, int k, BLOCK* belts) {
	int zero_cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (belts[i].d == 0)
			zero_cnt++;
	}
	if (zero_cnt >= k)
		return true;
	return false;
}

//��Ʈ�� ȸ���Լ�
void blets_rotate(int n, BLOCK* belts) {
	BLOCK tmp = belts[2 * n-1];
	for (int i = (2 * n) -2; i >= 0; i--) {
		belts[i + 1] = belts[i];
	}
	belts[0] = tmp;

	if (belts[n-1].is_robot)
		belts[n-1].is_robot = false;
	return;
}

//�κ� �̵� �Լ�
void robot_move(int n, BLOCK* belts) {
	for (int i = n - 2; i >= 0; i--) {
		if (belts[i].is_robot) {
			if (belts[i + 1].d >= 1 && !belts[i + 1].is_robot) {
				belts[i].is_robot = false;
				belts[i + 1].is_robot = true;
				belts[i + 1].d--;
			}
		}
	}
	if (belts[n-1].is_robot)
		belts[n-1].is_robot = false;
	return;
}

//�κ� �ø��� �Լ�
void robot_input(int n, BLOCK* belts) {
	//�ø��� ��ġ�� Ȯ��
	if (!belts[0].is_robot && belts[0].d >= 1) {
		belts[0].is_robot = true;
		belts[0].d --;
	}
}

//�ùķ��̼�
int simulation(int n, int k, BLOCK* belts) {
	//�÷���ī��Ʈ �ʱ�ȭ
	int play_cnt = 0;
	while (true) {
		//���� �� �ٷ� �����ϴ� �� �˻�
		if (is_break(n,k,belts))
			break;
		//������ �ƴϸ� ���ʷ� ����
		blets_rotate(n, belts);
		robot_move(n, belts);
		robot_input(n, belts);
		play_cnt++;
	}
	return play_cnt;
}

int main(void) {
	//�ʱ�ȭ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//�Է�
	int n, k;
	cin >> n >> k;
	//�����Ҵ�
	BLOCK* belts = new BLOCK[(2 * n) ];
	
	//������ �Է�
	for (int i = 0; i < 2 * n; i++) {
		int d;
		cin >> d;
		belts[i].d = d;
		belts[i].is_robot = false;
	}

	//�ùķ��̼� ����
	int ret = simulation(n, k, belts);
	//���� ���
	cout << ret << '\n';
	
	//�޸� ����
	delete[] belts;
	return 0;
}