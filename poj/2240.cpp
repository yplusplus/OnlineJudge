#include<cstdio>
#include<map>
#include<cstring>
#include<string>
using namespace std;
#define M 35

int n,m;
double g[M][M];
void floyd()
{
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			if(g[i][k])
				for(int j=0;j<n;j++)	
					if(g[i][j]<g[i][k]*g[k][j])
						g[i][j]=g[i][k]*g[k][j];
}
int main()
{
	int i,j,t=1;
	double rate;
	char s[100],s1[100],s2[100];
	map<string,int> ma;
	while(1)
	{
		scanf("%d",&n);
		if(!n)
			break;
		memset(g,0,sizeof(g));
		for(i=0;i<n;i++)
		{
			scanf("%s",s);
			ma[s]=i;
			g[i][i]=1;
		}
		scanf("%d",&m);
		for(i=0;i<m;i++)
		{
			scanf("%s",s1);
			scanf("%lf",&rate);
			scanf("%s",s2);
			g[ma[s1]][ma[s2]]=rate;
		}
		floyd();
		printf("Case %d: ",t++);
		for(i=0;i<n;i++)
		{
			if(g[i][i]>1)
			{
				printf("Yes\n");
				break;
			}
		}
		if(i==n)
			printf("No\n");
	}
	return 0;
}		
