#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct DNA
{
	char name[55];
	int num;
}DNA[100];
bool cmp(struct DNA p,struct DNA q)
{
	return p.num<q.num;
}
int main()
{
	int n,m,i,j,k;
	scanf("%d%d",&n,&m);
	for(i=0;i<m;i++)
	{
		scanf("%s",DNA[i].name);
		DNA[i].num=0;
		for(j=n-1;j;j--)
			for(k=0;k<j;k++)
				if(DNA[i].name[k]>DNA[i].name[j])
					DNA[i].num++;
	}
	sort(DNA,DNA+m,cmp);
	for(i=0;i<m;i++)
		printf("%s\n",DNA[i].name);
	return 0;
}