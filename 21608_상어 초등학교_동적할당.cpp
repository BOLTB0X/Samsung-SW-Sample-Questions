#include <iostream>
#include <queue>

using namespace std;

//�켱 ���� ť ���� ����
struct INFO {
	int y, x, blank, love;

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

//�л� ������ ��� ����ü
struct STUDENT {
	int student_idx;
	int love[4];
	int y;
	int x;
};

int n, result;
int board[21][21] = { 0, };

//�����¿�
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };
//������
const int satisfy[5] = { 0,1,10,100,1000 };

//�ڸ���ġ
void setting_sit(STUDENT* students) {
	//�л��迭�� ��ȸ�ϸ� 
	for (int i = 1; i <= n * n; i++) {
		priority_queue<INFO> pq;
		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= n; x++) {
				//�ش���ġ�� �ڸ� ��ġ�� �����ϴٸ�
				int blank_cnt = 0, love_cnt = 0;
				if (board[y][x] == 0) {
					//�����¿쿡 �����,��ȣ�л� üũ
					for (int dir = 0; dir < 4; dir++) {
						int ny = y + dy[dir];
						int nx = x + dx[dir];
						
						//���� �ʰ�
						if (ny > n || nx > n || nx < 1 || ny < 1)
							continue;
						//�����
						if (board[ny][nx] == 0)
							blank_cnt++;
						//�л��� ���ٸ�
						else {
							for (int j = 0; j < 4; j++) {
								if (board[ny][nx] == students[i].love[j]) {
									love_cnt++;
									break;
								}
							}
						}
					}
					//�켱���� ť�� ����
					pq.push({ y,x,blank_cnt,love_cnt });
				}
			}
		}
		//���� �л����� �Ѿ�� �� �켱���� ť�� ���Ұ� �ִٸ�
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

//������ ���
void get_satisfy(STUDENT* students) {
	for (int i = 1; i <= n * n; i++) {
		int y = students[i].y;
		int x = students[i].x;
		
		//�� �л����� �α� ��ȣ�л� üũ
		int love = 0;
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			
			//���� üũ
			if (y > n || x > n || x < 1 || y < 1)
				continue;
			//�ֺ� ��ȣ�л�
			for (int j = 0; j < 4; j++) {
				if (board[ny][nx] == students[i].love[j]) {
					love++;
				}
			}
		}
		//������ ���� ����
		result += satisfy[love];
	}
	return;
}

//�ùķ��̼�
void simulation(STUDENT* students) {
	setting_sit(students);
	get_satisfy(students);
	return;
}

int main(void) {
	//�ʱ�ȭ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//�Է�
	cin >> n;
	//n*nũ�⸸ŭ �����Ҵ�;
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
	//��� �ʱ�ȭ
	result = 0;
	//�ù�
	simulation(students);
	cout << result << '\n';
	//�޸� ����
	delete[] students;
	return 0;
}