#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <vector> 

using namespace std; 

//파이어볼 자료형 정의
typedef struct {
	int y, x;
	int mess, s, d;
} INF;

int n, m, k;
//맵을 벡터로 한 셀에 여러 원소가 올수 있음
vector<INF> map[51][51];
vector<INF> fireball;

//이동방향 
const int dy[8] = { -1,-1,0,1,1,1,0,-1 };
const int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

//파이어볼 정보에 따라 이동
void fireball_move(void) {
	//기존 맵 초기화
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j].clear();
		}
	}
	//파이어볼 이동
	for (int i = 0; i < fireball.size(); i++) {
		INF cur_fireball = fireball[i];
		int cur_y = cur_fireball.y;
		int cur_x = cur_fireball.x;
		int ny = cur_y + dy[cur_fireball.d] * cur_fireball.s;
		int nx = cur_x + dx[cur_fireball.d] * cur_fireball.s;
		//
		while (ny < 1)
			ny += n;
		while (nx < 1)
			nx += n;
		while (ny > n)
			ny -= n;
		while (nx > n)
			nx -= n;
		map[ny][nx].push_back({ ny,nx,cur_fireball.mess,cur_fireball.s,cur_fireball.d });
	}
	return;
}

// 방향이 모두 홀수인지, 모두 짝수인지 판별
bool is_direction(int y, int x) {
	bool even_flag = false, odd_flag = false;
	for (int i = 0; i < map[y][x].size(); i++) {
		if (map[y][x][i].d % 2 == 0)
			even_flag = true;
		else
			odd_flag = true;
	}
	//검사
	if (even_flag && !odd_flag) 
		return true;
	else if (!even_flag && odd_flag) 
		return true;
	else 
		return false;
}

//fire볼 업데이트
void fireball_update(void) {
	vector<INF> tmp;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int mass_tot = 0, speed_tot = 0;
			//비어있다면
			if (map[i][j].size() == 0)
				continue;
			//1개면 삽입
			if (map[i][j].size() == 1)
				tmp.push_back(map[i][j][0]);
			//2개 이상이면
			else {
				for (int k = 0; k < map[i][j].size(); k++) {
					mass_tot += map[i][j][k].mess;
					speed_tot += map[i][j][k].s;
				}
				int avg_mas = mass_tot / 5;
				int avg_speed = speed_tot / map[i][j].size();
				if (avg_mas == 0)
					continue;
				// all 홀 인지 all 짝인 검사
				if (is_direction(i, j)) {
					tmp.push_back({ i,j,avg_mas,avg_speed,0 });
					tmp.push_back({ i,j,avg_mas,avg_speed,2 });
					tmp.push_back({ i,j,avg_mas,avg_speed,4 });
					tmp.push_back({ i,j,avg_mas,avg_speed,6 });
				}
				else {
					tmp.push_back({ i,j,avg_mas,avg_speed,1 });
					tmp.push_back({ i,j,avg_mas,avg_speed,3 });
					tmp.push_back({ i,j,avg_mas,avg_speed,5 });
					tmp.push_back({ i,j,avg_mas,avg_speed,7 });
				}
			}
		}
	}
	//벡터교체
	fireball = tmp;
}

//시뮬레이션 실행
int simulation(void) {
	//시뮬시작
	for (int i = 0; i < k; i++) {
		fireball_move();
		fireball_update();
	}
	//질량출력
	int tot = 0;
	for (int i = 0; i < fireball.size(); i++) {
		tot += fireball[i].mess;
	}
	return tot;
}

int main(void) {
	//입력
	scanf("%d %d %d", &n, &m, &k);
	//파이어볼 정보 입력
	for (int i = 1; i <= m; i++) {
		int y, x, mess, d, s;
		scanf("%d %d %d %d %d", &y, &x, &mess, &s, &d);
		fireball.push_back({ y,x,mess,s,d });
	}
	int ret = simulation();
	printf("%d", ret);
	return 0;
}
