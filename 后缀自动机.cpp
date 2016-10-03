struct State {
    State *par;
    State *go[26];
    int val, minlen, right;
    int first_endpos;
    void init(int v = 0) {
        val = v;
        par = NULL;
        minlen = right = 0;
        memset(go, 0, sizeof(go));
    }
    int calc() {
        if (par == NULL) return 0;
        return val - par->val;
    }
};

int d[M];

struct SAM {

    State *root, *last, *cur, *b[N];
    State nodePool[N];

    State* newState(int val = 0) {
        cur->init(val);
        return cur++;
    }

    void init() {
        cur = nodePool;
        root = newState();
        last = root;
    }

    void insert(int w, int pos = 0) {
        State* p = last;
        State* np = newState(p->val + 1);
        np->first_endpos = pos;
        np->right = 1;
        while (p != NULL && p->go[w] == NULL) {
            p->go[w] = np;
            p = p->par;
        }
        if (p == NULL) {
            np->par = root;
        } else {
            State* q = p->go[w];
            if (p->val + 1 == q->val) {
                np->par = q;
            } else {
                State* nq = newState(p->val + 1);
                nq->first_endpos = q->first_endpos;
                memcpy(nq->go, q->go, sizeof(q->go));
                nq->par = q->par;
                q->par = nq;
                np->par = nq;
                while (p != NULL && p->go[w] == q) {
                    p->go[w] = nq;
                    p = p->par;
                }
            }
        }
        last = np;
    }

    void topo() {
        int siz = cur - nodePool;
        int maxval = 0;
        memset(d, 0, sizeof(d));
        for (int i = 1; i < siz; ++i) {
            maxval = max(maxval, nodePool[i].val);
            d[nodePool[i].val]++;
        }
        for (int i = 1; i <= maxval; ++i) d[i] += d[i - 1];
        for (int i = 1; i < siz; ++i) b[d[nodePool[i].val]--] = &nodePool[i];
        b[0] = root;
    }

    void count() {
        State* p;
        int siz = cur-nodePool;
        for (int i = siz - 1; i >= 0; --i){
            p = b[i];
            if (p->par != NULL) {
                (p->par)->right += p->right;
                p->minlen = (p->par)->val + 1;
            }
        }
    }
};
