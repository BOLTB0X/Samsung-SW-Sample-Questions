#include <iostream>
#include <queue>

using namespace std;

//우선 순위 큐 조건 변경
struct INFO {
	int y, x, blank, love;
	//정렬조건 수정
	bool operator < (const INFO& i) const {
		if (love == i.love) {
			if (blank == i.blank) {
				if (y == i.y) {
					return x > i.x;
				}
				return y > i.y;
			}
			return blank < i.blank;
		}
		return love < i.love;
	}
};

//학생 정보들 담는 구조체
struct STUDENT {
	int student_idx;
	int love[4];
	int y;
	int x;
};

int n, result;
int board[21][21] = { 0, };

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };
//만족도
const int satisfy[5] = { 0,1,10,100,1000 };

//자리배치
void setting_sit(STUDENT* students) {
	//학생배열을 순회하며 
	for (int i = 1; i <= n * n; i++) {
		priority_queue<INFO> pq;
		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= n; x++) {
				//해당위치에 자리 배치가 가능하다면
				int blank_cnt = 0, love_cnt = 0;
				if (board[y][x] == 0) {
					//상하좌우에 빈공간,선호학생 체크
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];
						
						//범위 초과
						if (ny > n || nx > n || nx < 1 || ny < 1)
							continue;
						//빈공간
						if (board[ny][nx] == 0)
							blank_cnt++;
						//학생을 본다면
						else {
							for (int j = 0; j < 4; j++) {
								if (board[ny][nx] == students[i].love[j]) {
									love_cnt++;
									break;
								}
							}
						}
					}
					//우선순위 큐에 삽입
					pq.push({ y,x,blank_cnt,love_cnt });
				}
			}
		}
		//다음 학생으로 넘어가지 전 우선순위 큐에 원소가 있다면
		if (!pq.empty()) {
			int y = pq.top().y;
			int x = pq.top().x;
			board[y][x] = students[i].student_idx;
			pq.pop();

			students[i].y = y;
			students[i].x = x;
		}
	}
	return;
}

//만족도 계산
void get_satisfy(STUDENT* students) {
	for (int i = 1; i <= n * n; i++) {
		int y = students[i].y;
		int x = students[i].x;
		
		//각 학생마다 인근 선호학생 체크
		int love = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			
			//범위 체크
			if (ny > n || nx > n || nx < 1 || ny < 1)
				continue;
			//주변 선호학생
			for (int j = 0; j < 4; j++) {
				if (board[ny][nx] == students[i].love[j]) {
					love++;
				}
			}
		}
		//만족도 점수 득점
		result += satisfy[love];
	}
	return;
}

//시뮬레이션
void simulation(STUDENT* students) {
	//자리 배정
	setting_sit(students);
	//만족도 검사
	get_satisfy(students);
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n;
	//n*n크기만큼 동작할당;
	STUDENT* students = new STUDENT[(n * n)+1];
	for (int i = 1; i <= n * n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		students[i].student_idx = a;
		students[i].love[0] = b;
		students[i].love[1] = c;
		students[i].love[2] = d;
		students[i].love[3] = e;
	}
	//결과 초기화
	result = 0;
	//시뮬
	simulation(students);
	cout << result << '\n';
	//메모리 해제
	delete[] students;
	return 0;
}
