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

int n, k;
int main() {
    while (~scanf("%d%d", &n, &k)) {
        map<ll, int> count;
        ll ans = 0;
        ll sum = 0;
        count[0]++;
        for (int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            if (x == k) sum += n;
            else sum += x < k ? -1 : 1;
            //cout << sum << endl;
            ans += count[sum - n];
            count[sum]++;
        }
        cout << ans << endl;
        
    }
    return 0;
}

