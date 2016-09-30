/*
平方剩余：
假设p是素数，a是整数。 如果存在一个整数x使得x^2≡a(mod p) （即x^2-a可以被p整除）， 那么就称a在p的剩余类中是平方剩余的。
根据欧拉定理，如果p是奇素数，则a平方剩余当且仅当 a^{(p-1)/2}≡1 (mod p).
在{1,2,...,p-1}中恰好有（p-1）/2 个数是平方剩余的。
例题：POJ 1808
*/

#include<stdio.h>
#define LL long long

LL pow_mod(LL a, LL n, LL mod) {
    LL res = 1;
    while(n) {
        if (n & 1) res = res * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return res;
}

LL modsqr(LL a, LL n){
    LL b,k,i,x;
    a = (a % n + n) % n;
    if(pow_mod(a, (n-1) / 2, n) == 1){
        return 1;
    }
    return -1;
}

int main ()
{
    int T,cas=1;
    scanf("%d",&T);
    while(T--)
    {
        LL a,b;
        scanf("%I64d%I64d",&a,&b);
        printf("Scenario #%d:\n%I64d\n\n",cas++,modsqr(a,b));
    }
}
