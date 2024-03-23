#include<cstdio>
#include<cstring>
int n,num;
char map[10][10];
bool visit[10];
int ans;
void dfs(int i,int j,int count)
{
	if(count==0)
	{
		ans++;
		return;
	}
	if(n-i<count)
		return;
	for(;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(map[i][j]=='#'&&!visit[j])
			{
				visit[j]=1;
				dfs(i+1,0,count-1);
				visit[j]=0;
			}
		}
	}
}
int main()
{
	int i;
	while(1)
	{
		scanf("%d %d",&n,&num);
		if(n==-1&&num==-1)
			break;
		for(i=0;i<n;i++)
			scanf("%s",map[i]);
		memset(visit,0,sizeof(visit));
		ans=0;
		dfs(0,0,num);
		printf("%d\n",ans);
	}
	return 0;
}