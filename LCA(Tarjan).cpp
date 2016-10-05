const int V = 1024, Q = 500010; 
int eglist[V], egsz;
int qlist[Q], qsz;
int par[V], ances[Q];

struct Edge {
	int to, nexteg;
} egs[V];

void AddEdge(int u, int v) {
	egs[++egsz].to = v;
	egs[egsz].nexteg = eglist[u];
	eglist[u] = egsz;
}

struct Query {
	int to, qID, nextq;
} qs[Q << 1];   // 注意询问得开两倍空间

void AddQuery(int u, int v, int qid) {
	qs[++qsz].to = v;
	qs[qsz].qID = qid;
	qs[qsz].nextq = qlist[u];
	qlist[u] = qsz;
}

/***************************LCA Tarjan 离线算法***************************/

int find(int x) {
	return par[x] == x ? x : par[x] = find(par[x]);
}

void TarjanLCA(int u) {
	for (int i = qlist[u]; i; i = qs[i].nextq) {
		int v = qs[i].to, qid = qs[i].qID;;
        	if (vis[v]) ances[qid] = find(v);
    	}
    	par[u] = u;
    	vis[u] = true;
    	for (int i = eglist[u]; i; i = egs[i].nexteg) {
        	int v = egs[i].to;
        	if (!vis[v]) {
            		TarjanLCA(v);
	            par[v] = u;
        	}
    	}
}

/************************************************************************/

void solve () {
	int q;    // 询问数目
	scanf("%d", &q);
	for (int u, v, i = 0; i < q; ++i) {
		scanf("%d %d", &u, &v);   // 询问u和v的最近公共祖先
		AddQuery(u, v, i); AddQuery(v, u, i);   // 必须将(u,v)和(v,u)都加以存储，所以qs[]数组得开两倍QuerySize的空间
	}
	TarjanLCA(rt);    // rt为根结点
  	// 操作完后ances[i]即为第i个询问的答案
}
