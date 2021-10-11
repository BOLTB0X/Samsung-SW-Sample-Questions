#include <iostream>
#include <queue>
#include <string>

using namespace std;

int k, score = 0;
//회전용 덱
deque<int> dq[5];

//입력
void input() {
	//4개의 톱니바퀴 정보 입력
	for (int i = 1; i <= 4; ++i) {
		string tmp;
		cin >> tmp;
		// N극은 0, S극은 1
		for (int j = 0; j < tmp.length(); ++j) {
			dq[i].push_back(tmp[j] - '0');
		}
	}
}

//톱니바퀴 회전
void gear_rotate(queue<pair<int, int>> q) {
	//제일 먼저 회전이 가능한기 확인
	while (!q.empty()) {
		//큐의 정보 
		int cur_idx = q.front().first;
		int turn_dir = q.front().second;
		q.pop();

		//만약 방향이 시계방향이면
		//가장 하단에 있는게 상단으로
		if (turn_dir == 1) {
			int tmp = dq[cur_idx].back();
			dq[cur_idx].pop_back();
			dq[cur_idx].push_front(tmp);
		}

		//만약 방향이 빈시계방향이면
		//가장 상단에 있는게 하단으로
		else if (turn_dir == -1) {
			int tmp = dq[cur_idx].front();
			dq[cur_idx].pop_front();
			dq[cur_idx].push_back(tmp);
		}
	}
	return;
}

//회전 가능한지 검사
void is_rotate(queue<pair<int,int>> q, int i, int d) {
	int idx = i;
	int tmp_dir = d;
	q.push({ idx,tmp_dir });

	//먼저 왼쪽에 있는 톱니바퀴 회전정보확인
	while (true) {
		if (idx == 4)
			break;
		idx++;
		tmp_dir *= -1;
		//2와 6부분을 비교 회전 가능하진 회전정보를 큐에 삽입
		if (dq[idx - 1][2] != dq[idx][6])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	idx = i;
	tmp_dir = d;

	//이번에 오른쪽에서 왼쪽으로
	while (true) {
		if (idx == 1)
			break;
		idx--;
		tmp_dir *= -1;
		//2와 6부분을 비교 회전 가능하진 회전정보를 큐에 삽입
		if (dq[idx + 1][6] != dq[idx][2])
			q.push({ idx,tmp_dir });
		else
			break;
	}
	gear_rotate(q);
	return;
}

//점수 득정
void get_score() {
	//점수 조건 2^n-1
	int cnt = 1;
	for (int i = 1; i < 5; i++) {
		if (dq[i][0] == 1)
			score += cnt;
		cnt *= 2;
	}
	return;
}

//시뮬레이션
void simulation(void) {
	input();
	cin >> k;
	//회전 정보용
	queue<pair<int, int>> q;
	while (k--) {
		//톱니바퀴 번호, 방향 1 시계 -1 반시계
		int gear_idx, gear_dir;
		cin >> gear_idx >> gear_dir;
		is_rotate(q,gear_idx, gear_dir);
		//큐 초기화
		while (!q.empty())
			q.pop();
	}
	get_score();
	cout << score << '\n';
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//시뮬시작
	simulation();
	return 0;
}
