#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

//학생들의 정보를 담는 구조체
struct STUDENT {
	int student_idx;
	int love[4];
	int y, x;
};

//우선순위 큐를 위한 구조체
struct INF {
	int y, x, blank, love;
	//우선순위 조건에 맞게 수정
	bool operator < (const INF &i) const {
		if (love == i.love) {
			if (blank == i.blank) {
				if (y == i.y)
					return x > i.x;
				else
					return y > i.y;
			}
			else
				return blank < i.blank;
		}
		else
			return love < i.love;
	}
};

int n, result;
int board[20][20] = { 0, };
vector<STUDENT> students(400);

//만족도 점수
const int satisfy[5] = { 0,1,10,100,1000 };
//상하좌우
const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

//상어 학생들의 자리배정
void setting_sit(void) {
	//기존 벡터에 저장된 학생들 뽑기
	for (int i = 0; i < n * n; i++) {
		//우선순위 큐 필요
		priority_queue<INF> pq;
		//그래프 탐색 시작
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				//만약 위치가 빈칸이라면
				//이 위치에 따른 빈공간, 선호도를 알아야함
				if (board[y][x] == 0) {
					//각 빈공간과 선호도 체크
					int blank_cnt = 0, love_cnt = 0;
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];
						//범위 초과시
						if (nx < 0 || ny < 0 || ny >= n || nx >= n)
							continue;
						//빈공간 수 체크
						if (board[ny][nx] == 0)
							blank_cnt++;
						//학생을 만난다면
						else {
							//지금 메인인 학생의 선호도학생들 탐색
							for (int s = 0; s < 4; s++) {
								if (board[ny][nx] == students[i].love[s]) {
									love_cnt++;
									break;
								}
							}
						}
					}
					pq.push({ y,x,blank_cnt,love_cnt });
				}
			}
		}
		//우선순위 큐가 비어있지않다면
		if (!pq.empty()) {
			//최상단 원소가 문제조건에 맞는 학생
			int y = pq.top().y;
			int x = pq.top().x;
			//맵에 해당 학생 배치
			board[y][x] = students[i].student_idx;
			//해당 학생의 위치정보 벡터에 삽입
			students[i].y = y;
			students[i].x = x;
		}
	}
}

//만족도 조사
void get_satisfy_score(void) {
	result = 0;
	//각 학생의 만족도를 알아야함
	for (int i = 0; i < n * n; i++) {
		//대상인 학생의 위치 확인
		int y = students[i].y;
		int x = students[i].x;

		//그 학생 주위 인접한 학생들 탐색
		int love = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			//범위 초과시
			if (nx < 0 || ny < 0 || ny >= n || nx >= n)
				continue;
			//그 학생들과 메인 학생의 선호도 배열과 확인
			for (int k = 0; k < 4; k++) {
				if (board[ny][nx] == students[i].love[k]) {
					love++;
					break;
				}
			}
		}
		//총 love수만큼 
		result += satisfy[love];
	}
}

//시뮬레이션 시작
void simulation(void) {
	setting_sit();
	get_satisfy_score();
}

int main(void) {
	//입력
	scanf("%d", &n);
	//상어 학생번호 입력
	for (int i=0;i<n*n;i++) {
		int idx;
		scanf("%d", &idx);
		students[i].student_idx = idx;
		//선호 학생들 입력
		for (int j = 0; j < 4; j++) {
			int a;
			scanf("%d", &a);
			students[i].love[j] = a;
		}
	}
	simulation();
	printf("%d", result);
	return 0;
}
