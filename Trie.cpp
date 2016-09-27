
struct Trie {

	int next[N][26];
	int root, sz, val[N];

	int idx(char c) { return c - 'a'; }

    int newnode() {
        clr(next[sz], -1);
        val[sz] = 0;
        return sz++;
    }

    void init() {
        sz = 0;
        root = newnode();
    }

    Trie() { init(); }

	void insert(char* s, int v = 1) {
	    int now = root;
	    while(*s) {
	    	int id = idx(*s++);
	    	if (next[now][id] == -1)
	    		next[now][id] = newnode();
			now = next[now][id];
		}
		val[now] = v;
	}

	int query(char* s) {
		int now = root;
		while(*s) {
			int id = idx(*s++);
			if (next[now][id] == -1) return 0;
			now = next[now][id];
		}
		return val[now];
	}
} trie;
