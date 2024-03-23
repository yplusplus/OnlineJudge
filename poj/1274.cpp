#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define max 205
bool maz[max][max],visit[max];
int match[max];
int n,m;

bool dfs(int u)
{
	for(int v=1;v<=m;v++)
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
		memset(visit,false,sizeof(visit));
		if(dfs(u))
			cnt++;
	}
	return cnt;
}

int main()
{
	int i,j,u,v;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(maz,0,sizeof(maz));
		for(u=1;u<=n;u++)
		{
			scanf("%d",&i);
			for(j=0;j<i;j++)
			{
				scanf("%d",&v);
				maz[u][v]=1;
			}
		}
		printf("%d\n",Match());
	}
	return 0;
}