#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1005
#define min(a,b) a<b?a:b
const int INF=99999999;
using namespace std;

int n,m;
int dist[maxn];
int maz[maxn][maxn];
bool visit[maxn];
void dijkstra(int s)
{
    int i,j;
    for(i=1;i<=n;i++)
        dist[i]=INF,visit[i]=0;
    dist[s]=0;
    for(i=1;i<=n;i++)
    {
        int min=INF,u=0;
        for(j=1;j<=n;j++)
            if(!visit[j]&&min>dist[j])
            {
                min=dist[j];
                u=j;
            }
        if(u==0)
            break;
        visit[u]=1;
        for(j=1;j<=n;j++)
            if(!visit[j]&&dist[j]>dist[u]+maz[u][j])
                dist[j]=dist[u]+maz[u][j];
    }
     return;
}
int main()
{
    int i,j,u,v,w;
    scanf("%d%d",&m,&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            maz[i][j]=INF;
    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        maz[u][v]=maz[v][u]=min(w,maz[v][u]);
    }
    dijkstra(n);
    printf("%d\n",dist[1]);
    return 0;
}
