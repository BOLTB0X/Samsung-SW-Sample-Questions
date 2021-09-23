#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

struct BLOCK {
	int d;
	bool is_robot;
};

deque<BLOCK> dq;

int n, k;

bool is_break_point(void) {
	int zero_cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (dq[i].d == 0)
			zero_cnt++;
	}
	if (zero_cnt >= k)
		return true;
	else
		return false;
}

void rotate(void) {
	dq.push_front(dq.back());
	dq.pop_back();

	if (dq[n-1].is_robot)
		dq[n - 1].is_robot = false;
}

void move(void) {
	for (int i = n - 2; i >= 0; i--) {
		if (dq[i].is_robot) {
			if (!dq[i + 1].is_robot && dq[i + 1].d >= 1) {
				dq[i].is_robot = false;
				dq[i + 1].is_robot = true;
				dq[i + 1].d -= 1;
			}
		}
	}
	if (dq[n - 1].is_robot)
		dq[n - 1].is_robot = false;
}

void input(void) {
	if (!dq[0].is_robot && dq[0].d >= 1) {
		dq[0].is_robot = true;
		dq[0].d -= 1;
	}
}

int simulation(void) {
	int play_step = 0;
	while (true) {
		if (is_break_point()) {
			break;
		}
		rotate();
		move();
		input();
		play_step++;
	}
	return play_step;
}

int main(void) {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < 2 * n; i++) {
		int d;
		scanf("%d", &d);
		dq.push_back({ d,false });
	}
	int ret = simulation();
	printf("%d\n", ret);
	return 0;
}

