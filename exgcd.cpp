//2.扩展欧几里德算法
// 返回 d = gcd(a, b)，并解出ax+by=gcd(a,b)的解(x,y)
// 递归版
int extgcd(int a, int b, int &x, int &y) {
    int d = a;
    if (b) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}