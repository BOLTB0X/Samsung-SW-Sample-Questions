n=int(input())
nums=list(map(int,input().split()))
add,sub,mul,div=map(int,input().split())

max_value=-1000000000
min_value=1000000000

def DFS(number,idx,add,sub,mul,div):
    global nums,max_value,min_value

    if n==idx: # 인덱스가 도달하면
        max_value=max(number, max_value)
        min_value=min(number, min_value)
        return
    
    else: #조건별 재귀적 함수호출
        if add > 0:
            DFS(number + nums[idx], idx + 1, add - 1, sub, mul, div)
        if sub > 0:
            DFS(number - nums[idx], idx + 1, add, sub - 1, mul, div)
        if mul > 0:
            DFS(number * nums[idx], idx + 1, add, sub , mul -1, div)
        if div > 0:
            DFS(int(number / nums[idx]), idx + 1, add, sub, mul, div -1)
DFS(nums[0],1,add,sub,mul,div)
print(max_value)
print(min_value)