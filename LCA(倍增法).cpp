/************************** LCA 倍增法 在线算法 **************************/
// depth[u]： 结点u的深度
// par[u][i]：结点u往上走第2^j个结点

void DFS(int u) { // 从根结点rt开始DFS，depth[rt]初始化为0
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == par[u][0]) continue;
		depth[v] = depth[u] + 1;
		par[v][0] = u;
		for (int j = 1; j < MAX_DEPTH; ++j) par[v][j] = par[par[v][j - 1]][j - 1];
		DFS(v);
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (int dis = depth[u] - depth[v], i = 0; dis; dis >>= 1, ++i)
		if (dis & 1) u = par[u][i];
	if (u == v) return u;
	for (int i = MAX_DEPTH - 1; i >= 0; --i) {
		if (par[u][i] == par[v][i]) continue;
		u = par[u][i], v = par[v][i];
	}
	return par[u][0];
}
