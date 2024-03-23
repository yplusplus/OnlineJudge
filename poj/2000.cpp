#include<cstdio>
int main()
{
	int day,day2,sum,i;
	scanf("%d",&day);
	while(day)
	{
		for(i=1,day2=0;day2<day;i++)
			day2+=i;
		i--;
		sum=i*(i+1)*(2*i+1)/6-i*(day2-day);
		printf("%d %d\n",day,sum);
		scanf("%d",&day);
	}
	return 0;
}