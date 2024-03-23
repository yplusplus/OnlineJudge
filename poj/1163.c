#include<stdio.h>
#define max(a,b) a>b?a:b
main()
{
	int n;
	int i,j;
	int a[105][105];
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<=i;j++)
			scanf("%d",&a[i][j]);
	for(i=n-2;i>=0;i--)
		for(j=0;j<=i;j++)
			a[i][j]+=max(a[i+1][j],a[i+1][j+1]);
	printf("%d\n",a[0][0]);
}