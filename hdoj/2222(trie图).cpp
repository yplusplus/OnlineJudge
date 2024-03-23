#include "iostream"
#include "cstdio"
#include "string"
#include "queue"
using namespace std;
const int size = 26;
#define MAX 300005
typedef struct trie {
	int end;
	trie *next[size], *fail;
}trie;

trie memory[MAX];
int tot;
char text[1000005], word[55];
void build(trie *&p) {
	p = &memory[tot++];
	for(int i = 0; i < size; i++)
		p -> next[i] = NULL;
	p -> end = 0;
}

void insert(trie *p, char *s) {
	while(*s) {
		int k = *s++ - 'a';
		if(!p -> next[k])
			build(p -> next[k]);
		p = p -> next[k];
	}
	p -> end++;
}

void build_ac_auto(trie *root) {
	queue<trie*> que;
	que.push(root);
	trie *tmp, *p;
	root -> fail = NULL;  
	while(!que.empty()) {  
		tmp = que.front();  
		que.pop();
		for(int i = 0; i < size; i++) 
			if(tmp -> next[i]) {  
				if(tmp == root)	tmp -> next[i] -> fail = root;  
				else tmp-> next[i] -> fail = tmp -> fail -> next[i];    
				que.push(tmp -> next[i]);  
			} else {
				if(tmp == root) tmp -> next[i] = root;
				else tmp ->next[i] = tmp -> fail -> next[i];
			}
	}  
}

int query(trie *root, char *s) {
	int cnt = 0;
	trie *tmp = root, *t;
	while(*s) {
		int k = *s++ - 'a';
		tmp = tmp -> next[k];
		t = tmp;
		while(t != root && t -> end) {
			cnt += t -> end;
			t -> end = 0;
			t = t -> fail;
		}
	}  
	return cnt;  
}

int main() {
	int t, n;
	cin >> t;
	while(t--) {
		cin >> n;
		trie *root;
		tot = 0;
		build(root);
		for(int i = 0; i < n; i++) {
			cin >> word;
			insert(root, word);
		}
		cin >> text;
		build_ac_auto(root);
		cout << query(root, text) << endl;
	}
	return 0;
}