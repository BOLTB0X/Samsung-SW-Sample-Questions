#include <iostream> 
#include <vector> 

using namespace std; 

typedef struct fish { 
	int num; 
	int dir; 
}fish; 

typedef struct INF { 
	int y; 
	int x; 
	bool alive; // 0 = dead 
}INF; 

fish map[4][4]; 
fish shark; 
INF fish_pos[17]; // 0 is not used 

const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; 
const int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1}; 
int result; 

bool isRange(int r, int c) { 
	if (r < 0 || r >= 4 || c < 0 || c >= 4) { 
		return false; 
	} 
	else 
		return true; 
} 

void swap(fish &a, fish &b) { 
	fish temp = a; 
	a = b; 
	b = temp; 
} 

void swap_pos(INF &a, INF &b) { 
	INF temp = a; 
	a = b; 
	b = temp; 
} 

void fish_move() { 
	fish t_fish; 
	int ny, nx, nd; 
	int y, x; 
	
	INF move_it; 
	for (int i = 1; i <= 16; i++) { 
		move_it = fish_pos[i]; 
		y = move_it.y; 
		x = move_it.x; 
		if (move_it.alive) { 
			t_fish = map[y][x]; // if it is a fish 
			if (t_fish.num >= 1 && t_fish.num <= 16) { 
				for (int d = 0; d < 8; d++) { 
					nd = (t_fish.dir + d) % 8; 
					//map[r][c].dir = n_d; 
					ny = y + dy[nd]; 
					nx = x + dx[nd]; 
					if (!isRange(ny, nx) || map[ny][nx].num == 100) { 
						continue; 
					} 
					if (map[ny][nx].num == 0) { 
						map[ny][nx] = { t_fish.num, nd }; 
						map[y][x].num = 0; 
						fish_pos[i] = { ny, nx, 1}; 
						break; 
					} 
					
					if (map[ny][nx].num >= 1 && map[ny][nx].num <= 16) { 
						fish_pos[i] = { ny, nx, 1 }; 
						fish_pos[map[ny][nx].num] = { y, x, 1 }; 
						map[y][x].dir = nd; 
						swap(map[y][x], map[ny][nx]); 
						//swap_pos(fish_pos[i], fish_pos[map[n_r][n_c].num]); 
						break; 
					} 
				} 
			} 
		} 
	} 
} 

void copy_map(fish dst[4][4], fish src[4][4]) { 
	for (int i = 0; i < 4; i++) { 
		for (int j = 0; j < 4; j++) { 
			dst[i][j] = src[i][j]; 
		} 
	} 
} 

void copy_pos(INF dst[17], INF src[17]) { 
	for (int i = 1; i <= 16; i++) { 
		dst[i] = src[i]; 
	} 
} 

void dfs(int sum, int sh_row, int sh_col) { 
	// first, move the fish 
	fish_move(); 
	// terminator 
	// if nowhere else to go (shark), then return 
	int ny, nx, nd; 
	fish t_fish, t_shark; 
	fish backup[4][4]; 
	INF back_pos[17]; 
	nd = map[sh_row][sh_col].dir; 
	
	vector<int> leap; // how much leap that shark can take 
	
	for (int i = 1; i <= 3; i++) { 
		ny = sh_row + dy[nd] * i; 
		nx = sh_col + dx[nd] * i; 
		
		if (isRange(ny, nx) && map[ny][nx].num != 0) { 
			leap.push_back(i); 
		} 
	} 
	// go home 
	if (leap.empty()) { 
		result = max(result, sum); 
		return; 
	} 
	else { // move shark and dfs 
		for (int i = 0; i < leap.size(); i++) { 
			// new position 
			ny = sh_row + dy[nd] * leap[i]; 
			nx = sh_col + dx[nd] * leap[i]; 
			
			// copy original 
			t_shark = map[sh_row][sh_col]; 
			t_fish = map[ny][nx]; 
			copy_map(backup, map); 
			copy_pos(back_pos, fish_pos); 
			
			// move shark 
			// empty original 
			map[sh_row][sh_col].num = 0; 
			
			// fill the new tile (obsorbs direction) 
			map[ny][nx].num = 100; 
			fish_pos[t_fish.num].alive = 0; 
			
			// dfs 
			dfs(sum + t_fish.num, ny, nx); 
			
			// restore 
			copy_map(map, backup); 
			copy_pos(fish_pos, back_pos); 
		} 
	} 
} 

int main() {
	//ÃÊ±âÈ­
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t_n, t_d; 
	fish start; 
	result = 0; 
	
	for (int i = 0; i < 16; i++) { 
		cin >> t_n >> t_d; 
		map[i / 4][i % 4] = { t_n, t_d - 1 }; 
		fish_pos[t_n] = { i / 4, i % 4, 1 }; 
	} 
	// shark eats the first one 
	start = map[0][0]; 
	
	result += start.num; 
	
	map[0][0].num = 100; 
	fish_pos[start.num].alive = false; 
	dfs(result, 0, 0); 
	
	cout << result << endl; 
}