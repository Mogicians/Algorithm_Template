#include<bits/stdc++.h>
using namespace std;

#define inf (0x3f3f3f3f)
#define maxn 1000
#define maxm 1000

template<class T>
struct isap
{
	isap(){memset(N,0,sizeof(N));cnt=2;maxflow=0;};
	isap(int _s,int _t):s(_s),t(_t),d(_t+1){memset(N,0,sizeof(N));cnt=2;maxflow=0;}
	int cnt,s,t,d,N[maxn],now[maxn],dpth[maxn],vtn[maxn];
	bool found;T maxflow,tflow;
	struct edge
	{
		edge(){};
		edge(int v,int n,T c):vt(v),ne(n),cap(c){};
		int vt,ne;T cap;
	}E[maxm];
	void build(int u,int v,T c)
	{E[cnt]=edge(v,N[u],c);now[u]=N[u]=cnt++;
	E[cnt]=edge(u,N[v],0);now[v]=N[v]=cnt++;}
	void sap(int u)
	{
		int v,e;T ct;
		if(u==t){found=true;maxflow+=tflow;return;}
		for(e=now[u],ct=tflow,v=E[e].vt;e;e=E[e].ne,v=E[e].vt,tflow=ct)if(E[e].cap&&dpth[v]+1==dpth[u])
		{now[u]=e;tflow=min(tflow,E[e].cap);sap(v);if(dpth[s]==d)return;if(found)break;}
		if(found){E[e].cap-=tflow;E[e^1].cap+=tflow;}
		else
		{
			if(--vtn[dpth[u]]==0){dpth[s]=d;return;}
			now[u]=N[u];v=d-1;
			for(e=N[u];e;e=E[e].ne)if(E[e].cap&&dpth[E[e].vt]<v){v=dpth[E[e].vt];now[u]=e;}
			dpth[u]=v+1;++vtn[dpth[u]];
		}
	}
	T flow()
	{	
		int u,v,e;queue<int> q;
		memset(dpth,0,sizeof(dpth));memset(vtn,0,sizeof(vtn));vtn[0]=1;q.push(t);
		while(!q.empty())
		{
			u=q.front();q.pop();
			for(e=N[u],v=E[e].vt;e;e=E[e].ne,v=E[e].vt)
			if(v!=t&&!dpth[v]){dpth[v]=dpth[u]+1;++vtn[dpth[v]];q.push(v);}
		}
		while(dpth[s]<d)
		{tflow=inf;found=false;sap(s);}
		return maxflow;
	}
};

int main(){}
