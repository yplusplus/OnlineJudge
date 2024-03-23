#include<cstdio>
#define M 105
#define min(a,b) a<b?a:b
const int INF=99999999;
int n,e;
int g[M][M];
int lowcost[M];
bool visit[M];

int prim(int s)
{
	int i,j,u,ans=0;
	for(i=1;i<=n;i++)
		lowcost[i]=g[s][i],visit[i]=0;
	visit[s]=1;
	for(i=1;i<n;i++)
	{
		int min=INF;
		for(j=1;j<=n;j++)
			if(!visit[j]&&lowcost[j]<min)
			{
				min=lowcost[j];
				u=j;
			}
		visit[u]=1;
		ans+=lowcost[u];
		for(j=1;j<=n;j++)
			if(!visit[j]&&g[u][j]<lowcost[j])
				lowcost[j]=g[u][j];
	}
	return ans;
}

int main()
{
	int i,j,p1,p2,dist;
	while(scanf("%d",&n)&&n)
	{
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				g[i][j]=INF;
		scanf("%d",&e);
		for(i=0;i<e;i++)
		{
			scanf("%d%d%d",&p1,&p2,&dist);
			g[p1][p2]=g[p2][p1]=min(g[p1][p2],dist);
		}
		printf("%d\n",prim(1));
	}
	return 0;
}