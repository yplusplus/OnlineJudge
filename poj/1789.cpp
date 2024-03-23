#include<cstdio>
#include<cstring>
#define M 2005
const int INF=99999999;
int n;
int g[M][M];
int lowcost[M];
char car[M][8];
bool visit[M];

int calculate(int u,int v)
{
	int diff=0;
	for(int i=0;i<8;i++)
		if(car[u][i]!=car[v][i])
			diff++;
	return diff;
}

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
	int i,j;
	while(scanf("%d",&n)&&n)
	{
		for(i=0;i<n;i++)
			scanf("%s",car[i]);
		for(i=0;i<n;i++)
			for(j=i;j<n;j++)
				g[i][j]=g[j][i]=calculate(i,j);
		printf("The highest possible quality is 1/%d.\n",prim(0));
	}
	return 0;
}
