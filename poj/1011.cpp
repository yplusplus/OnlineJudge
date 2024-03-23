#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX 65

bool cmp(int a,int b)
{
	return a>b;
}

bool visit[MAX];									//标记使用情况
int stick[MAX];										//记录小木棒长度
int n,flag,len,sum;

void dfs(int used,int nowlen,int index)				//used记录小木棒已组合的数目，index记录当前要处理小木棒的下标
{
	if(flag)
		return;
	if(nowlen==0)									//选择一个最长且未组合的小木棒
	{
		int k=0;
		while(visit[k])
			k++;
		visit[k]=true;
		dfs(used+1,stick[k],k+1);
		visit[k]=false;
		return;
	}
	if(nowlen==len)									//一个木棒组合完成
	{
		if(used==n)									//所有小木棒均已组合
		{
			flag=true;								//找到答案，停止搜索
			return;
		}
		else
		{		
			dfs(used,0,0);							//未完成，继续搜索
		}
	}
	for(int i=index;i<n;i++)						//最一般的情况
	{
		if(!visit[i-1]&&stick[i]==stick[i-1])		//如果前一根小木棒没有使用且和当前一根长度相等，即不用搜这一根（重要剪枝）	
			continue;
		if(!visit[i]&&nowlen+stick[i]<=len)			//选取未组合小木棒加入到当前组合的木棒中
		{
			visit[i]=true;
			dfs(used+1,nowlen+stick[i],i+1);
			visit[i]=false;
		}
	}
}

int main()
{
	while(1)
	{
		sum=flag=0;
		scanf("%d",&n);
		if(!n)
			break;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&stick[i]);
			sum+=stick[i];
		}
		sort(stick,stick+n,cmp);
		for(len=stick[0];len<sum;len++)
		{
			if(sum%len!=0)
				continue;
			memset(visit,0,sizeof(visit));
			dfs(0,0,0);
			if(flag)
				break;
		}
		printf("%d\n",len);
	}
	return 0;
}
