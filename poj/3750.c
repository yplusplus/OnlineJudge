#include<stdio.h>
#include<string.h>
main()
{
	int n,i,w,s,j;
	char name[65][20];
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%s",name[i]);
	scanf("%d,%d",&w,&s);
	w--;
	s--;
	while(n)
	{
		w=(w+s)%n;
		printf("%s\n",name[w]);
		for(j=w;j<n;j++)
			strcpy(name[j],name[j+1]);
		n--;
	}
}
