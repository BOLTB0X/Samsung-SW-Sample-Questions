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
	//�� ������, ���� ������
	int major, sub;
	scanf("%d %d", &major, &sub);

	long long result = 0;

	for (int i = 0; i < n; i++) {
		//�� ĭ�� �Ѱ����� Ŀ�� ���� �� �� ����
		arr[i] =arr[i] - major;
		result++;
		
		// Ŀ������ �� ������ ũ�ٸ�
		if (arr[i] > 0) {
			//�������� ����
			result = result + (arr[i] / sub);
			if (arr[i] % sub > 0)
				result++;
		}
	}

	printf("%lld\n", result);
	free(arr);
	return 0;
}