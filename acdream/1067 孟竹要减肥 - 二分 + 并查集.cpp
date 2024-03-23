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
const int N = 555;
ll x[N], y[N];
int n, m, tot;
int fa[N], cnt[N];
struct Edge {
	int u, v;
	ll dist;
	Edge(){}
	Edge(int _u, int _v, ll _dist) {
		u = _u, v = _v, dist = _dist;
	}
	bool operator< (const Edge &x) const {
		return dist < x.dist;
	}
}et[N*N];

void init() {
	for (int i = 0; i < n; i++) {
		fa[i] = i;
		cnt[i] = 1;
	}
}

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b) return false;
	fa[a] = b;
	cnt[b] += cnt[a];
}

ll getDist(int i, int j) {
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}


bool check(ll limit) {
	init();
	for (int i = 0; i < tot && et[i].dist <= limit; i++) {
		int u = et[i].u, v = et[i].v;
		Union(u, v);
	}
	for (int i = 0; i < n; i++) {
		if (cnt[i] >= m) return true;
	}
	return false;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> x[i] >> y[i];
		}
		vector<int> vec;
		tot = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				ll dist = getDist(i, j);
				vec.pb(dist);
				et[tot++] = Edge(i, j, dist);
			}
		}
		sort(vec.begin(), vec.end());
		sort(et, et + tot);
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		int l = 0, r = vec.size() - 1;
		double ans = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(vec[mid])) {
				ans = vec[mid];
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		printf("%.4f\n", sqrt(ans));
	}
	return 0;
}
