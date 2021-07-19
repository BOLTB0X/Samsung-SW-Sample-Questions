from collections import deque

n,m=map(int,input().split()) #세로 가로
r,c,d=map(int,input().split()) #d= 0(하) 1(우) 2(상) 3(좌)
graph=[]

for i in range(n): #맵 생성
    graph.append(list(map(int,input().split())))
# 북 동 남 서
dx=[-1,0,1,0] # 하 상
dy=[0,1,0,-1] # 우 좌

#    0
# 3     1
#    2

#방향 전환
def turn_left(d): #방향을 왼쪽으로 돌리는 함수
    if d==0:
        return 3
    elif d==1:
        return 0
    elif d==2:
        return 1
    elif d==3:
        return 2

#빽 스탭
def back(d):
    if d == 0:
        return 2
    elif d == 1:
        return 3
    elif d == 2:
        return 0
    elif d == 3:
        return 1

def BFS(r,c,d): #풀이 
    cnt = 1  #청소하는 칸의 개수
    graph[r][c] = 2 #방문체크
    que=deque([[r,c,d]])
    
    while que:
        r,c,d=que.popleft()
        temp_d=d

        for i in range(4): # 왼 쪽 방향부터 차례대로 인접한 칸을 탐색한다
            temp_d = turn_left(temp_d) #방향 전환
            new_row, new_col = r + dx[temp_d], c + dy[temp_d]

            # 범위에 해당하고 청소할 곳이 존재한다면
            if 0 <= new_row < n and 0 <= new_col < m and graph[new_row][new_col] == 0:
                cnt += 1
                graph[new_row][new_col] = 2
                que.append([new_row, new_col, temp_d])
                break
            
            elif i == 3:  # 갈 곳이 없었던 경우
                new_row, new_col = r + dx[back(d)], c + dy[back(d)]
                que.append([new_row, new_col, d])

                # 꽉 막혔을 경우
                if graph[new_row][new_col] == 1:  # 뒤가 벽인 경우
                    return cnt

answer = BFS(r,c,d)
print(answer)