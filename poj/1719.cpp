#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define max 1005
int r,c;
bool maz[max][max],visit[max];
int match[max];
bool dfs(int u)
{
	for(int v=1;v<=c;v++)
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
	for(int u=1;u<=r;u++)
	{
		memset(visit,false,sizeof(visit));
		if(dfs(u))
			cnt++;
	}
	return cnt;
}

int main()
{
	int i,j,u1,u2,v,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&r,&c);
		memset(maz,0,sizeof(maz));
		for(v=1;v<=c;v++)
		{
			scanf("%d%d",&u1,&u2);
			maz[u1][v]=maz[u2][v]=1;
		}
		if(Match()==r)
        {            
			for(i=1;i<=c;i++)                
				if(match[i]!=-1)  
					printf("%d ",match[i]);                
				else                
				{                    
					for(j=1;j<=r;j++)                         
						if(maz[j][i])
						{
							printf("%d ",j); 
							break;
						}                
				}                
				printf("\n");        
		}
		else
			printf("NO\n");
	}
	return 0;
}