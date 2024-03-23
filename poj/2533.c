#include<stdio.h>
#define MAX 10000
int main()
{
	int n,i,j,max=0;
	int a[MAX],maxlena[MAX]={0};
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	maxlena[1]=1;
	for(i=2;i<=n;i++)
	{
		for(j=1;j<i;j++)
		{
			if(a[i]>a[j])
				if(maxlena[j]>maxlena[i])
					maxlena[i]=maxlena[j];
		}
		maxlena[i]++;
	}
	for(i=1;i<=n;i++)
		if(max<maxlena[i])
			max=maxlena[i];
	printf("%d",max);
	return 0;
}