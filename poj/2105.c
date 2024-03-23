#include<stdio.h>
main()
{
	int c[8]={1,2,4,8,16,32,64,128};
	int T,a,b,i,j,sum;
	scanf("%d",&T);
	while(T--)
	{
		for(i=0;i<4;i++)
		{
			scanf("%8d",&a);
			for(sum=0,j=0;j<8;j++)
			{
				b=a%10;
				a/=10;
				if(b)
					sum+=c[j]*b;
			}
			printf("%d",sum);
			if(i<3)
				printf(".");
		}
		printf("\n");
	}
}