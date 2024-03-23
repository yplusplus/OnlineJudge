#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define maxn 125
int n,m;
bool maz[maxn][maxn],visit[maxn];
int match[maxn];
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
	{
		if(maz[u][v]&&!visit[v])
		{
			visit[v]=true;
			if(match[v]==-1||dfs(match[v]))
			{
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}

int Match()
{
	int cnt=0;
	memset(match,-1,sizeof(match));
	for(int u=1;u<=n;u++)
	{
		memset(visit,0,sizeof(visit));
		if(dfs(u))
			cnt++;
	}
	return cnt;
}

int main()
{
	int i,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		memset(maz,0,sizeof(maz));
		for(i=0;i<m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			maz[u][v]=1;
		}
		printf("%d\n",n-Match());
	}
	return 0;
}
