#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, max_result = -0x7fffffff, min_result = 0x7fffffff;

//최대
int max(int a, int b) {
	return a > b ? a : b;
}
//최소
int min(int a, int b) {
	return a < b ? a : b;
}

//깊이우선을 이용하는 백트래킹
void DFS(int* arr, int tot, int add, int sub, int mul, int div, int idx) {
	//탈출조건
	if (idx == n) {
		max_result = max(max_result, tot);
		min_result = min(min_result, tot);
		return;
	}
	//그 이외
	else {
		if (add > 0) {
			DFS(arr, tot + arr[idx], add - 1, sub, mul, div, idx + 1);
		}
		if (sub > 0) {
			DFS(arr, tot - arr[idx], add, sub - 1, mul, div, idx + 1);
		}
		if (mul > 0) {
			DFS(arr, tot * arr[idx], add, sub, mul - 1, div, idx + 1);
		}
		if (div > 0) {
			DFS(arr, (int)tot / arr[idx], add, sub, mul, div - 1, idx + 1);
		}
	}
}

int main(void) {
	int numbers[11];

	//입력
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	int add, sub, mul, div;
	
	//연산자들 입력
	scanf("%d %d %d %d", &add, &sub, &mul, &div);
	//DFS 탐새시작
	DFS(numbers, numbers[0], add, sub, mul, div, 1);

	//정답 도출
	printf("%d\n", max_result);
	printf("%d\n", min_result);
	return 0;
}
