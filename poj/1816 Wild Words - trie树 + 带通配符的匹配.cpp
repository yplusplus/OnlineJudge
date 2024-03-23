#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 110000
vector<int> cnt[MAX*7];
struct node {
	int pos;
	node *next[28];
}*root;
int vis[MAX],nodenum;
int n,m,ans[MAX],tot;
char pa[30],word[30];
int hash(char c) {
	if (c == '?') return 26;
	else if (c == '*') return 27;
	else return c - 'a'; 
}
node *CreateNode() {
	node *p;
	p = (node *) malloc (sizeof(node));
	p->pos = ++nodenum;
	for (int i = 0; i < 28; ++i)
		p->next[i] = NULL;
	return p;
}
void Release(node *p) {
	for (int i = 0; i < 28; ++i)
		if (p->next[i] != NULL) Release(p->next[i]);
	cnt[p->pos].clear();
	free(p);
}
void Insert(char *str,int in) {
	int i = 0,k;
	node *p = root;
	while (str[i]) {
		k = hash(str[i++]);
		if (p->next[k] == NULL)
			p->next[k] = CreateNode();
		p = p->next[k];
	}
	cnt[p->pos].push_back(in);
//	printf("p->pos = %d num = %d\n",p->pos,cnt[p->pos].size());
}
void Query(char *str,node *p) { //str是将要匹配的字符串，p是父节点
	int i,j,tp;
	if (str[0] == '\0') {
	//word已匹配到最后
		if (cnt[p->pos].size() != 0) {
			tp = cnt[p->pos].size();
			for (j = 0; j < tp; ++j)
				if (vis[cnt[p->pos][j]] == 0)
					ans[++tot] = cnt[p->pos][j],vis[cnt[p->pos][j]] = 1;
		}
		while (p->next[27] != NULL) {
			if (cnt[p->next[27]->pos].size() != 0) {
				tp = cnt[p->next[27]->pos].size();
				for (j = 0; j < tp; ++j)
					if (vis[cnt[p->next[27]->pos][j]] == 0)
						ans[++tot] = cnt[p->next[27]->pos][j],vis[cnt[p->next[27]->pos][j]] = 1;
			}
			p = p->next[27];
		}
		return;
	}
	int k = hash(str[0]);
	if (p->next[k] != NULL) Query(str+1,p->next[k]);
	if (p->next[26] != NULL) Query(str+1,p->next[26]);
	if (p->next[27] != NULL) {
		if (p->next[27]->next[27] != NULL) Query(str,p->next[27]);
		for (i = 0; str[i]; ++i) {
			int index = hash(str[i]);
			if (p->next[27]->next[index] != NULL )
				Query(str+i+1,p->next[27]->next[index]);
			if (p->next[27]->next[26] != NULL)
				Query(str+i+1,p->next[27]->next[26]);
		}
		Query(str+i,p->next[27]);
	}
}
int main() {
	while (scanf("%d%d",&n,&m) != EOF) {
		nodenum = 0;
		root = CreateNode();
		for (int i = 0; i < n; ++i)
			scanf("%s",pa),Insert(pa,i);
		for (int i = 0; i < m; ++i) {
			tot = 0;
			memset(vis,0,sizeof(vis));
			scanf("%s",word);
			Query(word,root);
			sort(ans+1,ans+1+tot);
			if (tot == 0)
				printf("Not match\n");
			else for (int j = 1; j <= tot; ++j)
				printf(j == tot ? "%d \n" : "%d ",ans[j]);
		}
		Release(root);
	}
}
