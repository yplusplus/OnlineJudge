#include<stdio.h>
#define max(a,b) a>b?a:b
int main()
{
	int i,j;
	int n;
	int cow[355][355];
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<=i;j++)
			scanf("%d",&cow[i][j]);
	for(i=n-2;i>=0;i--)
		for(j=0;j<=i;j++)
			cow[i][j]+=max(cow[i+1][j],cow[i+1][j+1]);
	printf("%d",cow[0][0]);
	return 0;
}