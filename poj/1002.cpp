#include<string.h>
#include<stdio.h>
#include<algorithm>
using namespace std;

struct phone
{
	char telenum[9];
	int num;
}phone[100005];

const int map[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9};

bool cmp(struct phone p,struct phone q)
{
	if(strcmp(p.telenum,q.telenum)<=0)
		return true;
	else
		return false;	
}
int main()
{
	int n;
	int i,j,flag;
	char ch;
	
	scanf("%d\n",&n);
	for(i=0;i<n;i++)
	{
		j=0;
		while((ch=getchar())!='\n')
		{
			if(ch=='-')
				continue;
			else if(ch>='0'&&ch<='9')
				phone[i].telenum[j++]=ch;
			else 
				phone[i].telenum[j++]=map[ch-'A']+'0';
			if(j==3)
				phone[i].telenum[j++]='-';
		}
		phone[i].num=1;
	}
	sort(phone,phone+n,cmp);

	for(i=1,flag=1;i<n;i++)
	{
		if(strcmp(phone[i-1].telenum,phone[i].telenum)==0)
		{
			phone[i].num+=phone[i-1].num;
			phone[i-1].num=0;
			flag=0;
		}
	}
	if(flag)
		printf("No duplicates.");
	else
		for(i=0;i<n;i++)
		{
			if(phone[i].num<=1)
				continue;			
			printf("%s %d\n",phone[i].telenum,phone[i].num);
		}
	return 0;
}