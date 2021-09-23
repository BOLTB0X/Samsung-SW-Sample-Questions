#include <cstdio>

struct BLOCK {
	int d;
	bool is_robot;
};

int n, k;
BLOCK belts[202];

void map_init(void) {
	for (int i = 1; i <= 2 * n; i++) {
		belts[i].d = 0;
		belts[i].is_robot = false;
	}
}

bool check_break(void) {
	int cnt = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (belts[i].d == 0)
			cnt++;
	}
	if (cnt >= k)
		return true;
	return false;
}

void rotate_belts(void) {
	BLOCK tmp = belts[2 * n];
	for (int i = 2 * n - 1; i >= 0; i--) {
		belts[i + 1] = belts[i];
	}
	belts[1] = tmp;
	if (belts[n].is_robot)
		belts[n].is_robot = false;
}

void move_robot(void) {
	for (int i = n - 1; i >= 0; i--) {
		if (belts[i].is_robot) {
			if (!belts[i + 1].is_robot &&
				belts[i + 1].d >= 1) {
				belts[i + 1].is_robot = true;
				belts[i + 1].d--;
				belts[i].is_robot = false;
			}
		}
	}
	if (belts[n].is_robot)
		belts[n].is_robot = false;
	if (!belts[1].is_robot && belts[1].d >= 1) {
		belts[1].is_robot = true;
		belts[1].d--;
	}
}

int simulation(void) {
	int play_cnt = 0;
	while (true) {
		//종료 체크
		if (check_break())
			break;
		rotate_belts();
		move_robot();
		play_cnt++;
	}
	return play_cnt++;
}

int main(void) {
	scanf("%d %d", &n, &k);
	map_init();
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