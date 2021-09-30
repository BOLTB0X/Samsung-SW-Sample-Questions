#include <cstdio>

//벨트의 한 블록
struct BLOCK {
	int d;
	bool is_robot;
};

int n, k;
BLOCK belts[202];

//맵 초기화 함수
void map_init(void) {
	for (int i = 1; i <= 2 * n; i++) {
		belts[i].d = 0;
		belts[i].is_robot = false;
	}
}

//작동을 중짛시키는 지 판단하는 함수
bool check_break(void) {
	int cnt = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (belts[i].d == 0)
			cnt++;
	}
	//문제 조건이면
	if (cnt >= k)
		return true; //중지
	return false;
}

//벨트 회전
void rotate_belts(void) {
	//마지막칸 임시로 저장
	BLOCK tmp = belts[2 * n];
	//한칸 씩 뒤로 민다.
	for (int i = 2 * n - 1; i >= 0; i--) {
		belts[i + 1] = belts[i];
	}
	belts[1] = tmp;
	//문제 조건상 무조건 내리는 위치
	if (belts[n].is_robot)
		belts[n].is_robot = false;
}

//로봇을 이동
void move_robot(void) {
	//1,2,3 은 로봇이 직접 움직일 수 있음
	for (int i = n - 1; i >= 0; i--) {
		//로봇이 있구
		if (belts[i].is_robot) {
			//그 다음칸에 로봇이 없다면
			if (!belts[i + 1].is_robot &&
				belts[i + 1].d >= 1) {
				belts[i + 1].is_robot = true;
				belts[i + 1].d--;
				belts[i].is_robot = false;
			}
		}
	}
	//무조건 내리는 위치
	if (belts[n].is_robot)
		belts[n].is_robot = false;
	
	//조건에 맞으면 로봇을 올리는 위치 
	if (!belts[1].is_robot && belts[1].d >= 1) {
		belts[1].is_robot = true;
		belts[1].d--;
	}
}

//시뮬
int simulation(void) {
	int play_cnt = 0;
	while (true) {
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
