#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;
#define maxn 105
double maz[maxn][maxn], ans;//�÷�������maz���󣬱�ʾͼ��i��j��Ȩֵ
int n, m, fa[maxn];
bool circle[maxn], visit[maxn];
int root = 1; //�ǵ��ȶ����
const double inf = 1 << 30;

struct node {
	double x, y;
}point[maxn];

void dfs(int x) {
    visit[x] = true;
    for (int i = 1; i <= n; ++i)
        if (!visit[i] && maz[x][i] < inf)
            dfs(i);
}

bool connect() {//ע������ͨ
    memset(visit, 0, sizeof (visit));
    dfs(root);
    for (int i = 1; i <= n; ++i) if (!visit[i]) return false;
    return true;
}

int exist_circle() {
    fa[root] = root; //���ĸ��ڵ�Ϊ��
    for (int i = 1; i <= n; ++i) {//Ϊ���е�����С��ȱ�
        if (i == root || circle[i]) continue;
        fa[i] = i, maz[i][i] = inf; //�����Ի�
        for (int j = 1; j <= n; ++j) { //����С��ȱ�
            if (!circle[j] && maz[j][i] < maz[fa[i]][i])
                fa[i] = j;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (i == root || circle[i]) continue;
        memset(visit, 0, sizeof (visit));
        int j = i;
        while (!visit[j]) visit[j] = true, j = fa[j];
        if (j == root) continue;
        else return j;
    }
    return -1;
}

void update(int t) {
    ans += maz[fa[t]][t];
    for (int i = fa[t]; i != t; i = fa[i])
        ans += maz[fa[i]][i], circle[i] = true;
    for (int i = 1; i <= n; ++i)
        if (!circle[i] && maz[i][t] != inf)
            maz[i][t] -= maz[fa[t]][t];
    for (int i = fa[t]; i != t; i = fa[i]) {
        for (int j = 1; j <= n; ++j) {
            if (circle[j]) continue;
            if (maz[j][i] != inf) maz[j][t] = min(maz[j][t], maz[j][i] - maz[fa[i]][i]);
            maz[t][j] = min(maz[i][j], maz[t][j]);
        }
    }
}

void solve() {
    ans = 0;
    memset(circle, 0, sizeof (circle));
    int t;
    while ((t = exist_circle()) != -1) update(t); //���ڻ�����������ֱ�������ڻ�Ϊֹ
    for (t = 1; t <= n; ++t) {
        if (t == root) continue;
        if (!circle[t])
            ans += maz[fa[t]][t]; //�����в��ɻ��ı�Ȩ����ȥ
    }
}

double getdist(int a, int b) {
	return sqrt((point[a].x - point[b].x) * (point[a].x - point[b].x) + (point[a].y - point[b].y) * (point[a].y - point[b].y));
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		for(int i = 1; i <= n ;i++) {
			scanf("%lf%lf", &point[i].x, &point[i].y);
		}
		for(int i = 1; i < maxn; i++) {
			for(int j = 1; j < maxn; j++) {
				maz[i][j] = inf;
			}
		}
		for(int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			maz[a][b] = getdist(a, b);
		}
		root = 1;
		if(!connect()) {
			printf("poor snoopy\n");
			continue;
		}
		solve();
		printf("%.2f\n", ans);
	}
	return 0;
}