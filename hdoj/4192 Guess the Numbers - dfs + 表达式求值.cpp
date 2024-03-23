#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
int n, ans;
int val[10];
int visit[10];
int hash1[256];
vector<int> vec;
string ex;
int s1[100000], top1;
char s2[100000], top2;
int size;
bool flag;

int func(char op, int a, int b) {
    if(op == '*') return a * b;
    if(op == '+') return a + b;
    if(op == '-') return a - b;
}

void dfs(int cnt) {
    if(cnt == n) {
        top1 = top2 = 0;
        for(int i = 0; i < size; i++) {
            if(ex[i] == '(') s2[top2++] = ex[i];
            else if(ex[i] == ')') {
                if(s2[top2-1] == '(') top2--;
                else {
                    int b = s1[--top1];
                    int a = s1[--top1];
                    s1[top1++] = func(s2[--top2], a, b);
                    top2--;
                }
            } else if(islower(ex[i])) {//Î´ÖªÊý
                if(s2[top2-1] == '*') {
                    top2--;
                    int tmp = func('*', s1[--top1], hash1[ex[i]]);
                    s1[top1++] = tmp;
                } else s1[top1++] = hash1[ex[i]];
            } else {//ÔËËã·û
                if(ex[i] == '*') s2[top2++] = ex[i];
				else if(s2[top2-1] != '(') {
                    char op = s2[--top2];
                        int b = s1[--top1];
                        int a = s1[--top1];
                        int tmp = func(op, a, b);
                        top2--;
                        s1[top1++] = tmp;
				} else s2[top2++] = ex[i];
            }
        }
        if(s1[top1-1] == ans) flag = true;
    } else {
        for(int i = 0; i < n && !flag; i++) {
            if(!visit[i]) {
                hash1[vec[cnt]] = val[i];
                visit[i] = true;
                dfs(cnt+1);
                visit[i] = false;
            }
        }
    }
}

int main() {
    while(1) {
        vec.clear();
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &val[i]);
        cin >> ans;
        if(!n) break;
        cin >> ex;
        size = ex.size();
        for(int i = 0; i < size; i++) {
            if(islower(ex[i])) vec.pb(ex[i]);
        }
        sort(vec.begin(), vec.end());
        unique(vec.begin(), vec.end());
        memset(visit, false, sizeof(visit));
        flag = false;
        dfs(0);
        if(flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
