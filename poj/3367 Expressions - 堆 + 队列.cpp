#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "stack"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define maxn 105000
char str[maxn];
int s[maxn], top;
struct Node {
    int l, r;
}p[maxn];

bool islow(char ch) {
    if(ch <= 'Z' && ch >= 'A') return false;
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", str);
        top = 0;
        for(int i = 0; i < maxn; i++) p[i].l = p[i].r = -1;
        int len = strlen(str);
        for(int i = 0; i < len; i++) {
            if(islow(str[i])) s[top++] = i;
            else {
                int a = s[--top], b = s[--top];
                p[i].r = a, p[i].l = b;
                s[top++] = i;
            }
        }
        queue<int> que;
        int cnt = 0;
        char ans[maxn];
        que.push(len-1);
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            ans[cnt++] = str[now];
            if(p[now].l != -1) que.push(p[now].l);
            if(p[now].r != -1) que.push(p[now].r);
        }
        for(int i = len - 1; i >= 0; i--) {
            cout << ans[i];
        }
        puts("");
    }
    return 0;
}
