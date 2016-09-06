
/*
HINT：
(1) 待排序数组长度为n, 放在s[0..n-1]中, 并令s[n] = 0
(2) sa数组有效下标为：      1..n
(3) _rank数组有效下标为:    0..n-1
(4) height数组有效下标为：  2..n
(5) height[i] = lcp(sa[i], sa[i-1])
(6) s数组中的元素都大于0, 且最大值不超过 m
(7) 调用build_sa函数时, 记得传入 n + 1
*/

char s[N];
int sa[N], t[N], t2[N], c[N];
int _rank[N], height[N];

struct suffixArray {
    bool cmp(int* r, int a, int b, int k) {
        return r[a] == r[b] && r[a + k] == r[b + k];
    }

    void build(char*s, int n, int m = 256) {
        int *x = t, *y = t2, p = 0;
        rep(i, 0, m) c[i] = 0;
        rep(i, 0, n) c[x[i] = s[i]]++;
        rep(i, 1, m) c[i] += c[i-1];
        per(i, n-1, 0) sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1, m = p, p = 0) {
            rep(i, n-k, n) y[p++] = i;
            rep(i, 0, n) if (sa[i] >= k) y[p++] = sa[i] - k;
            rep(i, 0, m) c[i] = 0;
            rep(i, 0, n) c[x[y[i]]]++;
            rep(i, 1, m) c[i] += c[i-1];
            per(i, n-1, 0) sa[--c[x[y[i]]]] = y[i];
            swap(x, y); p = 1; x[sa[0]] = 0;
            rep(i, 1, n) x[sa[i]] = cmp(y, sa[i], sa[i-1], k) ? p-1: p++;
            if (p >= n) break;
        }
    }

    void getHeight(int n) {
        rep(i, 0, n) _rank[sa[i]] = i;
        int k = 0;
        rep(i, 0, n) {
            if (k) k--;
            int j = sa[_rank[i]-1];
            while (s[i+k] == s[j+k]) k++;
            height[_rank[i]] = k;
        }
    }
}
 
