#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int s, d, z; //속력, 이동방향, 크기
}shark;

typedef struct {
	int r, c, s, d, z;
	//row,col,speed,dir,size;
}shark_inf;

int r, c, k;
vector<shark> map[101][101];
//상어 움직임을 저장하는 벡터
vector<shark_inf> moving_shark;
//잡은 상어를 저장하는 벡터
vector<shark> caught;
//위 아래 우 좌
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,1,-1 };

bool is_range(int nr, int nc) {
	if (nr < 0 || nc < 0 || nr >= r || nc >= c)
		return false;
	return true;
}

int turn_dir(int d) {
	if (d == 0) return 1;
	else if (d == 1) return 0;
	else if (d == 2) return 3;
	else if (d == 3) return 2;
}

void catch_shark(int king_cur) {
	shark tmp_shark;
	//낚시왕이 있는 열에 행들을 일일히 확인
	for (int i = 0; i < r; i++) {
		if (!map[i][king_cur].empty()) {
			tmp_shark = map[i][king_cur][0];
			map[i][king_cur].clear(); //잡았으니 비우기
			caught.push_back(tmp_shark);
			break;
		}
	}
}

//한 상어의 움직임 재귀이용
shark_inf moving_single_shark(int row, int col, shark cur_shark) {
	shark_inf tmp_inf;

	int nr = row;
	int nc = col;
	int cnt;

	if (cur_shark.d == 0 || cur_shark.d == 1)
		cnt = cur_shark.s % ((r - 1) * 2);
	else
		cnt = cur_shark.s % ((c - 1) * 2);

	for (int i = 0; i < cnt; i++) {
		nr += dr[cur_shark.d];
		nc += dc[cur_shark.d];

		if (!is_range(nr, nc)) {
			cur_shark.d = turn_dir(cur_shark.d);
			nr = nr + dr[cur_shark.d] * 2;
			nc = nc + dc[cur_shark.d] * 2;
		}
	}
	tmp_inf = { nr,nc,cur_shark.s,cur_shark.d,cur_shark.z };
	return tmp_inf;
}

//큰놈이 먼저
shark shark_crash(vector<shark> crash) {
	int max_z = 0;
	shark tmp_shark = crash[0];

	for (int i = 0; i < crash.size(); i++) {
		if (max_z < crash[i].z) {
			tmp_shark = crash[i];
			max_z = crash[i].z;
		}
	}
	return tmp_shark;
}

void move_shark(void) {
	//호출할때 상어의 이동이 변했으므로 초기화
	moving_shark.clear();

	shark_inf tmp_inf;
	shark tmp_shark;

	//움직이는 상어들을 moving_shark 벡터에 삽입
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			//상어들이 해당위치 맵에 있으면
			if (!map[i][j].empty()) {
				tmp_inf = moving_single_shark(i, j, map[i][j][0]);
				map[i][j].pop_back();
				moving_shark.push_back(tmp_inf);
			}
		}
	}
	//moving_shark벡터에 업데이트정보를 저장했으니 맵에 적용
	for (int i = 0; i < moving_shark.size(); i++) {
		tmp_inf = moving_shark[i];
		tmp_shark = { tmp_inf.s,tmp_inf.d,tmp_inf.z };
		map[tmp_inf.r][tmp_inf.c].push_back(tmp_shark);
	}

	//만약에 한 셀에 두마리 이상일 경우
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j].size() > 1) {
				tmp_shark = shark_crash(map[i][j]);
				map[i][j].clear();
				map[i][j].push_back(tmp_shark);
			}
		}
	}
	return;
}

void simulation(void) {
	//낚시왕은 항상 오른쪽으로 이동함
	for (int king = 0; king < c; king++) {
		// 한칸 씩 이동하며 
		catch_shark(king); //잡을 수있는 지
		move_shark(); //상어들의 움직임
	}
	return;

}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> r >> c >> k;
	shark tmp_shark;

	int tmp_r, tmp_c, tmp_s, tmp_d, tmp_z;
	int answer = 0;
	//맵생성 및 상어 정보입력
	for (int i = 0; i < k; i++) {
		cin >> tmp_r >> tmp_c >> tmp_s >> tmp_d >> tmp_z;
		tmp_shark = { tmp_s,tmp_d - 1,tmp_z };
		map[tmp_r - 1][tmp_c - 1].push_back(tmp_shark);
	}
	//시뮬레이션 지작
	simulation();
	// 잡은 상어 크기의 합을 출력
	for (int i = 0; i < caught.size(); i++) {
		answer += caught[i].z;
	}
	cout << answer << '\n';
	return 0;
}
