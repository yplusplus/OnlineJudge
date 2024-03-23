#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define maxn 505
int n,k;
bool maz[maxn][maxn],visit[maxn];
int match[maxn];
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
	{
		if(maz[u][v]&&!visit[v])
		{
			visit[v]=1;
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
	int i,u,v;
	scanf("%d%d",&n,&k);
	memset(maz,false,sizeof(maz));
	for(i=0;i<k;i++)
	{
		scanf("%d%d",&u,&v);
		maz[u][v]=1;
	}
	printf("%d\n",Match());
	return 0;
}
