void add(ll* sum, int l, int r, int v) {
    sum[l] = (sum[l] + v) % MOD;
    sum[r+1] = (sum[r+1] - v + MOD) % MOD;
}

void update(ll* sum, int n) {
    rep(i, 1, n) sum[i] = (sum[i] + sum[i-1]) % MOD; // 更新
    rep(i, 1, n) sum[i] = (sum[i] + sum[i-1]) % MOD; // 前缀和
}

ll query(ll* sum, int l, int r) {
    return (sum[r] - sum[l-1] + MOD) % MOD;
}