#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>

int main(void) {
	int n;

	scanf("%d", &n);
	//동적할당
	int* dp = (int*)malloc(sizeof(int) * (n + 1));
	int* T = (int*)malloc(sizeof(int) * (n + 1));
	int* P = (int*)malloc(sizeof(int) * (n + 1));

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &T[i], &P[i]);
		dp[i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			//해당 범위내
			if (j + T[j] - 1 <= i) {
				if (dp[i] < dp[j - 1] + P[j])
					dp[i] = dp[j - 1] + P[j];
			}
		}
	}
	printf("%d\n", dp[n]);
	free(dp);
	free(T);
	free(P);
	return 0;
}