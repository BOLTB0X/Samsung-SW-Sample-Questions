#include <iostream>
#include <vector>

using namespace std;

//위치
struct POS {
	int y, x;
};

//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//절댓값
int abs(int a) {
	return a < 0 ? -a : a;
}

int n, m,result;
int board[50][50];
bool visited[14] = { false, };

//최소값을 위한
int INF = 0x7fffffff;
vector<POS> house;
vector<POS> store;

//멘하탄 거리
int manhattan_dist(POS a, POS b) {
	return abs(a.y - b.y) + abs(a.x - b.x);
}

//치킨거리 반환
int get_dist(void) {
	int tmp_result = 0;
	//완전탐색으로 집과 치킨집의 최소의 치킨 거리의 합을 구함
	for (int i = 0; i < house.size(); i++) {
		int dist = INF;
		for (int j = 0; j < store.size(); j++) {
			if (visited[j])
				dist = min(dist, manhattan_dist(house[i], store[j]));
		}
		tmp_result += dist;
	}
	return tmp_result;
}

//조합 == 백트래킹
void combination(int cur, int depth) {
	//깊이가 도달하면
	if (depth == m) {
		//최소값 
		result = min(result, get_dist());
		return;
	}
	//깊이 이전 집의 갯수랑 같아지면
	if (cur == store.size())
		return;
	visited[cur] = true;
	combination(cur + 1, depth + 1);
	visited[cur] = false;
	combination(cur + 1, depth);
	return;
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//입력
	cin >> n >> m;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> board[y][x];
			//집인 경우
			if (board[y][x] == 1) {
				house.push_back({ y,x });
			}
			//치킨집인 경우
			else if (board[y][x] == 2) {
				store.push_back({ y,x });
			}
		}
	}
	result = INF;
	//백트래킹 시작
	combination(0,0);
	cout << result << '\n';
	return 0;
}

