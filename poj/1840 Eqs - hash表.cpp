#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;
int a[5];
const int Min = -50, Max = 50;
char hash[25000010];
int main() {
    memset(hash, 0, sizeof(hash));
    for(int i = 0; i < 5; i++) cin >> a[i];
    for(int i = Min; i <= Max; i++) {
        if(i == 0) continue;
        for(int j = Min; j <= Max; j++) {
            if(j == 0) continue;
            for(int k = Min; k <= Max; k++) {
                if(k == 0) continue;
                int tmp = i * i * i * a[0] + j * j * j * a[1] + k * k * k * a[2];
                if(tmp > 12500000 || tmp < -12500000)
                     continue;
                hash[tmp + 12500000]++;
            }
        }
    }
    int ans = 0;
    for(int i = Min; i <= Max; i++) {
        if(i == 0) continue;
        for(int j = Min; j <= Max; j++) {
            if(j == 0) continue;
            int tmp = -(i * i * i * a[3] + j * j * j * a[4]);
            ans += hash[tmp + 12500000];
        }
    }
    cout << ans << endl;
    return 0;
}

