#include <cstdio>

struct BLOCK {
	int d;
	bool is_robot;
};

int n, k;
BLOCK belts[201];

//맵 초기화
void map_init(void) {	
	for (int i = 1; i <= 2 * n; i++) {
		belts[i].d = 0;
		belts[i].is_robot = false;
	}
	return;
}

//탈출조건 확인
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

//벨트의 회전
void rotate_belt(void) {
	//맨끝 임시저장
	BLOCK tmp = belts[2 * n];
	for (int i = 2 * n - 1; i >= 1; i--) {
		belts[i + 1] = belts[i];
	}
	belts[1] = tmp;
	if (belts[n].is_robot)
		belts[n].is_robot = false;
	return;
}

//로봇의 이동
void move_robot(void) {
	//1~3 로봇이동
	for (int i = n - 1; i >= 1; i--) {
		if (belts[i].is_robot) {
			if (!belts[i + 1].is_robot && belts[i + 1].d >= 1) {
				belts[i + 1].is_robot = true;
				belts[i + 1].d--;
				belts[i].is_robot = false;
			}
		}
	}
	//마지막 칸 확인
	if (belts[n].is_robot) {
		belts[n].is_robot = false;
	}
	//올라가는 위치에 로봇이 없다면 로봇 올리기
	if (!belts[1].is_robot && belts[1].d >= 1) {
		belts[1].is_robot = true;
		belts[1].d--;
		belts[2*n].is_robot = false;
	}
	return;
}

//시뮬레이션
int simulation(void) {
	int turn_cnt = 0;
	while (true) {
		//종료조건인지 확인
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
	//내구성 입력
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