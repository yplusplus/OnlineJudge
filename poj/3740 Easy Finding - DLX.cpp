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

#define CC 2011
#define MM 60000

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
        puts("Yes, I found it");
        return true;
    }
    for(int tmp = CC, i = R[0]; i; i = R[i])
        if(S[i] < tmp) tmp = S[c=i];
    remove(c);
    for(int i = D[c]; i != c; i = D[i]) {
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
    int x;
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
        for(int i = 1; i <= n; i++) {
            H[i] = -1;//记得要先置行头指针为-1
            for(int j = 1; j <= m; j++) {
                scanf("%d", &x);
                if(x) Link(i, j);
            }
        }
        if(!Dance(0)) puts("It is impossible");
    }
    return 0;
}
