#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <time.h>
#include <cctype>
#include <functional>
#include <deque>
#include <iomanip>
#include <bitset>
#include <assert.h>
#include <numeric>
#include <sstream>
#include <utility>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
const ll linf = 1LL << 60;
const int N = 111111;
vector<int> vec;
int hash[N];
bool visit[N / 10];
int n;

int main() {
    while (~scanf("%d", &n)) {
        vec.resize(n);
        for (int i = 0; i < n; i++) scanf("%d", &vec[i]);
        memset(hash, -1, sizeof(hash));
        memset(visit, false, sizeof(visit));
        vector<int> vec_t(vec);
        sort(vec_t.begin(), vec_t.end());
        for (int i = 0; i < vec_t.size(); i++) {
            hash[vec_t[i]] = i;
        }
        ll ans = 0;
        ll u = vec_t[0];
        for (int i = 0; i < n; i++) {
            if (!visit[i]) {
                ll cnt = 0;
                ll sum = 0;
                ll v = linf;
                int x = i;
                while (!visit[x]) {
                    visit[x] = true;
                    cnt++;
                    sum += vec[x];
                    v = min(v, (ll)vec[x]);
                    x = hash[vec[x]];
                }
                if (cnt > 1) {
                    ans += min((cnt - 1) * v + sum - v, (cnt + 1) * u + sum + v);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}

