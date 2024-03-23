#include<stdio.h>
int mod(int n,int m)
{
	return n%m;
}
main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		printf("%d\n",mod(n,m));
	}
}