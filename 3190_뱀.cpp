#include <iostream>
#include <queue>
using namespace std;

int n, k, l;
int map[101][101];
deque<pair<int, int>> snake;
deque<pair<int, char>> dir_cmd;

//위 아래 좌 우
const int dr[4] = { 1,-1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int answer;

//범위 초과
bool is_range(int row, int col) {
	if (row <1 || col <1 || row >n || col >n)
		return false;
	else
		return true;
}

//방향전
int turn_dir(int cur_dir, char new_dir) {
	//위인 경우
	if (cur_dir == 0) {
		if (new_dir == 'L')
			return 2;
		else
			return 3;
	}//아래인 경우
	else if (cur_dir == 1) {
		if (new_dir == 'L')
			return 3;
		else
			return 2;
	}//좌인 경우
	else if (cur_dir == 2) {
		if (new_dir == 'L')
			return 1;
		else
			return 0;
	}//우인 경우
	else if (cur_dir == 3) {
		if (new_dir == 'L')
			return 0;
		else
			return 1;
	}
}

//시뮬
void simulation(int sec, int dir) {
	//뱀 이동 시작
	int nr = snake.front().first + dr[dir];
	int nc = snake.front().second + dc[dir];
	//뱀의 위치가 범위를 벗어나면
	if (!is_range(nr, nc)) {
		answer = sec;
		return;
	}
	//만약 몸이 부H인 경우
	//즉 덱의 원소와 겹치는 경우
	for (int i = 0; i < snake.size(); i++) {
		if ((nr == snake[i].first) && (nc == snake[i].second)) {
			answer = sec;
			return;
		}
	}
	//사과를 발견한 경우
	if (map[nr][nc] == 1) {
		map[nr][nc] = 0; //사과 삭제
		//덱의 앞에 삽입하여 뱀의 전체 위치 이동
		snake.push_front({ nr,nc });
	}
	//사과가 없으니 꼬리가 이동해야함
	else {
		snake.pop_back();
		snake.push_front({ nr,nc });
	}
	//만약 명령어가 없을 경우를 대비
	int change_dir = dir;
	//명령어가 존재하고 해당 초가 된다면
	if (!dir_cmd.empty() && dir_cmd.front().first == sec) {
		change_dir = turn_dir(dir, dir_cmd.front().second);
		dir_cmd.pop_front();
	}
	//시간 증가와 새로운 방향으로 재귀호출
	simulation(sec + 1, change_dir);
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//맵의 가로,세로 길이
	cin >> n;
	//사과 갯수
	cin >> k;
	
	//사과 위치
	for (int i = 0; i < k; i++) {
		int apple_r, apple_c;
		cin >> apple_r >> apple_c;
		map[apple_r][apple_c] = 1;
	}
	
	//명령어 입력
	cin >> l;
	for (int i = 0; i < l; i++) {
		int x;
		char ch;
		cin >> x >> ch;
		dir_cmd.push_back({ x,ch });
	}
	
	//뱀의 초기위치
	snake.push_back({ 1,1 });
	
	//뱀의 초기방향은 오른쪽
	simulation(1, 3); //카운트, 방향
	
	cout << answer << '\n';
	return 0;
}
