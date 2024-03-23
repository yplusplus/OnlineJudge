#include<stdio.h>
#include<string.h>
#define MAX 1000
#define max(a,b) a>b?a:b
int main()
{
	int i,j;
	char s1[MAX],s2[MAX];
	int s1len,s2len;
	int maxlen[MAX][MAX];
	for(i=0;i<=s1len;i++)
		maxlen[i][0]=0;
	for(j=0;j<=s2len;j++)
		maxlen[0][j]=0;
	while(scanf("%s%s",s1+1,s2+1)>0)
	{
		s1len=strlen(s1+1);
		s2len=strlen(s2+1);
		for(i=1;i<=s1len;i++)
			for(j=1;j<=s2len;j++)
			{
				if(s1[i]==s2[j])
					maxlen[i][j]=maxlen[i-1][j-1]+1;
				else
					maxlen[i][j]=max(maxlen[i][j-1],maxlen[i-1][j]);
			}
		printf("%d\n",maxlen[s1len][s2len]);
	}
	return 0;
}
