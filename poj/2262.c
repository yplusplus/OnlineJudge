#include<stdio.h>
#include<math.h>
#define MAX 1000005
int prime[MAX]={0};
int main()
{
	int i,j;
	int n,flag;
	for(i=3;i<=(int)sqrt((double)MAX);i+=2)
		if(!prime[i])
			for(j=2*i;j<=MAX;j+=i)
				prime[j]=1;
	scanf("%d",&n);
	while(n)
	{
		for(flag=1,i=3;i<n&&flag;i+=2)
		{
			if(prime[i])
				continue;
			for(j=n-3;j>=i;j-=2)
			{
				if(prime[j])
					continue;
				if(i+j==n)
				{
					printf("%d = %d + %d\n",n,i,j);
					flag=0;
					break;
				}
				else if(i+j<n)
					j=0;
			}
		}
		scanf("%d",&n);
	}
	return 0;
}