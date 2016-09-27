struct AhoCorasick {

    int next[N][26], fail[N], end[N], vis[N];
    int root, sz;

    int newnode() {
        clr(next[sz], -1);
        end[sz] = 0;
        return sz++;
    }

    void init() {
        sz = 0;
        clr(vis, 0);
        root = newnode();
    }

    int idx(char c) { return c - 'a'; }

    void insert(char* s) {
        int now = root;
        while (*s) {
            int id = idx(*s++);
            if (next[now][id] == -1)
                next[now][id] = newnode();
            now = next[now][id];
        }
        end[now]++;
    }

    void build() {
        queue<int> Q;
        fail[root] = root;
        rep(i, 0, 26) {
            if (next[root][i] != -1) {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            } else next[root][i] = root;
        }
        while(!Q.empty()) {
            int now = Q.front(); Q.pop();
            rep(i, 0, 26) {
                if (next[now][i] != -1) {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                } else next[now][i] = next[fail[now]][i];
            }
        }
    }

    int query(char* s){
        int now = root;
        int res = 0;
        while (*s) {
            int id = idx(*s++);
            now = next[now][id];
            int temp = now;
            while(temp != root && !vis[temp]) {
                res += end[temp];
                end[temp] = 0;
                vis[temp] = 1;
                temp = fail[temp];
            }
        }
        return res;
    }
} ac;
