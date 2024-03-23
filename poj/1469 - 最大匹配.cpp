#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define maxn 305
#define maxp 305
bool maz[maxp][maxn],visit[maxp];
int match[maxp];
int p,n;
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
		if(maz[u][v]&&!visit[v])
		{
			visit[v]=true;
			if(match[v]==-1||dfs(match[v]))
			{
				match[v]=u;
				return true;
			}
		}
	return false;
}

int Match()
{
	int cnt=0;
	memset(match,-1,sizeof(match));
	for(int u=1;u<=p;u++)
	{
		memset(visit,0,sizeof(visit));
		if(dfs(u))
			cnt++;
	}
	return cnt;
}

int main()
{
	int i,j,t,u,v;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&p,&n);
		memset(maz,0,sizeof(maz));
		for(u=1;u<=p;u++)
		{
			scanf("%d",&i);
			for(j=0;j<i;j++)
			{
				scanf("%d",&v);
				maz[u][v]=1;
			}
		}
		if(Match()==p)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
		