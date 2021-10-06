#include <iostream>
#include <vector>

using namespace std;

struct NODE {
	int y, x;
};

int n, m, result;
int board[50][50] = { 0, };

//대각선 포함 시계방향
const int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
const int dx[8] = { -1,-1,0,1,1,1,0,-1 };

//구름 벡터
vector<NODE> clouds;

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
void clouds_init(void) {
	clouds.push_back({ n - 1,0 });
	clouds.push_back({ n - 1,1 });
	clouds.push_back({ n - 2,0 });
	clouds.push_back({ n - 2,1 });
}

//구름의 이동
void clouds_move(vector<NODE>& v, int dir, int speed) {
	//순환 행렬이므로
	speed = speed % n;
	dir -= 1;
	//구름의 이동
	for (int i = 0; i < clouds.size(); ++i) {
		//순환행렬 공식이용
		clouds[i].y = (clouds[i].y + speed * dy[dir] + n) % n;
		clouds[i].x = (clouds[i].x + speed * dx[dir] + n) % n;
		board[clouds[i].y][clouds[i].x] += 1;
		//임시벡터에 삽입
		v.push_back({ clouds[i].y,clouds[i].x });
	}
	//구름 삭제
	clouds.clear();
	return;
}

//물 복사 버그 
void water_copy_bug(vector<NODE> &v) {
	//물복사 시전
	for (int i = 0; i < v.size(); ++i) {
		int water_cnt = 0;
		//대각선들만 탐색해야하므로 +2씩
		for (int dir = 1; dir < 8; dir += 2) {
			int ny = v[i].y + dy[dir];
			int nx = v[i].x + dx[dir];

			//범위 초과
			if (ny < 0 || nx < 0 || ny >= n || nx >= n)
				continue;
			//물이 있다면
			if (board[ny][nx] != 0)
				water_cnt++;
		}
		//물복사
		board[v[i].y][v[i].x] += water_cnt;
	}
}

//벡터안에 존재하는 판단
bool is_yx(vector<NODE>& v, int y, int x) {
	for (int i = 0; i < v.size(); i++) {
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
void get_tot_water() {
	int tot = 0;
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			//물이 있다면
			if (board[y][x] != 0)
				tot += board[y][x];
		}
	}
	result = tot;
	return;
}

//시뮬레이션
void simulation(void) {
	//입력
	input();
	//구름 초기화
	clouds_init();
	//시뮬
	while (m--) {
		vector<NODE> tmp;
		int dir, speed;
		cin >> dir >> speed;
		clouds_move(tmp, dir, speed);
		water_copy_bug(tmp);
		clouds_update(tmp);
	}
	//물의 양 합산
	get_tot_water();
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	result = 0;
	//시작
	simulation();
	cout << result << '\n';
	return 0;
}
