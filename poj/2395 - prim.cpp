#include<cstdio>
#define M 2005
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
const int INF=999999999;
int n,m;
int g[M][M];
int lowcost[M];
bool visit[M];

int prim(int s)
{
	int i,j,ans=0;
	for(i=1;i<=n;i++)
		lowcost[i]=g[s][i],visit[i]=0;
	visit[s]=1;
	for(i=1;i<n;i++)
	{
		int min=INF,u=-1;
		for(j=1;j<=n;j++)
			if(!visit[j]&&lowcost[j]<min)
				min=lowcost[j],u=j;
		visit[u]=1;
		ans=max(ans,lowcost[u]);
		for(j=1;j<=n;j++)
			if(!visit[j]&&lowcost[j]>g[u][j])
				lowcost[j]=g[u][j];
	}
	return ans;
}
	
int main()
{
	int i,j,k,dist;
	scanf("%d%d",&n,&m);
	for(i=0;i<M;i++)
		for(j=0;j<M;j++)
			g[i][j]=INF;
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d",&j,&k,&dist);
		g[j][k]=g[k][j]=min(g[k][j],dist);
	}
	printf("%d\n",prim(1));
	return 0;
}