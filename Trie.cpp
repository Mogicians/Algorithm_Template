const int SIZE = 26;
struct Trie {
	int next[MAX_N][SIZE];
	int sz, val[MAX_N];
    
    void init() { sz = 1; clr(next[0], 0); }
	Trie() { init(); }
	int idx(char c) { return c - 'a'; }
	
	void insert(char* s, int v = 1) {
	    int cur = 0;
	    while(*s) {
	    	int id = idx(*s++);
	    	if (!next[cur][id]) {
	    		clr(next[sz], 0);
	    		val[sz] = 0;
	    		next[cur][id] = sz++;
			}
			cur = next[cur][id];
		}
		val[cur] = v;
	}
	
	bool search(char* s) {
		int cur = 0;
		while(*s) {
			int id = idx(*s++);
			if (!next[cur][id]) return false;
			cur = next[cur][id];
		}
		return val[cur];
	}     
} tire;
