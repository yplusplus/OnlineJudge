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
const int number = 16;
int a[number];

//15�����ж����޽�
//����������+0�����е��±꣨��1��ʼ��Ϊż�������н⣻�����޽�

int main() {
    for (int i = 0; i < number; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < number; i++) {
        if (a[i] == 0) {
            ans += i / 4;
        } else {
            for (int j = 0; j < i; j++) {
                if (a[j] > a[i]) ans++;
            }
        }
    }
    puts((ans & 1) ? "YES" : "NO");
    return 0;
}
