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
#include "set"
#include "utility"
using namespace std;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sof(x) sizeof(x)
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

#define CC 1011
#define MM 102011

int L[MM], R[MM], U[MM], D[MM], C[MM], X[MM];
int H[CC], S[CC], Q[CC];
int size, n, m;

void remove(int c) {
    R[L[c]] = R[c], L[R[c]] = L[c];
    for(int i = D[c]; i != c; i = D[i])
        for(int j = R[i]; j != i; j = R[j])
            U[D[j]] = U[j], D[U[j]] = D[j], --S[C[j]];
}

void resume(int c) {
    R[L[c]] = L[R[c]] = c;
    for(int i = U[c]; i != c; i = U[i])
        for(int j = L[i]; j != i ; j = L[j])
            ++S[C[U[D[j]] = D[U[j]] = j]];
}

bool Dance(int k) {
    int c = -1;
    if(!R[0]) {
        printf("%d", k);
        for(int i = 0; i < k; i++) printf(" %d", X[Q[i]]);
        puts("");
        return true;
    }
    for(int tmp = CC, i = R[0]; i; i = R[i])
        if(S[i] < tmp) tmp = S[c=i];
    remove(c);
    for(int i = D[c]; i != c; i = D[i]) {
        Q[k] = i;
        for(int j = R[i]; j != i; j = R[j]) remove(C[j]);
        if(Dance(k + 1)) return true;
        for(int j = L[i]; j != i; j = L[j]) resume(C[j]);
    }
    resume(c);
    return false;
}

void Link(int r, int c) {
    ++S[C[size] = c];
    D[size] = D[c];
    U[D[c]] = size;
    U[size] = c;
    D[c] = size;
    if(H[r] < 0) H[r] = L[size] = R[size] = size;
    else {
        R[size] = R[H[r]];
        L[R[H[r]]] = size;
        L[size] = H[r];
        R[H[r]] = size;
    }
    X[size++] = r;
}

int main() {
    int num;
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 0; i <= m; i++) {
            S[i] = 0;
            D[i] = U[i] = i;
            L[i+1] = i;
            R[i] = i + 1;
        }
        R[m] = 0;
        L[0] = m;
        size = m + 1;
        for(int i = 1, j; i <= n; i++) {
            H[i] = -1;//记得要先置行头指针为-1
            scanf("%d", &num);
            while(num--) {
                scanf("%d", &j);
                Link(i, j);
            }
        }
        if(!Dance(0)) puts("NO");
    }
    return 0;
}
