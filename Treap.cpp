#include <cstdio>
#include <cstdlib> // rand()
const int N = 1000005;

struct Treap {
    int l, r, v, s, rnd, w;
    // l = lson, r = rson, v = value
    // s = size, rnd = 随机因子
    // w = 同一个数的个数
} tr[N];

int n, siz, root, x;

void update (int k) {
    tr[k].s = tr[tr[k].l].s + tr[tr[k].r].s + tr[k].w;
}

void L_Rotate (int &k) {
    int t = tr[k].r;
    tr[k].r = tr[t].l;
    tr[t].l = k;
    tr[t].s = tr[k].s;
    update(k);
    k = t;
}

void R_Rotate (int &k) {
    int t = tr[k].l;
    tr[k].l = tr[t].r;
    tr[t].r = k;
    tr[t].s = tr[k].s;
    update(k);
    k = t;
}

void insert (int &k,int x) {
    if(k == 0) {
        siz++;
        k = siz;
        tr[k].v = x;
        tr[k].rnd = rand();
        tr[k].s = tr[k].w = 1;
        return ;
    }
    tr[k].s++;
    if (x == tr[k].v) tr[k].w++;
    else if(x > tr[k].v) {
        insert(tr[k].r, x);
        if(tr[tr[k].r].rnd < tr[k].rnd) L_Rotate(k);
    } else {
        insert(tr[k].l, x);
        if(tr[tr[k].l].rnd < tr[k].rnd) R_Rotate(k);
    }
}

void del(int &k,int x) {
    if(k == 0) return; 
    if(x == tr[k].v) {
        if(tr[k].w > 1) {
            tr[k].w--;
            tr[k].s--;
            return ;
        }
        if(tr[k].l*tr[k].r == 0) k = tr[k].l + tr[k].r;
        else if(tr[tr[k].l].rnd < tr[tr[k].r].rnd) {
            R_Rotate(k);
            del(k, x);
        } else {
            L_Rotate(k);
            del(k, x);
        }
    } else if(x > tr[k].v) {
        tr[k].s--;
        del(tr[k].r, x);
    } else {
        tr[k].s--;
        del(tr[k].l, x);
    }
}

int queryRank(int k, int x) { //查询数x的排名是多少
    if(k == 0) return 0;
    if(tr[k].v == x) return tr[tr[k].l].s + 1;
    else if(x > tr[k].v)
        return tr[tr[k].l].s + tr[k].w + queryRank(tr[k].r, x);
    else return queryRank(tr[k].l, x);
}

int queryNum (int k, int x) { //查询第x大的数是多少
    if(k == 0) return 0;
    if(x <= tr[tr[k].l].s)
        return queryNum(tr[k].l, x);
    else if(x > tr[tr[k].l].s + tr[k].w)
        return queryNum(tr[k].r, x - tr[tr[k].l].s - tr[k].w);
    else return tr[k].v;
}
