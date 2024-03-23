#include<stdio.h>
#include<string.h>
main()
{
	int cells[105];
	int n,T,sum;
	int i,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		memset(cells,1,sizeof(cells));
		for(i=2;i<=n;i++)
			for(j=i;j<=n;j+=i)
				cells[j]=!cells[j];
		for(sum=0,i=1;i<=n;i++)
			if(cells[i])
				sum++;
		printf("%d\n",sum);
	}
}
