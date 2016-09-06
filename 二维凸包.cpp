struct TPoint {
    double x, y;
    TPoint(){}
    TPoint(const double &_x, const double &_y):x(_x), y(_y) {}
};

TPoint p[N], hull[N];

TPoint operator-(const TPoint & a, const TPoint b) { 
    return TPoint(a.x - b.x, a.y - b.y); 
}

double cross(const TPoint & a, const TPoint & b, const TPoint & c) { 
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x); 
}

double len(const TPoint & a) { 
    return sqrt((double)(a.x * a.x+a.y * a.y)); 
}

double dis(const TPoint & a, const TPoint & b) { 
    return len(b-a); 
}

bool graham_cmp(const TPoint &b, const TPoint &c) {
    double tmp = cross(b, c, p[0]);
    if(tmp > EPS) return true;
    if(fabs(tmp) < EPS && (dis(b, p[0]) < dis(c, p[0]))) return true;
    return false;
}

int graham_scan(TPoint hull[], int n) {
    int top, i, k = 0;
    for(i = 1;i < n;++i)
    if((p[k].y-p[i].y>EPS)||(fabs(p[i].y-p[k].y)<EPS&&p[k].x-p[i].x>EPS )) k = i;
    swap(p[0], p[k]);
    sort(p+1, p + n, graham_cmp);
    hull[0] = p[0], hull[1] = p[1], hull[2] = p[2];
    if(n < 3) return n; else top = 3;
    for(i = 3;i < n;++ i) {
        while(top >= 2 && cross(hull[top-2], hull[top-1], p[i]) < EPS) --top;
        hull[top++] = p[i];
    }
    return top;
}
 
