#include <cstdio>

struct BLOCK {
	int d;
	bool is_robot;
};

int n, k;
BLOCK belts[201];

//�� �ʱ�ȭ
void map_init(void) {	
	for (int i = 1; i <= 2 * n; i++) {
		belts[i].d = 0;
		belts[i].is_robot = false;
	}
	return;
}

//Ż������ Ȯ��
bool check_break() {
	int cnt = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (belts[i].d == 0)
			cnt++;
	}
	if (cnt >= k)
		return true;
	else
		return false;
}

//��Ʈ�� ȸ��
void rotate_belt(void) {
	//�ǳ� �ӽ�����
	BLOCK tmp = belts[2 * n];
	for (int i = 2 * n - 1; i >= 1; i--) {
		belts[i + 1] = belts[i];
	}
	belts[1] = tmp;
	if (belts[n].is_robot)
		belts[n].is_robot = false;
	return;
}

//�κ��� �̵�
void move_robot(void) {
	//1~3 �κ��̵�
	for (int i = n - 1; i >= 1; i--) {
		if (belts[i].is_robot) {
			if (!belts[i + 1].is_robot && belts[i + 1].d >= 1) {
				belts[i + 1].is_robot = true;
				belts[i + 1].d--;
				belts[i].is_robot = false;
			}
		}
	}
	//������ ĭ Ȯ��
	if (belts[n].is_robot) {
		belts[n].is_robot = false;
	}
	//�ö󰡴� ��ġ�� �κ��� ���ٸ� �κ� �ø���
	if (!belts[1].is_robot && belts[1].d >= 1) {
		belts[1].is_robot = true;
		belts[1].d--;
		belts[2*n].is_robot = false;
	}
	return;
}

//�ùķ��̼�
int simulation(void) {
	int turn_cnt = 0;
	while (true) {
		//������������ Ȯ��
		if (check_break()) 
			break;
		rotate_belt();
		move_robot();
		turn_cnt++;
	}
	return turn_cnt;
}

int main(void) {
	scanf("%d %d", &n, &k);
	map_init();
	//������ �Է�
	for (int i = 1; i <= 2 * n; i++) {
		int d;
		scanf("%d", &d);
		belts[i].d = d;
		belts[i].is_robot = false;
	}
	int ret = simulation();
	printf("%d", ret);
	return 0;
}