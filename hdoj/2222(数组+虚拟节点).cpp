#include "iostream"
#include "string"
using namespace std;
#define maxn 700000
#define kind 26
struct Node {
	int child[kind];
	int fail;
	int id;
	void init() {
		memset(child, 0, sizeof(child));
		fail = -1, id = 0;
	}
}T[maxn];
int root, tot;
char word[55], text[1000005];
int que[maxn], head, tail;
void init() {
	root = tot = 0;
	T[root].init();
}

void insert(char *s) {
	int p = root, index;
	while(*s) {
		index = *s++ - 'a';
		if(!T[p].child[index]) {
			T[++tot].init();
			T[p].child[index] = tot;
		}
		p = T[p].child[index];
	}
	T[p].id++;
}

void build_ac_auto() {
	head = tail = 0;
	que[tail++] = root;
	while(head < tail) {
		int u = que[head++];
		for(int i = 0; i < kind; i++) {
			if(T[u].child[i]) {
				int son = T[u].child[i];
				int p = T[u].fail;
				if(u == root) T[son].fail = root;
				else T[son].fail = T[p].child[i];
				que[tail++] = son;
			} else {
				int p = T[u].fail;
				if(u == root) T[u].child[i] = root;
				else T[u].child[i] = T[p].child[i];
			}
		}
	}
}

int query(char *t) {
	int p = root, cnt = 0;
	while(*t) {
		int index = *t++ - 'a';
		p = T[p].child[index];
		int t = p;
		while(t != root && T[t].id) {
			cnt += T[t].id;
			T[t].id = 0;
			t = T[t].fail;
		}
	}
	return cnt;
}

int main() {
	int t, n;
	cin >> t;
	while(t--) {
		cin >> n;
		init();
		for(int i = 0; i < n; i++) {
			cin >> word;
			insert(word);
		}
		cin >> text;
		build_ac_auto();
		cout << query(text) << endl;
	}
	return 0;
}