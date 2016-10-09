/*********************** Template ***********************/
int par[V], son[V], sz[V], depth[V], top[V], id[V], tot;

void dfs1(int u, int fa) { // init: depth[rt] = tot = 0
	par[u] = fa; son[u] = -1; sz[u] = 1;
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == fa) continue;
		depth[v] = depth[u] + 1;
		dfs1(v, u);
		sz[u] += sz[v];
		if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
	}
}

void dfs2(int u, int rt) {
	top[u] = rt; id[u] = ++tot;
	if (~son[u]) dfs2(son[u], rt);
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == par[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
/********************************************************/

// sample
void solve(int u, int v) { // u <-> v
	while (top[u] != top[v]) {
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
    		update_or_query(id[top[u]], id[u]);
    		u = par[top[u]];
    	}
    	if (depth[u] > depth[v]) swap(u, v);
    	update_or_query(id[u], id[v]);
}
