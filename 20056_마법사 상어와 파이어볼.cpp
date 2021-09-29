#include <iostream>
#include <vector>

using namespace std;

//파이어볼의 정보를 담는 구조체
struct FIREBALL {
	int y, x, mess, speed, dir;
};

int n, m, k, result;
vector<FIREBALL> board[51][51];
vector<FIREBALL> fireball;

const int dy[8] = { -1,-1,0,1,1,1,0,-1 };
const int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

//맵 초기화
void board_init(void) {
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			board[y][x].clear();
		}
	}
}

//파이어볼 이동
void fireball_move(void) {
	board_init();
	for (int i = 0; i < fireball.size(); i++) {
		FIREBALL cur_fireball = fireball[i];
		int cy = cur_fireball.y;
		int cx = cur_fireball.x;

		//파이어볼 이동
		int ny = cy + dy[cur_fireball.dir] * cur_fireball.speed;
		int nx = cx + dx[cur_fireball.dir] * cur_fireball.speed;
		//범위 검사
		//너무 깊게 들어갔을 때
		while (ny < 1)
			ny += n;
		while (nx < 1)
			nx += n;
		while (nx > n)
			nx -= n;
		while (ny > n)
			ny -= n;
		//파이어볼이 이동했으니 맵에 표시해줌
		board[ny][nx].push_back({ ny,nx,cur_fireball.mess,cur_fireball.speed,cur_fireball.dir });
	}
	return;
}

//한 맵의 셀에 파이어볼의 방향 확인
bool is_odd_even(int y, int x) {
	bool odd_flag = false;
	bool even_flag = false;

	for (int i = 0; i < board[y][x].size(); i++) {
		if (board[y][x][i].dir % 2 == 0)
			even_flag = true;
		else
			odd_flag = true;
	}
	//올 홀 또는 올 짝이면 한쪽은 불 이어야함
	if (even_flag && !odd_flag)
		return true;
	else if (!even_flag && odd_flag)
		return true;
	else
		return false;
}

//파이어볼 업데이트
void fireball_update(void) {
	//임시 파이어볼 벡터
	vector<FIREBALL> tmp_fireball;
	//파이어볼이 2개인지 확인
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			//비어있다면
			if (board[y][x].size() == 0)
				continue;
			//1개 있을 경우
			else if (board[y][x].size() == 1) {
				tmp_fireball.push_back(board[y][x][0]);
			}
			//2개 이상
			//파이어볼을 합쳐야함
			else {
				int tot_mess = 0, tot_speed = 0;
				for (int i = 0; i < board[y][x].size(); i++) {
					tot_mess += board[y][x][i].mess;
					tot_speed += board[y][x][i].speed;
				}
				int avg_mess = tot_mess / 5;
				if (avg_mess == 0) {
					continue;
				}
				int avg_speed = tot_speed / board[y][x].size();

				//합쳐지는 파이어볼 방향 홀짝인지 검사
				//전부 홀이거나 짝인 경우
				if (is_odd_even(y, x)) {
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,0 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,2 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,4 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,6 });
				}
				//그 
				else {
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,1 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,3 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,5 });
					tmp_fireball.push_back({ y,x,avg_mess,avg_speed,7 });
				}
			}
		}
	}
	//수정한 벡터 기존벡터로 교체
	fireball = tmp_fireball;
}

//시뮬레이션
void simulation(void) {
	//k번 반복
	while (k--) {
		fireball_move();
		fireball_update();
	}
	//정답 도출
	for (int i = 0; i < fireball.size(); i++) {
		result += fireball[i].mess;
	}
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		fireball.push_back({ a,b,c,d,e });
	}
	//시뮬 시작
	result = 0;
	simulation();
	cout << result << '\n';
	return 0;
}
