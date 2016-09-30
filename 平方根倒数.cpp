/*
平方根倒数速算法
https://zh.wikipedia.org/wiki/%E5%B9%B3%E6%96%B9%E6%A0%B9%E5%80%92%E6%95%B0%E9%80%9F%E7%AE%97%E6%B3%95
double情况：
0x5fe6eb50c7aa19f9
float -> double 
long -> long long
*/

float Q_rsqrt(float number) { // 平方根倒数
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    const int T = 10;              // 迭代次数
    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;          // evil floating point bit level hacking（对浮点数的邪恶位元hack）
    i  = 0x5f37642f - ( i >> 1 );  // what the fuck?（这他妈的是怎么回事？）
    y  = * ( float * ) &i;
    for (int i = 0; i < T; ++i)
        y  = y * ( threehalfs - ( x2 * y * y ) );  
    return y;
}
