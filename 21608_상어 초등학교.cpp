#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//학생 정보들 담는 구조체
struct STUDENT {
	int student_idx;
	int y;
	int x;
	int love[4];
};

//우선 순위큐 조건 변경 및 자료형을 담는 구조체
struct INFO {
	int y, x;
	int blacnk_cnt;
	int love_cnt;
	
	//문제조건
	bool operator < (const INFO &i) const {
		//1
		if (love_cnt == i.love_cnt) {
			//2
			if (blacnk_cnt == i.blacnk_cnt) {
				//3
				if (y == i.y)
					return x > i.x;
				//4
				return y > i.y;
			}
			return blacnk_cnt < i.blacnk_cnt;
		}
		return love_cnt < i.love_cnt;
	}
};

int n, result;
int board[20][20];

//상하좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };
//만족도
const int satisfy[5] = { 0,1,10,100,1000 };

//자리 배치 --> 우선순위 큐
void setting_sit(vector<STUDENT>& student) {
	//벡터 부터 순회
	for (int i = 1; i <= n * n; i++) {
		priority_queue<INFO> pq;
		//맵 순회
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				//빈 공간 발견
				if (board[y][x] == 0) {
					int blank = 0, love = 0;
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];

						if (ny >= n || nx >= n || ny < 0 || nx < 0)
							continue;
						//빈공간인 경우
						if (board[ny][nx] == 0)
							blank++;
						else {
							//해당학생의 선호학생인지 검사
							for (int s = 0; s < 4; s++) {
								if (board[ny][nx] == student[i].love[s]) {
									love++;
									break;
								}
							}
						}
						//우선순위 큐에 삽입
					}
					pq.push({ y, x, blank, love });
				}
			}
		}
		//우선순위 큐가 비어있지 않다면
		//자리 배치
		if (!pq.empty()) {
			INFO cur = pq.top();
			int y = cur.y;
			int x = cur.x;
			board[y][x] = student[i].student_idx;
			//만족도 계산을 위한 위치정보 삽입
			student[i].y = y;
			student[i].x = x;
		}
	}
	return;
}

//만족도 점수 계산
void get_satisfy_score(vector<STUDENT>& student) {
	//학생벡터 순회
	for (int i = 1; i <= n * n; i++) {
		int cy = student[i].y;
		int cx = student[i].x;
		
		//그 학생의 인근 선호도 조사 
		int love = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];
			
			//범위 초과
			if (ny >= n || nx >= n || ny < 0 || nx < 0)
				continue;
			//인근에 학생이 있다면
			if (board[ny][nx] !=0) {
				//선호학생인지 검사
				for (int s = 0; s < 4; s++) {
					if (board[ny][nx] == student[i].love[s]) {
						love++;
						break;
					}
				}
			}
		}
		//만족도 점수 
		result += satisfy[love];
	}
	return;
}

void simulation(vector<STUDENT>& student) {
	//시뮬레이션 시작
	result = 0;
	setting_sit(student);
	get_satisfy_score(student);
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	//벡터 초기화
	vector<STUDENT> student((n * n)+1);
	for (int i = 1; i <= n * n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		student[i].student_idx = a;
		student[i].love[0] = b;
		student[i].love[1] = c;
		student[i].love[2] = d;
		student[i].love[3] = e;
	}
	simulation(student);
	cout << result << '\n';
	return 0;
}
