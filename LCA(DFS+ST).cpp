// POJ 1330 Nearest Common Ancestors
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V = 10005;
int T, n, egsz, eglist[V], euler[V << 1], tot, depth[V], pos[V], d[V << 1][20], x, y, deg[V], rt;

struct Edge {
	int from, to, nexteg;
} egs[V];

void AddEdge(int u, int v) {
	egs[++egsz].to = v;
	egs[egsz].nexteg = eglist[u];
	eglist[u] = egsz;
}

/**************************LCA在线算法 DFS+ST表**************************/

// euler[i]：欧拉路径上的第i个结点（结点个数：2 * V - 1）
// depth[u]：结点u的深度
// pos[u]：  结点u在欧拉路径上首次出现的位置

void dfs(int u, int fa) {
	for (int i = eglist[u]; i; i = egs[i].nexteg) {
		int v = egs[i].to;
		if (v == fa) continue;
		depth[v] = depth[u] + 1;
		pos[v] = tot;
		euler[tot++] = v;
		dfs(v, u);
		euler[tot++] = u;
	}
}

void RMQ_init() {
	for (int i = 0; i < tot; ++i) d[i][0] = euler[i];
	for (int j = 1; (1 << j) <= tot; ++j)
		for (int i = 0; i + (1 << j) - 1 < tot; ++i) {
			int u = d[i][j - 1], v = d[i + (1 << (j - 1))][j - 1];
			d[i][j] = depth[u] < depth[v] ? u : v;
		}
}

int RMQ(int L, int R) {
	int k = 0;
	while ((1 << (k + 1)) <= R - L + 1) ++k;
	int u = d[L][k], v = d[R - (1 << k) + 1][k];
	return depth[u] < depth[v] ? u : v;
}

int LCA(int u, int v) {
	return pos[u] < pos[v] ? RMQ(pos[u], pos[v]) : RMQ(pos[v], pos[u]);
}
/************************************************************************/

int main() {
	scanf("%d", &T);
	while (T--) {
		//--------------------------------init
		egsz = tot = 0;
		memset(eglist, 0, sizeof(eglist));
		memset(pos, -1, sizeof(pos));
		memset(deg, 0, sizeof(deg));
		//--------------------------------init
		scanf("%d", &n);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d %d", &u, &v);
			AddEdge(u, v);
			++deg[v];
		}
		for (rt = 1; deg[rt]; ++rt);
		euler[tot++] = rt; pos[rt] = 0;
		dfs(rt, -1);
		RMQ_init();
		scanf("%d %d", &x, &y);
		printf("%d\n", LCA(x, y));
	}
	return 0;
}
