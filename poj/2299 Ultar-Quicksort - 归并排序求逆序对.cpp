#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
#define maxn 1005000
#define ll long long
int val[maxn];
int tmp[maxn];//辅助数组
int n;
ll cnt;

void output() {
    cout << val[1];
    for(int i = 2; i <= n; i++) cout << " " << val[i] ;
    cout << endl;
}

void Merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    while(i <= mid && j <= r) {
        if(val[i] > val[j]) tmp[k++] = val[j++], cnt += mid + 1 - i;
        else tmp[k++] = val[i++]; 
    }
    while(i <= mid) tmp[k++] = val[i++];
    while(j <= r) tmp[k++] = val[j++];
    while(l <= r) val[l] = tmp[l], l++;
}

void Mergesort() {
    cnt = 0;
    for(int len = 1; len < n; len *= 2) {//控制区间长度
        int i;
        for(i = 1; i + 2 * len - 1 <= n; i += 2 * len) { 
            Merge(i, i + len - 1, i + 2 * len - 1);    
        }
        if(i + len - 1 <= n) {
            Merge(i, i + len - 1, n);
        }
//        output();
    }
}

int main() {
    while(~scanf("%d", &n)) {
        if(n == 0) break;
        for(int i = 1; i <= n; i++) cin >> val[i];
        Mergesort();
        cout << cnt << endl;
 //       break;
    }
    return 0;
}
