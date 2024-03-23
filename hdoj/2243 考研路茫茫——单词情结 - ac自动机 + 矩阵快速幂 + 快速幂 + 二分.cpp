#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define ull unsigned long long
int n, l;
const int kind = 26;
const int maxn = 35;
int root, tot;
char ch[10];
bool visit[maxn];
struct Node {
    int child[kind];
    int fail;
    bool id;
    void init() {
        memset(child, 0, sizeof (child));
        fail = -1, id = false;
    }
} T[maxn];

int que[maxn], head, tail;
void init() {
    root = tot = 0;
    T[root].init();
}

struct Mat {
	ull val[maxn][maxn];
	void unit() {//单位矩阵
		zero();
		for(int i = 0; i < maxn; i++) val[i][i] = 1;
	}
	void zero() {//零矩阵
		memset(val, 0, sizeof(val));
	}
}x;

Mat operator *(const Mat &a, const Mat &b) {//矩阵乘法
	Mat tmp;
	tmp.zero();
	for(int k = 0; k <= tot; k++) {
		for(int i = 0; i <= tot; i++)
			if(a.val[i][k])
				for(int j = 0; j <= tot; j++) {
					tmp.val[i][j] += a.val[i][k] * b.val[k][j];
				}
	}
	return tmp;
}

Mat operator ^(Mat x, int n) {//矩阵快速幂
	Mat tmp;
	tmp.unit();
	while(n) {
		if(n & 1) tmp = tmp * x;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

Mat operator +(const Mat &a, const Mat &b) {//矩阵加法
	Mat tmp;
	for(int i = 0; i <= tot; i++)
		for(int j = 0; j <= tot; j++)
			tmp.val[i][j] = a.val[i][j] + b.val[i][j];
	return tmp;
}

void insert(char *s) {//插入单词
    int p = root, index;
    while (*s) {
        index = *s - 'a';
        if (!T[p].child[index]) {
            T[++tot].init();
            T[p].child[index] = tot;
        }
        p = T[p].child[index];
        s++;
    }
    T[p].id = true;
}

void build_ac_auto() {
    head = tail = 0;
    que[tail++] = root;
    while (head < tail) {
        int u = que[head++];
        for (int i = 0; i < kind; i++) {
            if (T[u].child[i]) {
                int son = T[u].child[i];
                int p = T[u].fail;
                if (u == root) T[son].fail = root;
				else {
					T[son].fail = T[p].child[i];
					T[son].id |= T[T[son].fail].id;
				}
                que[tail++] = son;
            } else {//trie图，设定虚拟节点
                int p = T[u].fail;
                if (u == root) T[u].child[i] = root;
                else T[u].child[i] = T[p].child[i];
            }
        }
    }
}

Mat sum(int k) {
	if(k == 1) return x;
	else {
		Mat tmp = sum(k >> 1);
		if(k & 1) {
			Mat tmp2 = x ^ ((k >> 1) + 1);
			return tmp + tmp2 + tmp * tmp2;
		} else {
			Mat tmp2 = x ^ (k >> 1);
			return tmp + tmp * tmp2;
		}
	}
}

ull quickpower(ull x, int n) {
	ull tmp = 1;
	while(n) {
		if(n & 1) tmp = x * tmp;
		x = x * x;
		n >>= 1;
	}
	return tmp;
}

ull sum2(ull x, int k) {
	if(k == 1) return x;
	ull tmp = sum2(x, k >> 1);
	if(k & 1) {
		ull tmp2 = quickpower(x, (k >> 1) + 1);
		return tmp + tmp2 + tmp * tmp2;
	} else {
		ull tmp2 = quickpower(x, k >> 1);
		return tmp + tmp * tmp2;
	}
}

void create_Mat() {
	x.zero();
	for(int i = 0; i <= tot; i++)
		if(!T[i].id)
			for(int j = 0 ;j < kind; j++) {
				int son = T[i].child[j];
				if(!T[son].id)
					x.val[i][son]++;
			}
}
			
void solve() {
	memset(visit, false, sizeof(visit));
	create_Mat();
	ull ans = sum2(26, l);
	Mat tmp = sum(l);
	for(int i = 0; i <= tot; i++) 
		ans -= tmp.val[0][i];
	printf("%I64u\n", ans);
}

int main() {
	while(~scanf("%d%d", &n, &l)) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%s", ch);
			insert(ch);
		}
		build_ac_auto();
		solve();
	}
	return 0;
}