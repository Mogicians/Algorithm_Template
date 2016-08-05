int sg[105];

int getSG(int x) {
    if (sg[x] >= 0) return sg[x];
    set<int> s;
    // 转移到[0, x) 任意一种情况
    rep(i, 0, x) s.insert(getSG(i));
    // 分成三堆的情况
    rep(i, 1, x) rep(j, 1, x) rep(k, 1, x) {
        if (i + j + k == x) s.insert(getSG(i) ^ getSG(j) ^ getSG(k));
    }
    int i; for (i = 0; s.count(i); ++i);
    sg[x] = i;
    return sg[x];
}

void solve() {
    clr(sg, -1);
    rep(i, 1, 100) printf("sg[%d] = %d\n", i, getSG(i));
}