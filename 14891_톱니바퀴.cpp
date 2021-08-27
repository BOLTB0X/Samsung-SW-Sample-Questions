#include <iostream>
#include <string>
#include <queue>
using namespace std;

deque<int> dq[5]; //실제 톱니바퀴 회전용
int score = 0;

//점수확인 
void get_score() {
	int check = 1;
	//점수방식은 2^n-1
	for (int i = 1; i < 5; i++) {
		if (dq[i][0] == 1)
			score += check;
		check *= 2;
	}
	return;
}

void gear_rotate(queue<pair<int,int>> q) {
	//회전정보를 담은 큐가 비어질때 까지
	while (!q.empty()) {
		int cur_idx = q.front().first;
		int rotate = q.front().second;
		q.pop();
		//시계방향인 경우
		if (rotate == 1) {
			//가장 하단에 있던게 최상단으로 이동
			int tmp = dq[cur_idx].back();
			dq[cur_idx].pop_back();
			dq[cur_idx].push_front(tmp);
		}
		//반시계방향인 경우
		else {
			//가장 상단에 있던게 최하단으로 이동
			int tmp = dq[cur_idx].front();
			dq[cur_idx].pop_front();
			dq[cur_idx].push_back(tmp);
		}
	}
	return;
}

void gear_rotate_check(queue<pair<int,int>> q,int gear_idx, int gear_dir) {
	int idx = gear_idx;
	int tmp_dir = gear_dir;
	//큐 삽입
	q.push({ idx,tmp_dir });

	//현재 톱니바퀴의 옆 확인
	while (true) {
		if (idx == 4)
			break;
		idx++;
		tmp_dir *= -1;
		//회전정보를 큐에 삽입
		//3시방향과 9시 방향이 다르면
		if (dq[idx - 1][2] != dq[idx][6])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	idx = gear_idx;
	tmp_dir = gear_dir;
	//이전 확인
	while (true) {
		if (idx == 1)
			break;
		idx--;
		tmp_dir *= -1;
		// 회전할 경우 큐의 정보를 삽입
		// 9시방향과 3시방향
		if (dq[idx + 1][6] != dq[idx][2])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	gear_rotate(q);
	return;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	queue<pair<int, int>> q; //회전 정보를 탐는 큐
	
	string tmp_gear;
	for (int i = 1; i < 5; i++) {
		cin >> tmp_gear;
		//톱니바퀴의 N,S극의 정보를 덱에 삽입
		for (int j = 0; j < tmp_gear.length(); j++) {
			dq[i].push_back(tmp_gear[j] - '0');
		}
	}
	int T;
	cin >> T;
	while (T>0) {
		int gear_idx, gear_dir;
		cin >> gear_idx >> gear_dir;
		//진짜 회전시키기전에 체크
		gear_rotate_check(q,gear_idx, gear_dir);
		//큐 초기화
		while (!q.empty())
			q.pop();
		T--;
	}
	//점수확인
	get_score();
	cout << score << '\n';
	return 0;
}
