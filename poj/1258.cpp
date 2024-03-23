#include<cstdio>
#include<cstring>
#define M 105
const int INF=99999999;
int g[M][M];
int n;
bool visit[M];
int lowcost[M];
__int64 ans;
void prim(int s)
{
	int i,j,u;
	for(i=0;i<n;i++)
		lowcost[i]=g[s][i];
	visit[s]=1;
	for(i=1;i<n;i++)
	{
		int min=INF;
		for(j=0;j<n;j++)
			if(!visit[j]&&lowcost[j]<min)
			{
				min=lowcost[j];
				u=j;
			}
		visit[u]=true;
		for(j=0;j<n;j++)
			if(!visit[j]&&g[u][j]<lowcost[j])
				lowcost[j]=g[u][j];
	}
}

int main()
{
	int i,j;
	while(scanf("%d",&n)!=EOF)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				scanf("%d",&g[i][j]);
		memset(visit,false,sizeof(visit));
		prim(0);
		for(ans=i=0;i<n;i++)
			ans+=lowcost[i];
		printf("%I64d\n",ans);
	}
	return 0;
}
