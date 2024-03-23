#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "vector"
#include "queue"
#include "stack"
#include "cmath"
#include "string"
#include "cctype"
#include "map"
#include "iomanip"
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long
#define ull unsigned long long
const int inf = 1 << 29;
const double dinf = 1e30;
const ll linf = 1LL << 55;
const int N = 1111;
int k;
int maxNumber[N][N];
int len;
string ansStr, s;
//贪心
//考虑每次从start开始前k个，把其中最大的之前的删去，递归处理后面
void dfs(int start) {
    if(k == 0) {
        ansStr += s.substr(start);
        return;
    }
    if(len - start == k) return;
    int end = min(len - 1, start + k);
    for(int i = start; i <= end; i++) {
        if(maxNumber[start][i] == maxNumber[start][end]) {
            ansStr += s[i];
            k -= i - start;
            dfs(i + 1);
            return;
        }
    }
}

int main() {
    while(cin >> s >> k) {
        memset(maxNumber, -1, sizeof(maxNumber));
        len = s.length();
        for(int i = 0; i < len; i++) {
            maxNumber[i][i] = s[i];
            for(int j = i + 1; j < len; j++) {
                maxNumber[i][j] = max(maxNumber[i][j-1], (int)s[j]);
            }
        } 
        ansStr = "";
        dfs(0);
        cout << ansStr << endl;
    }
    return 0;
}
