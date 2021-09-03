#include <iostream>
#include <queue>
using namespace std;

int n, k, l;
int map[101][101];
deque<pair<int, int>> snake;
deque<pair<int, char>> dir_cmd;
//�� �Ʒ� �� ��
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int answer;

bool is_range(int row, int col) {
	if (row <1 || col <1 || row >n || col >n)
		return false;
	else
		return true;
}

int turn_dir(int cur_dir, char new_dir) {
	//���� ���
	if (cur_dir == 0) {
		if (new_dir == 'L')
			return 2;
		else
			return 3;
	}//�Ʒ��� ���
	else if (cur_dir == 1) {
		if (new_dir == 'L')
			return 3;
		else
			return 2;
	}//���� ���
	else if (cur_dir == 2) {
		if (new_dir == 'L')
			return 1;
		else
			return 0;
	}//���� ���
	else if (cur_dir == 3) {
		if (new_dir == 'L')
			return 0;
		else
			return 1;
	}
}

void simulation(int sec, int dir) {
	//�� �̵� ����
	int nr = snake.front().first + dr[dir];
	int nc = snake.front().second + dc[dir];
	//���� ��ġ�� ������ �����
	if (!is_range(nr, nc)) {
		answer = sec;
		return;
	}
	//���� ���� �΋H�� ���
	//�� ���� ���ҿ� ��ġ�� ���
	for (int i = 0; i < snake.size(); i++) {
		if ((nr == snake[i].first) && (nc == snake[i].second)) {
			answer = sec;
			return;
		}
	}
	//����� �߰��� ���
	if (map[nr][nc] == 1) {
		map[nr][nc] = 0; //��� ����
		//���� �տ� �����Ͽ� ���� ��ü ��ġ �̵�
		snake.push_front({ nr,nc });
	}
	//����� ������ ������ �̵��ؾ���
	else {
		snake.pop_back();
		snake.push_front({ nr,nc });
	}
	//���� ��ɾ ���� ��츦 ���
	int change_dir = dir;
	//��ɾ �����ϰ� �ش� �ʰ� �ȴٸ�
	if (!dir_cmd.empty() && dir_cmd.front().first == sec) {
		change_dir = turn_dir(dir, dir_cmd.front().second);
		dir_cmd.pop_front();
	}
	//�ð� ������ ���ο� �������� ���ȣ��
	simulation(sec + 1, change_dir);
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//���� ����,���� ����
	cin >> n;
	//��� ����
	cin >> k;
	//��� ��ġ
	for (int i = 0; i < k; i++) {
		int apple_r, apple_c;
		cin >> apple_r >> apple_c;
		map[apple_r][apple_c] = 1;
	}
	//��ɾ� �Է�
	cin >> l;
	for (int i = 0; i < l; i++) {
		int x;
		char ch;
		cin >> x >> ch;
		dir_cmd.push_back({ x,ch });
	}
	//���� �ʱ���ġ
	snake.push_back({ 1,1 });
	//���� �ʱ������ ������
	simulation(1, 3); //ī��Ʈ, ����
	cout << answer << '\n';
	return 0;
}