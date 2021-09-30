#include <iostream>
#include <deque>

using namespace std;

//벨트의 한 블록
struct BLOCK {
	int d;
	bool is_robot;
};

int n, k;
deque<BLOCK> blets;

//중지는 시키는 지 판단 함수
bool is_break(void) {
	int zero_cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (blets[i].d == 0)
			zero_cnt++;
	}
	//중지 조건이면
	if (zero_cnt >= k)
		return true;
	return false;
}

//벨트 회전 
void blets_rotate(void) {
	//한칸 씩 뒤로 밀수있음
	blets.push_front(blets.back());
	blets.pop_back();

	//조건없이 내리는 위치
	if (blets[n - 1].is_robot)
		blets[n - 1].is_robot = false;
	return;
}

// 0 1 2 이 칸들은 로봇들이 직접 이동
void robot_move(void) {
	for (int i = n - 2; i >= 0; i--) {
		//로봇이 있지만
		if (blets[i].is_robot) {
			//다음칸에 로봇이 없고 내구성이 1이상이면
			if (!blets[i + 1].is_robot && blets[i + 1].d >= 1) {
				blets[i].is_robot = false;
				blets[i + 1].is_robot = true;
				blets[i + 1].d -= 1;
			}
		}
	}
	//조건없이 내리는 위치
	if (blets[n - 1].is_robot)
		blets[n - 1].is_robot = false;
	return;
}

//0은 로봇을 올리는 위치
void robot_input(void) {
	//로봇이 없고 내구성이 1이상면
	if (blets[0].d >= 1 && !blets[0].is_robot) {
		blets[0].d -= 1;
		blets[0].is_robot = true;
	}
	return;
}

//시뮬
int simulation(void) {
	int play_cnt = 0;
	while (true) {
		if (is_break())
			break;
		blets_rotate();
		robot_move();
		robot_input();
		play_cnt++;
	}
	return play_cnt;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		int d;
		cin >> d;
		blets.push_back({ d,false });
	}
	int ret = simulation();
	cout << ret << '\n';
	return 0;
}
