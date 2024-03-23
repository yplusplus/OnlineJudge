#include<cstdio>
#define M 30
const int INF=99999999;
int n;
int g[M][M];
bool visit[M];
int lowcost[M];

int prim(int s)
{
	int i,j,u,ans=0;
	for(i=0;i<n;i++)
		lowcost[i]=g[s][i],visit[i]=0;
	visit[s]=1;
	for(i=1;i<n;i++)
	{
		int min=INF;
		for(j=0;j<n;j++)
		{
			if(!visit[j]&&lowcost[j]<min)
			{
				min=lowcost[j];
				u=j;
			}
		}
		visit[u]=1;
		ans+=lowcost[u];
		for(j=0;j<n;j++)
			if(!visit[j]&&g[u][j]<lowcost[j])
				lowcost[j]=g[u][j];
	}
	return ans;
}

int main()
{
	char p1,p2;
	int i,j,m,dist;
	while(scanf("%d",&n)&&n)
	{
		for(i=0;i<n;i++)
			for(j=i;j<n;j++)
				g[i][j]=g[j][i]=INF;
		for(i=1;i<n;i++)
		{
			scanf(" %c %d",&p1,&m);
			p1-='A';
			for(j=0;j<m;j++)
			{
				scanf(" %c %d",&p2,&dist);
				p2-='A';
				g[p1][p2]=g[p2][p1]=dist;
			}
		}
		printf("%d\n",prim(0));
	}
	return 0;
}