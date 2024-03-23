#include "iostream"
#include "cstdio"
#include "string"
using namespace std;

typedef struct trie {
	int cnt;
	trie *next[26];
}trie;

int tot;
trie memory[200005];
char word[1005][25];

void build(trie *&p) {
	p = &memory[tot++];
	for(int i = 0; i < 26; i++)
		p -> next[i] = NULL;
	p -> cnt = 1;
}

void insert(trie *p, char *s) {
	int i = 0;
	while(s[i]) {
		int k = s[i++] - 'a';
		if(p -> next[k] != NULL)
			p -> next[k] -> cnt++;
		else
			build(p -> next[k]);
		p = p -> next[k];
	}
}

void search(trie *p, char *s) {
	int i = 0;
	while(s[i]) {
		int k = s[i] - 'a';
		cout << s[i++];
		p = p -> next[k];
		if(p -> cnt == 1)
			break;
	}
	cout << endl;
}

int main() {
	int num = 0;
	trie *root = NULL;
	build(root);
	while(cin >> word[num])
		insert(root, word[num++]);
	for(int i = 0; i < num; i++) {
		cout << word[i] << " ";
		search(root, word[i]);
	}
	return 0;
}