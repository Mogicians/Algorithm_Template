bool IsPrime[N];
int prime[N >> 1], tot = 0;
memset(IsPrime,true,sizeof(IsPrime));
for (int i = 2; i <= N; i++) {
    if (IsPrime[i]) prime[tot++] = i;
    for (int j = 0; j < tot; j++) {
        if (i * prime[j] > N) break;//超过最大范围，跳出 
        IsPrime[i * prime[j]] = false;//将倍数筛除 
        if (i % prime[j] == 0) break;//保证只筛到以prime[j]为最小质因数的数 
    }
}