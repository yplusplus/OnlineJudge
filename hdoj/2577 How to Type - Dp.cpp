#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 105
int on[maxn], off[maxn];
char s[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		int len = strlen(s);
		on[0] = 1, off[0] = 0;
		for(int i = 0; i < len; i++) {
			if(s[i] >= 'a' && s[i] <= 'z') {
				on[i+1] = min(on[i] + 2, off[i] + 2);
				off[i+1] = min(on[i] + 2, off[i] + 1);
			} else {
				on[i+1] = min(on[i] + 1, off[i] + 2);
				off[i+1] = min(on[i] + 2, off[i] + 2);
			}
		}
		printf("%d\n", min(on[len] + 1, off[len]));
	}
	return 0;
}