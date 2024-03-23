#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	int cow[10000];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&cow[i]);
	sort(cow,cow+n);
	printf("%d",cow[n/2]);
	return 0;
}
