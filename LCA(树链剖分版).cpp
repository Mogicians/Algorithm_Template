/***************************** LCA 树链剖分版 *****************************/
int par[V], son[V], sz[V], depth[V], top[V], tot;

void dfs1(int u, int fa) {
	par[u] = fa; son[u] = -1; sz[u] = 1;
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == fa) continue;
		depth[v] = depth[u] + 1;
		dfs1(v, u);
		sz[u] += sz[v];
		if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
	}
}

void dfs2(int u, int rt) {
	top[u] = rt;
	if (~son[u]) dfs2(son[u], rt);
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == par[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}

int LCA(int u, int v) {
	for (; top[u] != top[v]; u = par[top[u]])
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
	return depth[u] < depth[v] ? u : v;
}
/*************************************************************************/
