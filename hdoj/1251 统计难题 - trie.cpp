#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAX 26
#define nMAX 100005
char word[nMAX][15],s[nMAX][15];
typedef struct trienode
{
	int ncount;
	struct trienode *next[MAX];
}trienode;

trienode *create()
{
	trienode *p=(trienode*)malloc(sizeof(trienode));
	p->ncount=1;
	for(int i=0;i<MAX;i++)
		p->next[i]=NULL;
	return p;
}

void insert(trienode *root,char s[])
{
	int i,index;
	trienode *p=root;
	i=0;
	while(s[i]!='\0')
	{
		index=s[i++]-'a';
		if(p->next[index])
			p->next[index]->ncount++;
		else
			p->next[index]=create();
		p=p->next[index];
	}
}

int search(trienode *root,char s[])
{
	int i,index;
	trienode *p=root;
	i=0;
	while(s[i]!='\0')
	{
		index=s[i++]-'a';
		if(p->next[index])
			p=p->next[index];
		else
			return 0;
	}
	return p->ncount;
}

int main()
{
	int i;
	trienode *root=create();
	i=0;
	do
	{
		gets(word[i]);
		insert(root,word[i]);
		i++;
	}while(strcmp(word[i-1],"")!=0);
	i=0;
	while(gets(s[i])>0)
	{
		printf("%d\n",search(root,s[i]));
		i++;
	}
	return 0;
}
