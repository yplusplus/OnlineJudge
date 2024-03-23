#include<cstdio>
#include<cstring>
#define M 505
#define max(a,b) a>b?a:b
const int INF=99999999;
int n;
int ans;
int g[M][M];
int lowcost[M];
bool visit[M];
void prim(int s)
{
	int i,j,u;
	for(i=0;i<n;i++)
	{
		lowcost[i]=g[s][i];
		visit[i]=0;
	}
	visit[s]=1;
	for(ans=0,i=1;i<n;i++)
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
		ans=max(ans,lowcost[u]);
		for(j=0;j<n;j++)
			if(!visit[j]&&g[u][j]<lowcost[j])
				lowcost[j]=g[u][j];
	}
}
int main()
{
	int T,i,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				scanf("%d",&g[i][j]);
		prim(0);			
		printf("%d\n",ans);
	}
	return 0;
}