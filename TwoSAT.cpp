struct TwoSAT {
	int n, sta[MAXN << 1], top;
	vector<int> G[MAXN << 1];
	bool mark[MAXN << 1];
	void init(int n) {
		this->n = n;
		for (int i = 0, bnd = n << 1; i < bnd; ++i) G[i].clear();
		memset(mark, false, sizeof(mark));
	}
	void add_clause(int x, int xval, int y, int yval) {
		x = x << 1 | xval, y = y << 1 | yval;
		G[x ^ 1].push_back(y), G[y ^ 1].push_back(x);
	}
	bool dfs(int x) {
		if (mark[x ^ 1]) return false;
		if (mark[x]) return true;
		mark[x] = true;
		sta[top++] = x;
		for (int i = 0; i < G[x].size(); ++i)
			if (!dfs(G[x][i])) return false;
		return true;
	}
	bool solve() {
		for (int i = 0, bnd = n << 1; i < bnd; i += 2)
			if (!mark[i] && !mark[i | 1]) {
				top = 0;
				if (!dfs(i)) {
					while (top) mark[sta[--top]] = false;
					if (!dfs(i | 1)) return false;
				}
			}
		return true;
	}
};
