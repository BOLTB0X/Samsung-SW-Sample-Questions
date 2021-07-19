n,m=map(int,input().split())
data=[] #초기 맵 리스트
temp=[[0] * m for _ in range(n)]#벽을 설치한 뒤의 맵 리스트

for _ in range(n):
    data.append(list(map(int,input().split())))
dx=[-1,1,0,0] 
dy=[0,0,-1,1]
result=0

def virus(x,y): #바이러스가 사방으로 퍼지기
    for i in range(4):
        nx=x+dx[i]
        ny=y+dy[i]
        if nx >=0 and nx<n and ny>=0 and ny <m:
            if temp[nx][ny]==0: #바이러스 채우기
                temp[nx][ny]=2
                virus(nx,ny)

def get_score(): #안전영역의 크기 계산
    score=0
    for i in range(n):
        for j in range(m):
            if temp[i][j] == 0:
                score+=1
    return score  

def dfs(count):
    global result
    if count == 3: #매번 안전 영역의 크기 계산
        for i in range(n):
            for j in range(m):
                temp[i][j] = data[i][j]
        for i in range(n):
            for j in range(m):
                if temp[i][j]==2:
                    virus(i,j)
        #안전 영역의 최댓값 계산
        result=max(result,get_score())
        return

    for i in range(n): #매번 DFS를 이용해 울타리 설치
        for j in range(m):
            if data[i][j]==0:
                data[i][j]=1
                count+=1
                dfs(count)
                data[i][j]=0
                count-=1
dfs(0)
print(result)