#include <iostream>
#include <vector>

using namespace std;

//노드
struct NODE {
	int y, x;
};

//맵
int n, m;
int board[50][50] = { 0, };
//구름 벡터
vector<NODE> clouds;

//시계방향 대각선 포함
const int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };
const int dx[9] = { 0, -1,-1,0,1,1,1,0,-1 };

//입력
void input(void) {
	cin >> n >> m;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			cin >> board[y][x];
		}
	}
	return;
}

//구름 초기화
void clouds_init() {
	clouds.push_back({ n - 1,0 });
	clouds.push_back({ n - 1,1 });
	clouds.push_back({ n - 2,0 });
	clouds.push_back({ n - 2,1 });
	return;
}

//구름이 이동
void clouds_move(vector<NODE> &v, int d, int s) {
	//속력 맵의 크기만큼 조정
	s %= n;
	for (int i = 0; i < clouds.size(); ++i) {
		//구름이동 
		clouds[i].y = (clouds[i].y + s * dy[d] + n) % n;
		clouds[i].x = (clouds[i].x + s * dx[d] + n) % n;
		board[clouds[i].y][clouds[i].x]++;
		//임시벡터
		v.push_back({ clouds[i].y,clouds[i].x });
	}
	//구름 초기화
	clouds.clear();
	return;
}

//물복사 버그 
void water_bug(vector<NODE>& v) {
	//물복사 시전
	for (int i = 0; i < v.size(); ++i) {
		int water_cnt = 0;
		for (int dir = 2; dir < 9; dir += 2) {
			int ny = v[i].y + dy[dir];
			int nx = v[i].x + dx[dir];

			//범위 초과
			if (ny >= n || nx >= n || ny < 0 || nx < 0)
				continue;
			
			//물이 있다면
			if (board[ny][nx] != 0)
				water_cnt++;
		}
		//물의 양 증가
		board[v[i].y][v[i].x] += water_cnt;
	}
	return;
}

//벡터안에 존재하는 판단
bool is_yx(vector<NODE>& v, int y, int x) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].y == y && v[i].x == x)
			return false;
	}
	return true;
}

//구름 업데이트
void clouds_update(vector<NODE>& v) {
	//맵 완전탐색
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			//물의 양이 2이상
			//이때 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 함
			if (board[y][x] >= 2 && is_yx(v, y, x)) {
				clouds.push_back({ y,x });
				board[y][x] -= 2;
			}
		}
	}
	v.clear();
	return;
}

//물의 총 합
int get_tot_water(void) {
	int tot = 0;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			//물이 있다면
			if (board[y][x] != 0) {
				tot += board[y][x];
			}
		}
	}
	return tot;
}

//시뮬레이션
int simulation(void) {
	//맵 정보 입력
	input();
	//구름의 초기화
	clouds_init();
	//마법사 상어의 시뮬레이션
	while (m--) {
		int d, s;
		vector<NODE> tmp;
		cin >> d >> s;
		//구름의 이동
		clouds_move(tmp,d, s);
		//물복사
		water_bug(tmp);
		//구름 변경
		clouds_update(tmp);
	}
	//시뮬레이션 후 남은 물의 양
	int result = get_tot_water();
	return result;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//시뮬레이션의 반환
	int ret = simulation();
	cout << ret << '\n';
	return 0;
}
