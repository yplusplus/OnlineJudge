#include<stdio.h>
#include<algorithm>
using namespace std;
#define MAX 10005
int main()
{
	int n,i,j;
	long long cow[MAX],sum=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%lld",&cow[i]);
	sort(cow,cow+n);
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			sum+=(cow[j]-cow[i]);
	sum*=2;
	printf("%lld",sum);
	return 0;
}

