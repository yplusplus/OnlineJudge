#include<stdio.h>
#include<string.h>
int main()
{
	char letter[260];
	int i,len,sum=0;
	gets(letter);
	while(letter[0]!='#')
	{
		len=strlen(letter);
		for(sum=0,i=0;i<len;i++)
		{
			if(letter[i]==' ')
				continue;
			else
				sum+=(i+1)*(letter[i]-64);
		}
		printf("%d\n",sum);
		gets(letter);
	}
	return 0;
}

