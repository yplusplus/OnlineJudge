#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 1005
#define maxm 15005
int n,m;
int p[maxn];
int num=0;
int path[maxm];

struct edge
{
    int u,v,w;
}edge[maxm];

bool cmp(struct edge p,struct edge q)
{
    if(p.w!=q.w)
        return p.w<=q.w;
    if(p.u!=q.u)
        return p.u<q.u;
    return p.v<=q.v;
}

int find(int x)
{
    return p[x]==x?x:p[x]=find(p[x]);
}

int kruskal()
{
    int i;
    int max=0;
    for(i=0;i<n;i++)
        p[i]=i;
    sort(edge,edge+m,cmp);
    for(i=0;i<m;i++)
    {
        if(num==n-1)
            break;
        int x=find(edge[i].u),y=find(edge[i].v);
        if(x!=y)
        {
            p[x]=y;
            if(max<edge[i].w)
                max=edge[i].w;
            path[num++]=i;
        }
    }
    return max;
}

int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    printf("%d\n",kruskal());
    printf("%d\n",num);
    for(i=0;i<num;i++)
        printf("%d %d\n",edge[path[i]].u,edge[path[i]].v);
    return 0;
}