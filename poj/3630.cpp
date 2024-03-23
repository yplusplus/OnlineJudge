#include<cstdio>
#include<cstring>
#include<memory>
#define MAX 10

typedef struct trienode
{
	int flag;
	struct trienode *next[MAX];
}trienode;
int memoryindex=0;
trienode memory[60005];
int flag2=0;

trienode *create()
{
	trienode *p=&memory[memoryindex++];
	p->flag=0;
	for(int i=0;i<MAX;i++)
		p->next[i]=NULL;
	return p;
}

void insert(trienode *root,char *s)
{
	trienode *p=root;
	int index,i=0;
	while(s[i]!='\0')
	{
		index=s[i++]-'0';
		if(!p->next[index])
			p->next[index]=create();
		p=p->next[index];
		if(s[i]=='\0')
			p->flag=1;
	}
}

void traverse(trienode *root)
{
	int i;
	if(flag2)
		return;
	if(root->flag==1)
	{
		for(i=0;i<MAX;i++)
			if(root->next[i])
			{
				flag2=1;
				return;
			}
	}
	for(i=0;i<MAX;i++)
		if(root->next[i])
			traverse(root->next[i]);
}

int main()
{
	int t,n;
	char phone[10005][15];
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d\n",&n);
		trienode *root=create();
		for(int i=0;i<n;i++)
		{
			scanf("%s",phone[i]);
			insert(root,phone[i]);
		}
		traverse(root);
		if(flag2)
			printf("NO\n");
		else
			printf("YES\n");
		flag2=0;
		memoryindex=0;
	}
	return 0;
}
