#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 205
#define maxm 205
const int INF=2000000000;
int n,m;
int flow[maxn][maxn],cap[maxn][maxn],a[maxn],p[maxn];
int min(int a,int b)
{
	return a<b?a:b;
}

int ek(int s,int t)
{
	memset(flow,0,sizeof(flow));
	int f=0;
	queue<int> que;
	while(1)
	{
		memset(a,0,sizeof(a));
		memset(p,0,sizeof(p));
		a[s]=INF;
		que.push(s);
		while(!que.empty())
		{
			int u=que.front();
			que.pop();
			for(int v=1;v<=m;v++)
				if(!a[v]&&cap[u][v]>flow[u][v])
				{
					p[v]=u;
					que.push(v);
					a[v]=min(a[u],cap[u][v]-flow[u][v]);
				}
		}
		if(a[t]==0)
			break;
		for(int u=t;u!=s;u=p[u])
		{
			flow[p[u]][u]+=a[t];
			flow[u][p[u]]-=a[t];
		}
		f+=a[t];
	}
	return f;
}
int main()
{
	int u,v,w;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(cap,0,sizeof(cap));
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			cap[u][v]+=w;
		}
		printf("%d\n",ek(1,m));
	}
	return 0;
}