/*****************************************************
 * 扩展欧几里德算法
 *****************************************************/
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

// 非递归版
int extgcd(int a, int b, int &x, int &y) {
	int x0 = 0, y0 = 1, x1 = 1, y1 = 0, q = 0, r = b;
	b = a;
	do {
		x = x0 - q * x1; y = y0 - q * y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		a = b; b = r;
		r = a % b;
		q = (a - r) / b;
	} while (r);
	return b;
}
