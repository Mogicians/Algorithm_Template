/************************************************************************
 * 有向图强连通分量的Tarjan算法
 ************************************************************************/
int DFN[V], LOW[V], Belong[V], Sta[V], Stop, Bcnt, Dindex;
bool instack[V];
// DFN[v]: 结点v的DFS序编号
// LOW[V]: 结点v往前能到达的最远结点的DFS序编号
void Tarjan(int u) {
	DFN[u] = LOW[u] = ++Dindex;
	instack[u] = true;
	Sta[Stop++] = u;
	for (int i = eglist[u]; i; i = egs[i].next_eg) {
		int v = egs[i].to;
		if (!DFN[v]) {
			Tarjan(v);
			LOW[u] = min(LOW[u], LOW[v]);
		} else if (instack[v]) LOW[u] = min(LOW[u], DFN[v]);
	}
	if (DFN[u] == LOW[u]) {
		++Bcnt;
		int v;
		do {
			v = Sta[--Stop];
			instack[v] = false;
			Belong[v] = Bcnt;
		} while (v != u);
	}
}

void solve() {
	Stop = Bcnt = Dindex = 0;
	memset(DFN, 0, sizeof(DFN));
	memset(instack, 0, sizeof(instack));
	for (int i = 1; i <= V; ++i)
		if (!DFN[i]) Tarjan(i);
}