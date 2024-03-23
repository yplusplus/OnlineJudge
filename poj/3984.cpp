#include"cstdio"
#include"iostream"
#include"cstring"
#include"queue"
using namespace std;
#define n 5
typedef struct node
{
	int x,y;
}node;
int maz[5][5];
int dx[]={0,1,0,-1};
int dy[]={-1,0,1,0};
bool visit[5][5];
int p[5][5][2];
void bfs()
{
	visit[0][0]=1;
	p[0][0][0]=p[0][0][1]=-1;
	node s={0,0};
	queue<node> que;
	que.push(s);
	while(!que.empty())
	{
		node tmp=que.front();
		que.pop();
		for(int i=0;i<4;i++)
		{
			node tmp2;
			tmp2.x=tmp.x+dx[i];
			tmp2.y=tmp.y+dy[i];
			if(tmp2.x>=0&&tmp2.x<5&&tmp2.y>=0&&tmp2.y<5&&!visit[tmp2.x][tmp2.y]&&!maz[tmp2.x][tmp2.y])
			{
				visit[tmp2.x][tmp2.y]=1;
				p[tmp2.x][tmp2.y][0]=tmp.x;
				p[tmp2.x][tmp2.y][1]=tmp.y;
				que.push(tmp2);
			}
		}
	}
}

void print(int x,int y)
{
	if(x==-1&&y==-1)
		return ;
	else
		print(p[x][y][0],p[x][y][1]);
	printf("(%d, %d)\n",x,y);
}


int main()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>maz[i][j];
	bfs();
	print(4,4);
	return 0;
}
			