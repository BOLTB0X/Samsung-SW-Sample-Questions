#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int* arr = (int *)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	//총 감독관, 보조 감독관
	int major, sub;
	scanf("%d %d", &major, &sub);

	long long result = 0;

	for (int i = 0; i < n; i++) {
		//이 칸의 총감독이 커버 가능 한 수 빼기
		arr[i] =arr[i] - major;
		result++;
		
		// 커버가능 한 수보다 크다면
		if (arr[i] > 0) {
			//보조감독 투입
			result = result + (arr[i] / sub);
			if (arr[i] % sub > 0)
				result++;
		}
	}

	printf("%lld\n", result);
	free(arr);
	return 0;
}