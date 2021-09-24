#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int board[21][21];
int p[5];

int n, result;

//�����
void backup(int(*from)[21], int(*to)[21]) {
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			to[y][x] = from[y][x];
		}
	}
	return;
}
//
void move(int dir) {
    vector<int> v;
    //�� 0 �� 1 �� 2 �� 3
    if (dir == 0) {
        for (int y = 1; y <= n; y++) {
            for (int x = n; x >= 1; x--) {
                if (board[y][x]) 
                    v.push_back(board[y][x]);
                board[y][x] = 0;
            }
            for (int j = 0, idx = n; j < v.size(); j++) {
                if (v[j] == v[j + 1] && j + 1 < v.size()) 
                    board[y][idx] = v[j++] * 2;
                else 
                    board[y][idx] = v[j];
                idx--;
            }
            v.clear();
        }
    }
    else if (dir == 1) {
        for (int y = 1; y <= n; y++) {
            for (int x = 1; x <= n; x++) {
                if (board[y][x]) 
                    v.push_back(board[y][x]); // ó������ ���鼭 ���Ϳ� �ϴ� �� �־��ش�.
                board[y][x] = 0; // �־��ָ鼭 ���� �ʱ�ȭ
            }
            for (int j = 0, idx = 1; j < v.size(); j++) { // ���͸� ó������ ������ ���鼭
                if (v[j] == v[j + 1] && j + 1 < v.size()) 
                    board[y][idx] = v[j++] * 2; // ���� ������ ���簪�� �������� ������ ��ĥ �� ������ 2�� ���� ���� �־��ش�. �� ��쿣 �ѹ� �� j++�� ������Ѵ�.
                else 
                    board[y][idx] = v[j]; // �ٸ��ٸ� �׳� ���� ���Ͱ��� �ʿ� �־��ش�.
                idx++;
            }
            v.clear();
        }
    }
    else if (dir == 2) {
        for (int y = 1; y <= n; y++) {
            for (int x = n; x >= 1; x--) {
                if (board[x][y]) 
                    v.push_back(board[x][y]);
                board[x][y] = 0;
            }
            for (int j = 0, idx = n; j < v.size(); j++) {
                if (v[j] == v[j + 1] && j + 1 < v.size()) 
                    board[idx][y] = v[j++] * 2;
                else 
                    board[idx][y] = v[j];
                idx--;
            }
            v.clear();
        }
    }
    else {
        for (int y = 1; y <= n; y++) {
            for (int x = 1; x <= n; x++) {
                if (board[y][x]) 
                    v.push_back(board[x][y]);
                board[x][y] = 0;
            }
            for (int j = 0, idx = 1; j < v.size(); j++) {
                if (v[j] == v[j + 1] && j + 1 < v.size()) 
                    board[idx][y] = v[j++] * 2;
                else 
                    board[idx][y] = v[j];
                idx++;
            }
            v.clear();
        }
    }
}

//������� �ߺ����� �̵���Ŵ
void rotate() {
	for (int i = 0; i < 5; i++) {
		move(p[i]);
	}
    for (int y = 1; y <= n; y++) { // �ִ��� ���ϴ� ����
        for (int x = 1; x <= n; x++) {
            if (result < board[y][x]) 
                result = board[y][x];
        }
    }
	return;
}

//DFS�� �ߺ�����
void DFS(int cnt) {
	if (cnt == 5) {
		int c_board[21][21];
		backup(board, c_board);
		rotate();
		backup(c_board, board);
		return;
	}

	for (int i = 0; i < 5; i++) {
		p[cnt] = i;
		DFS(cnt + 1);
	}
}

int main(void) {
	//�Է�
	scanf("%d", &n);
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			scanf("%d", &board[y][x]);
		}
	}
    result = 0;
	DFS(0);
	printf("%d\n", result);
	return 0;
}