#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

struct INF {
	int y, x;
};

int n, m, result;
int map[50][50];
INF house[14];
int house_size = 0;
INF store[14];
int store_size = 0;
bool visited[14];

//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//절댓값
int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}

//맨하튼 거리
int manhattan_dist(INF a, INF b) {
	return abs(a.y - b.y) + abs(a.x - b.x);
}

//치킨거리
int get_dist(void) {
	int tmp_result = 0;
	for (int i = 0; i < house_size; i++) {
		int dist = 0x7fffffff;
		for (int j = 0; j < store_size; j++) {
			if (visited[j])
				dist = min(dist, manhattan_dist(house[i], store[j]));
		}
		tmp_result += dist;
	}
	return tmp_result;
}

void combination(int idx, int depth) {
	if (depth == m) {
		result = min(result, get_dist());
		return;
	}
	if (idx == store_size)
		return;
	visited[idx] = true;
	combination(idx + 1, depth + 1);
	visited[idx] = false;
	combination(idx + 1, depth);
}

int main(void) {
	//입력
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &map[y][x]);
			//집인 경우
			if (map[y][x] == 1) 
				house[house_size++] = { y,x };
			//상점인 경우
			if (map[y][x] == 2) 
				store[store_size++] = { y,x };
		}
	}
	result = 0x7fffffff;
	combination(0, 0);
	printf("%d", result);
	return 0;
}
