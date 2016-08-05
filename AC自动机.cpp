const int SIZE = 26;

struct AhoCorasick {
	int next[MAX_N][SIZE];
	int sz, val[MAX_N], fail[MAX_N], last[MAX_N];
    
	void init() { sz = 1; clr(next[0], 0); }
	int idx(char c) { return c - 'a'; }
	int newnode() { clr(next[sz], 0); val[sz] = 0; return sz++; }
	
	void insert(char* s, int v = 1) {
	    int cur = 0;
	    while(*s) {
	    	int id = idx(*s++);
	    	if (!next[cur][id]) next[cur][id] = newnode();
			cur = next[cur][id];
		}
		val[cur] = v;
	}
	
	void getfail() {
		queue<int> q;
		fail[0] = 0;
		rep(c, 0, SIZE) {
			int u = next[0][c];
			if (u) { fail[u] = 0; q.push(u); last[u] = 0; }
		}
		while (!q.empty()) {
			int r = q.front(); q.pop();
			rep(c, 0, SIZE) {
				int u = next[r][c];
				if (!u) {
					next[r][c] = next[fail[r]][c]; //建成Trie图
					continue;
				}
				q.push(u);
				int v = fail[r];
				while (v && !next[v][c]) v = fail[v];
				fail[u] = next[v][c];
				last[u] = (val[fail[u]] ? fail[u] : last[fail[u]]);
			}
		}
	}
	
	void find(char* T) {
		int j = 0;
		while(*T) {
			int c = idx(*T++);
			j = next[j][c];
			if (val[j]) out(j);
			else if (last[j]) out(last[j]);
		}
	}
	
	void out(int i) {
		if (i) {
			cnt++;
			out(last[i]);
		}
	}   
} AC;
