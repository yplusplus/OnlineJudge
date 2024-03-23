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
const int N = 333;
int L;
int passengerNumber, doorNumber;
int door[N];
int passenger[N];

//很容易知道，最后position一定落在整数点，或者0.5,1.5,2.5,……之类的点
//所以我们可以采用枚举，枚举步长为0.5
//朴素枚举复杂度是O(L*n*m)
//但是可以利用单调性优化成O(L*(n+m))
//实现时我为了避免精度丢失，把坐标放大了一倍处理

int calc(int x, int a, int b) {
    return min(abs(x - a), abs(x - b));
}

int main() {
    while(cin >> L) {
        L <<= 1;
        cin >> passengerNumber;
        for(int i = 0; i < passengerNumber; i++) {
            cin >> passenger[i];
            passenger[i] <<= 1;
        }
        cin >> doorNumber;
        for(int i = 2; i <= doorNumber; i++) {
            cin >> door[i];
            door[i] <<= 1;
        }
        door[1] = 0;
        door[0] = -inf, door[doorNumber + 1] = inf;
        
        int sum = 0;
        int pos = 0;
        for(int tmpPos = 0; tmpPos + door[doorNumber] <= L; tmpPos++) {
            int index = 0;
            int tmpSum = 0;
            for(int i = 0; i < passengerNumber; i++) {
                while(index <= doorNumber && door[index + 1] + tmpPos <= passenger[i]) index++;
                tmpSum += calc(passenger[i], door[index] + tmpPos, door[index + 1] + tmpPos);
            }
            if(sum <= tmpSum) sum = tmpSum, pos = tmpPos;
        }
        printf("%.1f %.1f\n", pos / 2.0, sum / 2.0);
    }
    return 0;
}
