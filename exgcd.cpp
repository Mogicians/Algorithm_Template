//2.��չŷ������㷨
// ���� d = gcd(a, b)�������ax+by=gcd(a,b)�Ľ�(x,y)
// �ݹ��
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