struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator < (const Point& a) const {
        return x < a.x || (x == a.x && y < a.y);
    }
};

typedef Point Vector;

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}

double Length(Vector A) {
    return sqrt(Dot(A, A));
}

double Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

struct Line {
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(Point p, Vector v):p(p), v(v) {
        ang = atan2(v.y, v.x);
    }
    bool operator < (const Line& l) const {
        return ang < l.ang;
    }
};

Vector Normal(Vector A) {
    double l = Length(A);
    return Vector(-A.y / l, A.x / l);
}

Vector operator+ (Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator- (Point A, Point B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator* (Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}

Vector operator/ (Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}

int Dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    else return x < 0 ? -1 : 1;
}

bool OnLeft(Line l, Point p) {
    return Cross(l.v, p - l.p) > 0;
}

Point GetIntersection(Line a, Line b) {
    Vector u = a.p - b.p;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.p + a.v * t;
}

int HalfplaneIntersection(Line* l, int n, Point* poly) {
    sort(l, l + n);
    int head, tail;
    Point* p = new Point[n];
    Line* q = new Line[n];
    q[head = tail = 0] = l[0];
    rep(i, 1, n) {
        while (head < tail && !OnLeft(l[i], p[tail - 1])) tail--;
        while (head < tail && !OnLeft(l[i], p[head])) head++;
        q[++tail] = l[i];
        if (fabs(Cross(q[tail].v, q[tail - 1].v)) < EPS) {
            tail--;
            if (OnLeft(q[tail], l[i].p)) q[tail] = l[i];
        }
        if (head < tail) p[tail - 1] = GetIntersection(q[tail - 1], q[tail]);
    }
    while (head < tail && !OnLeft(q[head], p[tail - 1])) tail--;
    if (tail - head <= 1) return 0;
    p[tail] = GetIntersection(q[tail], q[head]);
    int m = 0;
    rep(i, head, tail + 1) poly[m++] = p[i];
    return m;
}
