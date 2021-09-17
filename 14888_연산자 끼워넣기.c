#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//최대
int max(int a, int b) {
	return a > b ? a : b;
}
//최소
int min(int a, int b) {
	return a < b ? a : b;
}

int n, max_result = -0x7fffffff, min_result = 0x7fffffff;

void DFS(int *arr,int tot, int add, int sub, int mul, int div, int idx) {
	if (idx == n) {
		max_result = max(max_result, tot);
		min_result = min(min_result, tot);
		return;
	}
	else {
		if (add > 0) {
			DFS(arr,tot + arr[idx], add - 1, sub, mul, div, idx + 1);
		}
		if (sub > 0) {
			DFS(arr,tot - arr[idx], add, sub - 1, mul, div, idx + 1);
		}
		if (mul > 0) {
			DFS(arr,tot * arr[idx], add, sub, mul - 1, div, idx + 1);
		}
		if (div > 0) {
			DFS(arr,(int)tot / arr[idx], add, sub, mul, div - 1, idx + 1);
		}
	}
}

int main(void) {
	int numbers[11];
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) 
		scanf("%d", &numbers[i]);

	int add, sub, mul, div;

	scanf("%d %d %d %d", &add, &sub, &mul, &div);
	DFS(numbers,numbers[0], add, sub, mul, div, 1);
	
	printf("%d\n", max_result);
	printf("%d\n", min_result);
	return 0;
}
