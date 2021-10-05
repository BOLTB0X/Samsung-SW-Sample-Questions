#include <iostream>
#include <vector>

using namespace std;

struct NODE {
    int y, x;
};

int n, m, d, s, result;
int board[50][50];
bool visited[50][50];
vector<NODE> clouds;

const int dy[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
const int dx[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

//구름 초기화
void clouds_init(void) {
    clouds.push_back({ n - 1,0 });
    clouds.push_back({ n - 1,1 });
    clouds.push_back({ n - 2,0 });
    clouds.push_back({ n - 2,1 });
}

//구름 이동
void move_clouds(int d, int s) {
    s = s % n;
    for (int c = 0; c < clouds.size(); ++c) {
        clouds[c].y = (clouds[c].y + s * dy[d] + n) % n;
        clouds[c].x = (clouds[c].x + s * dx[d] + n) % n;
        board[clouds[c].y][clouds[c].x]++;
        visited[clouds[c].y][clouds[c].x] = true;
    }
}

//물복사 버그
void copy_bug() {
    for (NODE cur : clouds) {
        int wcnt = 0;
        for (int k = 2; k <= 8; k += 2) {
            int ny = cur.y + dy[k];
            int nx = cur.x + dx[k];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                continue;
            if (board[ny][nx])
                wcnt++;
        }
        board[cur.y][cur.x] += wcnt;
    }
}

//구름 생성
void new_clouds(void) {
    vector<NODE> tmp = clouds;
    clouds.clear();

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (visited[y][x] || board[y][x] < 2)
                continue;
            clouds.push_back({ y,x });
            board[y][x] -= 2;
        }
    }

    for (NODE cur : tmp) {
        visited[cur.y][cur.x] = false;
    }
    tmp.clear();
}

//총 물량
void get_tot_water(void) {
    int tot = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            tot += board[y][x];
        }
    }
    result = tot;
}

//시뮬레이션
void simulation(void) {
    //시뮬전 초기화
    clouds_init();
    while (m--) {
        //방향 속력 입력
        cin >> d >> s;
        move_clouds(d,s);
        copy_bug();
        new_clouds();
    }
    get_tot_water();
}

int main(void) {
    //초기화
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //맵 입력
    cin >> n >> m;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> board[y][x];
        }
    }
    //시뮬시작
    simulation();
    //정답 출력
    cout << result << '\n';
    return 0;
}