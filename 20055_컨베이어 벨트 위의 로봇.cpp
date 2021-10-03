#include <iostream>

using namespace std;

//벨트의 한 블록
struct BLOCK {
	int d;
	bool is_robot;
};

//동작을 중지시키는지 판단
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

//벨트만 회전함수
void blets_rotate(int n, BLOCK* belts) {
	//최하단 따로 저장
	BLOCK tmp = belts[2 * n-1];
	for (int i = (2 * n) -2; i >= 0; i--) {
		belts[i + 1] = belts[i];
	}
	//상단으로 이동
	belts[0] = tmp;

	if (belts[n-1].is_robot)
		belts[n-1].is_robot = false;
	return;
}

//로봇 이동 함수
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

//로봇 올리기 함수
void robot_input(int n, BLOCK* belts) {
	//올리는 위치에 확인
	if (!belts[0].is_robot && belts[0].d >= 1) {
		belts[0].is_robot = true;
		belts[0].d --;
	}
}

//시뮬레이션
int simulation(int n, int k, BLOCK* belts) {
	//플레이카운트 초기화
	int play_cnt = 0;
	while (true) {
		//시작 후 바로 동작하는 지 검사
		if (is_break(n,k,belts))
			break;
		//중지가 아니면 차례로 수행
		blets_rotate(n, belts);
		robot_move(n, belts);
		robot_input(n, belts);
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
	int n, k;
	cin >> n >> k;
	//동적할당
	BLOCK* belts = new BLOCK[(2 * n) ];
	
	//내구성 입력
	for (int i = 0; i < 2 * n; i++) {
		int d;
		cin >> d;
		belts[i].d = d;
		belts[i].is_robot = false;
	}

	//시뮬레이션 시작
	int ret = simulation(n, k, belts);
	//정답 출력
	cout << ret << '\n';
	
	//메모리 해제
	delete[] belts;
	return 0;
}
