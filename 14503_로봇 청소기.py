from collections import deque

n,m=map(int,input().split()) #n은 세로 m은 가로
row,col,direction=map(int,input().split()) # 행 열 방향 
graph=[] # 맵

for i in range(n): #맵 생성
    graph.append(list(map(int,input().split())))
# 북 동 남 서
dx=[-1,0,1,0]
dy=[0,1,0,-1]

#    0
# 3     1
#    2

def turn_left(direction): #방향 전환
    if direction==0:
        return 3
    elif direction == 1:
        return 0
    elif direction == 2:
        return 1
    elif direction == 3:
        return 2

def turn_back(direction): #방향 전환
    if direction==0:
        return 2
    elif direction == 1:
        return 3
    elif direction == 2:
        return 0
    elif direction == 3:
        return 1

def BFS(row,col,direction):
    cnt = 1
    graph[row][col] = 2 # 청소 체크
    que = deque([[row,col,direction]])

    while que: # 큐가 빌때가지
        row,col,direction = que.popleft()
        tmp_direction=direction
        for i in range(4):
            tmp_direction = turn_left(tmp_direction) #왼쪽방향부터 확인
            new_row=row+dx[tmp_direction]
            new_col=col+dy[tmp_direction]

            # 범위에 해당하고 청소하지 않았다면
            if  0 <= new_row < n and 0 <= new_col < m and graph[new_row][new_col] == 0:
                cnt+=1
                graph[new_row][new_col] = 2
                que.append([new_row, new_col, tmp_direction])
                break

            elif i == 3: # 위 반복문이 다 반복할 동안 갈곳을 찾지 못한다면
                #후진
                new_row=row+dx[turn_back(direction)]
                new_col=col+dy[turn_back(direction)]
                # 첫 번째 단계로 돌아감
                que.append([new_row,new_col,direction])
                
                # 만약 후진을 해도 꽉 막혔다면
                if graph[new_row][new_col] == 1:
                    return cnt
answer = BFS(row,col,direction)
print(answer)