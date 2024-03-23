#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define M 500
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
int n;
double g[M][M];
double coord[M][2];
double lowcost[M];
int closed[M];
const double INF=99999999;
bool visit[M];

double calculate(int i,int j)
{
	double a=coord[i][0]-coord[j][0];
	double b=coord[i][1]-coord[j][1];
	return sqrt(a*a+b*b);
}

void prim(int s)
{
	int i,j,u;
	for(i=1;i<=n;i++)
	{
		lowcost[i]=g[s][i];
		closed[i]=s;
	}
	visit[s]=1;
	for(i=2;i<=n;i++)
	{
		double min=INF;
		for(j=1;j<=n;j++)
			if(!visit[j]&&lowcost[j]<min)
			{
				min=lowcost[j];
				u=j;
			}
		visit[u]=1;
		for(j=1;j<=n;j++)
			if(!visit[j]&&g[u][j]<lowcost[j])
			{
				lowcost[j]=g[u][j];
				closed[j]=u;
			}
	}
}

int main()
{
	int i,j,t=1;
	while(scanf("%d",&n)&&n)
	{
		for(i=1;i<=n;i++)
			scanf("%lf %lf",&coord[i][0],&coord[i][1]);
		for(i=1;i<=n;i++)
			for(j=i;j<=n;j++)
				g[i][j]=g[j][i]=calculate(i,j);
		memset(visit,false,sizeof(visit));
		prim(1);
		int index=2;
		double ans=0;
		while(index!=1)
		{
			ans=max(ans,lowcost[index]);
			index=closed[index];
		}
		printf("Scenario #%d\n",t++);
		printf("Frog Distance = %.3f\n\n",ans);
	}
	return 0;
}
