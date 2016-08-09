#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
typedef __int64 ll;

ll fac[maxn],rfac[maxn],inv[maxn];

ll fpow(ll b,ll p,ll m)
{
	ll r=1;
	while(p)
	{
		if(p&1)r=r*b%m;
		b=b*b%m;
		p=p/2;
	}
	return r;
}

void init(ll p)
{
	fac[0]=fac[1]=1;
	for(int i=2;i<p;++i)
		fac[i]=fac[i-1]*i%p;
	inv[p-1]=fpow(fac[p-1],p-2,p);
	for(int i=p-2;i>=0;--i)
		inv[i]=inv[i+1]*(i+1)%p;
}

ll c(ll n,ll m,ll p)
{
	if(n<0||m<0||n<m)return 0;
	return fac[n]*inv[m]*inv[n-m]%p;
}

ll lucas(ll n,ll m,ll p)
{
	if(n<0||m<0||n<m)return 0;
	ll ans=1;
	while(n||m)
	{
		ans=ans*c(n%p,m%p,p)%p;
		n/=p;
		m/=p;
	}
	return ans;
}

int main()
{
	ll n,m,p;
	init(p);
	cin>>n>>m>>p;
	cout<<lucas(n,m,p)<<endl;
}
