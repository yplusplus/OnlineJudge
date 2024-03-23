#include<cstdio>
#include<cstdlib>
#include<cstring>
#define M 105
#define min(a,b) a<b?a:b
const int INF=99999999;
int g[M][M];
int dist[M];
int n;
int dijkstra(int s)
{
	bool visit[M];
	int i,j,k,min;
	for(i=0;i<n;i++)
	{
		dist[i]=INF;
		visit[i]=0;
	}
	dist[s]=0;
	for(i=0;i<n;i++)
	{
		min=INF;
		for(j=0;j<n;j++)
		{
			if(!visit[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		}
		visit[k]=1;
		for(j=0;j<n;j++)
			if(g[k][j]&&!visit[j])
				dist[j]=min(dist[j],dist[k]+g[k][j]);
	}
	int max=0;
	for(i=0;i<n;i++)
		if(max<dist[i])
			max=dist[i];
	return max;
}
int main()
{
	char str[5];
	int i,j;
	memset(g,0,sizeof(g));
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		for(j=0;j<i;j++)
		{
			scanf("%s",str);
			g[i][j]=g[j][i]=atoi(str);
		}
	}
	printf("%d\n",dijkstra(0));
	return 0;
}
