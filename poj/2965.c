#include<stdio.h>
#include<string.h>
int main()
{
	char light[5][5];
	int num[5][5]={0};
	int i,j,k;
	int sum=0;
	for(i=1;i<=4;i++)
		scanf("%s",light[i]+1);
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(light[i][j]=='+')
			{
				for(k=1;k<=4;k++)
					num[i][k]++;
				for(k=1;k<=4;k++)
					num[k][j]++;
				num[i][j]--;
			}
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(num[i][j]%2)
				sum++;
	printf("%d\n",sum);
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			if(num[i][j]%2!=0)
				printf("%d %d\n",i,j);
	return 0;
}