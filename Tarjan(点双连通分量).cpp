int n, dfn[V], low[V], bccno[V], dindex, bcnt;
bool iscut[V];
vector<int> G[V], bcc[V];
struct Edge {
	int u, v;
	Edge(){}
	Edge(int uu, int vv): u(uu), v(vv){}
};
stack<Edge> sta;

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++dindex;
	int child = 0;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		Edge e = Edge(u, v);
		if (!dfn[v]) {
			++child;
			sta.push(e);
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				iscut[u] = true; // u是割点
				bcc[++bcnt].clear();
				while (1) {
					Edge eg = sta.top(); sta.pop();
					if (bccno[eg.u] != bcnt) bcc[bcnt].push_back(eg.u), bccno[eg.u] = bcnt;
					if (bccno[eg.v] != bcnt) bcc[bcnt].push_back(eg.v), bccno[eg.v] = bcnt;
					if (eg.u == u && eg.v == v) break;
				}
			}
		} else if (dfn[v] < dfn[u] && v != fa) {
			sta.push(e);
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = false;
}

void FindBCC() {
	dindex = bcnt = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(bccno, 0, sizeof(bccno));
	memset(iscut, false, sizeof(iscut));
	for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, -1);
}
