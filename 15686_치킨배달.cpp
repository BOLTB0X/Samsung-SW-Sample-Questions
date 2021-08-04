#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x7fffffff;
int n, m;
int result;
int graph[50][50];
vector<pair<int, int>> house, chicken;
bool visited[13];

int distance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void DFS(int idx, int selected) {
    //조건 만족
    if (selected == m) {
        int tempResult = 0;
        for (int i = 0; i < house.size(); i++) {
            int dist = INF;
            for (int j = 0; j < chicken.size(); j++)
                if (visited[j])
                    dist = min(dist, distance(house[i], chicken[j]));
            tempResult += dist;
        }
        result = min(result, tempResult);
        return;
    }

    //기저 사례
    if (idx == chicken.size()) return;

    //프랜차이즈 선정
    visited[idx] = true;
    DFS(idx + 1, selected + 1);
    //프랜차이즈 선정 X
    visited[idx] = false;
    DFS(idx + 1, selected);
}

int main(void) {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 1)
                house.push_back({ i, j });
            else if (graph[i][j] == 2)
                chicken.push_back({ i, j });
        }
    }

    result = INF;
    DFS(0, 0);
    cout << result << "\n";
    return 0;
}
