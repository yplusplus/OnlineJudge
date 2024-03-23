#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX 65

bool cmp(int a,int b)
{
	return a>b;
}

bool visit[MAX];									//���ʹ�����
int stick[MAX];										//��¼Сľ������
int n,flag,len,sum;

void dfs(int used,int nowlen,int index)				//used��¼Сľ������ϵ���Ŀ��index��¼��ǰҪ����Сľ�����±�
{
	if(flag)
		return;
	if(nowlen==0)									//ѡ��һ�����δ��ϵ�Сľ��
	{
		int k=0;
		while(visit[k])
			k++;
		visit[k]=true;
		dfs(used+1,stick[k],k+1);
		visit[k]=false;
		return;
	}
	if(nowlen==len)									//һ��ľ��������
	{
		if(used==n)									//����Сľ���������
		{
			flag=true;								//�ҵ��𰸣�ֹͣ����
			return;
		}
		else
		{		
			dfs(used,0,0);							//δ��ɣ���������
		}
	}
	for(int i=index;i<n;i++)						//��һ������
	{
		if(!visit[i-1]&&stick[i]==stick[i-1])		//���ǰһ��Сľ��û��ʹ���Һ͵�ǰһ��������ȣ�����������һ������Ҫ��֦��	
			continue;
		if(!visit[i]&&nowlen+stick[i]<=len)			//ѡȡδ���Сľ�����뵽��ǰ��ϵ�ľ����
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
