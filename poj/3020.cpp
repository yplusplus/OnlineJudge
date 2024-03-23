#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define maxn 405
int n,m,cnts;
int map[maxn][maxn];
bool maz[maxn][maxn],visit[maxn];
int match[maxn];
char map2[45][15];
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

int dfs(int u)
{
	for(int v=1;v<=n;v++)
	{
		if(maz[u][v]&&!visit[v])
		{
			visit[v]=true;
			if(match[v]==-1||dfs(match[v]))
			{
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}

int Match()
{
	int cnt=0;
	memset(match,-1,sizeof(match));
	for(int u=1;u<=n;u++)
	{
		memset(visit,false,sizeof(visit));
		if(dfs(u))
			cnt++;
	}
	return cnt;
}

bool judge(int x,int y)
{
    if(x<=n&&y<=m&&x>=1&&y>=1&&map2[x][y]=='*') return true;
    return false;
}

void init()
{
    int i,j,k;
    int xx,yy,a,b;
    cnts=0;
    for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(map2[i][j]=='*')
			{
				cnts++;
				a=(i-1)*m+j;
				for(k=0;k<4;k++)
                {
                    xx=i+dir[k][0];
                    yy=j+dir[k][1];
                    if(judge(xx,yy))
                    {
                        b=(xx-1)*m+yy;
                        maz[a][b]=1;
                    }
                }
			}
     n=n*m;
}

int main()
{
	int i,t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		memset(maz,false,sizeof(maz));
		for(i=1;i<=n;i++)
			scanf("%s",&map2[i][1]);	
		init();
		cout<<cnts-Match()/2<<endl;
	}
	return 0;
}