#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int T;
deque<int> dq[5]; //실제 톱니바퀴 회전용
queue<pair<int, int>> q; //회전 정보를 위한 큐

void gear_rotate() {
	//회전 정보를 담는 큐가 비어질때까지 팝
	while (!q.empty()) {
		int cur_num = q.front().first; //현재 회전할 톱니바퀴
		int rotate = q.front().second; //시계방향인지 반시계방향인지
		q.pop();
		//시계방향인 경우
		if (rotate == 1) {
			//가장 하단에 있던 게 최상단으로 이동 
			int tmp = dq[cur_num].back();
			dq[cur_num].pop_back();
			dq[cur_num].push_front(tmp);
		}
		//반시계방향인 경우
		else {
			//가장 상단에 있던게 최하단으로 이동
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
	//큐 삽입
	q.push({ idx,tmp_dir });

	//이전확인
	while (true) {
		if (idx == 4) 
			break;
		idx++;
		tmp_dir *= -1;
		// 회전을 할경우 관련 정보를 큐에 삽입
		if (dq[idx - 1][2] != dq[idx][6])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	idx = gear_num;
	tmp_dir = gear_dir;
	//옆 확인
	while (true) {
		if (idx == 1) 
			break;

		idx--;
		tmp_dir *= -1;
		//회전할 경우 큐의 정보를 삽입
		if (dq[idx + 1][6] != dq[idx][2]) //회전 조건
			q.push({ idx,tmp_dir }); 
		else
			break;
	}
	//진짜 톱니바퀴 회전시작
	gear_rotate();
	return;
}

int get_score() {
	int score = 0;
	int check = 1;
	//톱니바퀴 번호가 올라갈수록 ==> 2^n-1
	for (int i = 1; i < 5; i++) {
		if (dq[i][0] == 1) 
			score += check;
		check *= 2;
	}
	return score;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//톱니바퀴 입력
	for (int i = 1; i < 5; i++) {
		string tmp_gear;
		cin >> tmp_gear;
		//톱니바퀴의 정보 디큐에 삽입
		//톱니바퀴 가지는 01234567, N = 0, S = 1
		for (int j = 0; j < tmp_gear.length(); j++) 
			dq[i].push_back(tmp_gear[j] - '0');
	}
	//테스트 시작
	cin >> T;
	while (T--) {
		int gear_num, gear_dir;
		cin >> gear_num >> gear_dir;
		//진짜 돌리기전 조건에 맞는 지 체크
		gear_rotate_check(gear_num, gear_dir);
		//q 초기화
		while (!q.empty()) 
			q.pop();
	}
	//점수확인
	int ret = get_score();
	cout << ret << '\n';
	return 0;
}