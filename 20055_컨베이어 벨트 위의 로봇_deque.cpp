#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

//벨트의 각 블록 
struct BLOCK {
	int d;
	bool is_robot;
};

int n, k, result;

//작동 중지 체크
bool check_break(deque<BLOCK>& dq) {
	int cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (dq[i].d == 0)
			cnt++;
	}
	if (cnt >= k)
		return true;
	else
		return false;
}

//벨트의 회전
void rotate(deque<BLOCK>& dq) {
	//덱 특성 이용
	dq.push_front(dq.back());
	dq.pop_back();
	//내리는 위치에 로봇이 존재하면
	if (dq[n - 1].is_robot) {
		dq[n - 1].is_robot = false;
	}
	return;
}

//로봇의 움직임
void robot_move(deque<BLOCK>& dq) {
	//1~3 ===> 0 1 2 구간만 회전
	for (int i = n - 2; i >= 0; i--) {
		if (dq[i].is_robot) {
			if (!dq[i + 1].is_robot && dq[i + 1].d >= 1) {
				//로봇이 이동가능
				dq[i].is_robot = false;
				dq[i + 1].is_robot = true;
				dq[i + 1].d -= 1;
			}
		}
	}
	//다시 한번 내리는 위치에 로봇있나 확인
	if (dq[n - 1].is_robot) {
		dq[n - 1].is_robot = false;
	}
	return;
}

//로봇 넣기
void robot_input(deque<BLOCK>& dq) {
	//내구성 1 이상이고 로봇이 없으면
	if (dq[0].d >= 1 && !dq[0].is_robot) {
		dq[0].d -= 1;
		dq[0].is_robot = true;
	}
}

//시뮬레이션
void simulation(deque<BLOCK>& dq) {
	int play_cnt = 0;
	//시뮬시작
	while (true) {
		//작동해도되는 지 검사
		if (check_break(dq))
			break;
		//문제 조건 벨트와 로봇이 같이 회전
		rotate(dq);
		//로봇 이동
		robot_move(dq);
		//올리는 위치에 올리는지 마는지 확인
		robot_input(dq);
		play_cnt++;
	}
	result = play_cnt;
	return;
}

int main(void) {
	//입력
	scanf("%d %d", &n, &k);
	deque<BLOCK> dq;
	//내구성 입력
	for (int i = 0; i < 2 * n; i++) {
		int d;
		scanf("%d", &d);
		dq.push_back({ d,false });
	}
	//시뮬 시작
	simulation(dq);
	printf("%d", result);
	return 0;
}
