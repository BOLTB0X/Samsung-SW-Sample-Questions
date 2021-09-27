#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//학생들의 정보를 담는 구조체
struct STUDENT {
	int student_idx;
	int love[4];
	int y;
	int x;
};

//우선순위를 위한 구조체
struct INFO {
	int y;
	int x;
	int blank_cnt;
	int love_cnt;

	bool operator < (const INFO& i) const {
		//1순위 선호도
		if (love_cnt == i.love_cnt) {
			//2순위 빈공간
			if (blank_cnt == i.blank_cnt) {
				//행
				if (y == i.y) {
					return x > i.x;
				}
				//열
				else
					return y > i.y;
			}
			else
				return blank_cnt < i.blank_cnt;
		}
		else
			return love_cnt < i.love_cnt;
	}
};

//맵 정보
int n,result;
int board[20][20];

//연산 필요한 고정 배열
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };
const int satisfy[5] = { 0,1,10,100,1000 };

//자리 배정
//각 자리에대한 인근 선호도와 빈공간 수를 체크
//그 후 우선순위 큐에 넣고 우선순위별로 뽑아 맵에 체크
void setting_sit(vector<STUDENT>& student) {
	//벡터에 담긴 학생이 기준
	for (int i = 1; i <= n * n; i++) {
		//이에 맞추어 pq선언
		priority_queue<INFO> pq;
		//맵 탐색
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				// 자리배정 가능한 칸을 만나면
				if (board[y][x] == 0) {
					int near_blank = 0, near_love = 0;
					//상하좌우를 탐색하며 인근 선호도, 빈공간 수 카운트
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];
						
						//맵 초과
						if (ny >= n || nx >= n || ny < 0 || nx < 0)
							continue;
						//빈공간
						if (board[ny][nx] == 0)
							near_blank++;
						//학생을 보게 되면
						else {
							for (int j = 0; j < 4; j++) {
								if (board[ny][nx] == student[i].love[j]) {
									near_love++;
									break;
								}
							}
						}
					}
					//삽입
					pq.push({ y,x,near_blank,near_love });
				}
			}
		}
		//삽입이 되어진게 있으면 맵에 체크
		if (!pq.empty()) {
			int y = pq.top().y;
			int x = pq.top().x;
			pq.pop();
			board[y][x] = student[i].student_idx;
			student[i].y = y;
			student[i].x = x;
		}
	}
	return;
}

//만족도 검사
void get_satisfy(vector<STUDENT>& student) {
	//벡터에 담긴 학생들 순회
	for (int i = 1; i <= n * n; i++) {
		int cy = student[i].y;
		int cx = student[i].x;
		int love = 0;
		//인근 선호도 학생 체크
		for (int dir = 0; dir < 4; dir++) {
			int ny = cy + dy[dir];
			int nx = cx + dx[dir];
			
			//범위 초과
			if (ny >= n || nx >= n || ny < 0 || nx < 0)
				continue;
			//선호학생이 있으면
			for (int j = 0; j < 4; j++) {
				if (board[ny][nx] == student[i].love[j]) {
					love++;
					break;
				}
			}
		}
		//만족도 결과에 더 해준다.
		result += satisfy[love];
	}
	return;
}

//시뮬레이션 
void simulation(vector<STUDENT>& student) {
	setting_sit(student);
	get_satisfy(student);
	return;
}

//메인
int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//벡터관련 입력
	cin >> n;
	//초기화
	vector<STUDENT> student((n * n) + 1);
	//학생 정보입력
	for (int i = 1; i <= n * n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		student[i].student_idx = a;
		student[i].love[0] = b;
		student[i].love[1] = c;
		student[i].love[2] = d;
		student[i].love[3] = e;
	}
	//연산을 위해 0으로 초기화
	result = 0;
	//시뮬시작
	simulation(student);
	cout << result << '\n';
	return 0;
}
