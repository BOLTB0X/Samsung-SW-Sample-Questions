#include <iostream>
#include <string>
using namespace std;

int n;//문자열 길이
string str;// 수식
int num[20];
char op[20];
int num_idx = 0, op_idx = 0;
int result = -0x7fffffff;

int max(int a, int b) {
	return a > b ? a : b;
}

int cal(int tot, int num, char op) {
	if (op == '+')
		return tot + num;
	else if (op == '-')
		return tot - num;
	else
		return tot * num;
}

void DFS(int tot, int depth) {
	//탈출 조건
	if (op_idx == depth) {
		result = max(result, tot);
		return;
	}
	
	int cur = cal(tot, num[depth + 1], op[depth]);
	DFS(cur, depth + 1);
	
	//괄호
	if (depth + 1 < op_idx) {
		int tmp = cal(num[depth + 1], num[depth + 2], op[depth + 1]);
		int next = cal(tot, tmp, op[depth]);
		DFS(next, depth + 2);
	}
}

int main(void) {
	ios::sync_with_stdio(0); 
	cin.tie(0); 
	cout.tie(0);
	
	cin >> n;
	cin >> str;
	
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) num[num_idx++] = str[i] - '0';
		else op[op_idx++] = str[i];
	}

	DFS(num[0], 0);
	cout << result << '\n';
	return 0;
}
