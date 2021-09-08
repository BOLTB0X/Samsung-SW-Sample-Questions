#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x7fffffff;
int n, m, result;
int map[51][51];
vector<pair<int, int>> house;
vector<pair<int, int>> chicken;
bool visited[14];

int manhattan_dist(pair<int, int> a, pair<int, int> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int get_chicken_dist() {
	int tmp_result = 0;
	for (int i = 0; i < house.size(); i++) {
		int dist = INF;
		for (int j = 0; j < chicken.size(); j++) {
			if (visited[j])
				dist = min(dist, manhattan_dist(house[i], chicken[j]));
		}
		tmp_result += dist;
	}
	return tmp_result;
}

void combination(int idx, int select_cnt) {
	if (select_cnt == m) {
		result = min(result, get_chicken_dist());
		return;
	}

	if (idx == chicken.size())
		return;
	visited[idx] = true;
	combination(idx + 1, select_cnt + 1);
	visited[idx] = false;
	combination(idx + 1, select_cnt);
}

int main(void) {
	//초기화
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	//입력
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back({ i,j });
			else if (map[i][j] == 2)
				chicken.push_back({ i,j });
		}
	}

	result = INF;
	combination(0, 0);
	cout << result << "\n";
	return 0;
}
