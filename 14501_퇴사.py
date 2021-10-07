n = int(input())
T,P=[0 for _ in range(n+1)],[0 for _ in range(n+1)]
DP=[0 for _ in range(n+1)]

#입력
for i in range(1,n+1):
    t,p=map(int,input().split())
    T[i]=t
    P[i]=p
#거꾸로 순회
for i in range(n-1,-1,-1):
    #현재 인덱스에서 걸리는 일수를 더함
    next = i+T[i]
    #퇴사일을 넘긴다면
    if next > n:
        DP[i]=DP[i+1]
    #넘기지 않다면
    else:
        DP[i] = max(DP[i+1],DP[next]+P[i])
print(DP[0])