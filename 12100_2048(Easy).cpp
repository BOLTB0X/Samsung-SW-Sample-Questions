#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int board[21][21];
int p[5];

int n, result;

//백업용
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
    //동 0 서 1 남 2 북 3
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
                    v.push_back(board[y][x]); // 처음부터 돌면서 벡터에 일단 다 넣어준다.
                board[y][x] = 0; // 넣어주면서 맵은 초기화
            }
            for (int j = 0, idx = 1; j < v.size(); j++) { // 벡터를 처음부터 끝까지 돌면서
                if (v[j] == v[j + 1] && j + 1 < v.size()) 
                    board[y][idx] = v[j++] * 2; // 만약 벡터의 현재값과 다음값이 같으면 합칠 수 있으니 2배 해준 값을 넣어준다. 이 경우엔 한번 더 j++를 해줘야한다.
                else 
                    board[y][idx] = v[j]; // 다르다면 그냥 현재 벡터값을 맵에 넣어준다.
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

//만들어진 중복순열 이동시킴
void rotate() {
	for (int i = 0; i < 5; i++) {
		move(p[i]);
	}
    for (int y = 1; y <= n; y++) { // 최댓값을 구하는 과정
        for (int x = 1; x <= n; x++) {
            if (result < board[y][x]) 
                result = board[y][x];
        }
    }
	return;
}

//DFS로 중복순열
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
	//입력
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