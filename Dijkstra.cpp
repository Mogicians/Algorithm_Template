struct Edge {
	int to, next, cost;
} e[N];

int T, S, D, top;
int head[N], dis[N];

void init() {
	top = 0;
	clr(head, -1);
}

void addedge(int u, int v, int cost) {
	e[top].to = v, e[top].cost = cost, e[top].next = head[u], head[u] = top++;
	e[top].to = u, e[top].cost = cost, e[top].next = head[v], head[v] = top++;
}

void dijkstra(int s) {
	priority_queue<PII, vector<PII>, greater<PII> > que;
	clr(dis, INF);
	dis[s] = 0;
	que.push(PII(0, s));
	while (!que.empty()) {
		PII p = que.top(); que.pop();
		int v = p.se;
		if (dis[v] < p.fi) continue;
		for (int i = head[v]; i != -1; i = e[i].next) {
			int u = e[i].to, cost = e[i].cost;
			if (dis[u] > dis[v] + cost) {
				dis[u] = dis[v] + cost;
				que.push(PII(dis[u], u));
			}
		}
	}
}
