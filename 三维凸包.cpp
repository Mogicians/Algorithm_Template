//三维点
struct Point {
    double x, y, z;
    Point() {}
    Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    Point operator - (const Point p1) {
        return Point(x - p1.x, y - p1.y, z - p1.z);
    }
    Point operator * (Point p) {
        return Point(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);    //叉乘
    }
    double operator ^ (Point p) {
        return x*p.x+y*p.y+z*p.z;    //点乘
    }
};

struct _3DCH {
    struct fac {
        int a, b, c;    //表示凸包一个面上三个点的编号
        bool ok;        //表示该面是否属于最终凸包中的面
    };
    int n;    //初始点数
    Point P[N];    //初始点
    int cnt;    //凸包表面的三角形数
    fac F[N*8]; //凸包表面的三角形
    int to[N][N];
    double vlen(Point a) {
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);    //向量长度
    }
    double area(Point a, Point b, Point c) {
        return vlen((b-a)*(c-a));    //三角形面积*2
    }
    double volume(Point a, Point b, Point c, Point d) {
        return (b-a)*(c-a)^(d-a);    //四面体有向体积*6
    }
    //正：点在面同向
    double Pointof(Point &p, fac &f) {
        Point m = P[f.b]-P[f.a], n = P[f.c]-P[f.a], t = p-P[f.a];
        return (m * n) ^ t;
    }
    void deal(int p, int a, int b) {
        int f = to[a][b];
        fac add;
        if (F[f].ok) {
            if (Pointof(P[p], F[f]) > EPS) dfs(p, f);
            else {
                add.a = b, add.b = a, add.c = p, add.ok = 1;
                to[p][b] = to[a][p] = to[b][a] = cnt;
                F[cnt++] = add;
            }
        }
    }
    void dfs(int p, int cur) {
        F[cur].ok = 0;
        deal(p, F[cur].b, F[cur].a);
        deal(p, F[cur].c, F[cur].b);
        deal(p, F[cur].a, F[cur].c);
    }
    bool same(int s, int t) {
        Point &a = P[F[s].a], &b = P[F[s].b], &c = P[F[s].c];
        return fabs(volume(a, b, c, P[F[t].a])) < EPS && fabs(volume(a, b, c, P[F[t].b])) < EPS && fabs(volume(a, b, c, P[F[t].c])) < EPS;
    }
    //构建三维凸包
    void construct() {
        cnt = 0;
        if (n < 4) return;
        /*********此段是为了保证前四个点不公面，若已保证，可去掉********/
        bool sb = 1;
        //使前两点不公点
        rep(i, 1, n) {
            if (vlen(P[0] - P[i]) > EPS) {
                swap(P[1], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb)return;

        sb = 1;
        //使前三点不公线
        rep(i, 2, n) {
            if (vlen((P[0] - P[1]) * (P[1] - P[i])) > EPS) {
                swap(P[2], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb) return;
        sb = 1;
        //使前四点不共面
        rep(i, 3, n) {
            if (fabs((P[0] - P[1]) * (P[1] - P[2]) ^ (P[0] - P[i])) > EPS) {
                swap(P[3], P[i]);
                sb = 0;
                break;
            }
        }
        if (sb) return;
        /*********此段是为了保证前四个点不公面********/
        fac add;
        rep(i, 0, 4) {
            add.a = (i+1)%4, add.b = (i+2)%4, add.c = (i+3)%4, add.ok = 1;
            if (Pointof(P[i], add) > 0) swap(add.b, add.c);
            to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
            F[cnt++] = add;
        }

        rep(i, 4, n) rep(j, 0, cnt) {
            if (F[j].ok && Pointof(P[i], F[j]) > EPS) {
                dfs(i, j);
                break;
            }
        }
        int tmp = cnt;
        cnt = 0;
        rep(i, 0, tmp) if (F[i].ok) F[cnt++] = F[i];
    }
    //表面积
    double area() {
        double ret = 0.0;
        rep(i, 0, cnt) {
            ret += area(P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return ret / 2.0;
    }
    //体积
    double volume() {
        Point O(0, 0, 0);
        double ret = 0.0;
        rep(i, 0, cnt) {
            ret += volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
        }
        return fabs(ret / 6.0);
    }
    //表面三角形数
    int facetCnt_tri() {
        return cnt;
    }
    //表面多边形数
    int facetCnt() {
        int ans = 0;
        rep(i, 0, cnt) {
            bool nb = 1;
            rep(j, 0, i) {
                if (same(i, j)) {
                    nb = 0;
                    break;
                }
            }
            ans += nb;
        }
        return ans;
    }
};
