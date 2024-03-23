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
#define all(a) (a).begin(),(a).end()
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FORD(i,a,b) for (int i=(a); i>=(b); i--)
#define REP(i,b) FOR(i,0,b)
#define sf scanf
#define pf printf
using namespace std;
const int maxint = -1u>>1;
const double pi = 3.14159265358979323;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<int>::iterator vit;
#define maxn 110
double mat[maxn][maxn], x[maxn];
int A, B, C, n;
vector<int> vec[maxn];
#define eps 1e-16

inline int dcmp(double d) {
    return (d < -eps) ? -1 : (d > eps);
}
//mat[][]=增广矩阵
//row=行数,col=列数,x[i]=变量i的值
bool gauss(int row, int col) {
    int r , c , i , j;
    for(r = c = 0; r < row && c < col; r++, c++) {
        for(i = r ; i < row ; i ++) if(dcmp(mat[i][c]) != 0)break;
        if(i == row) {r--; continue;}
        if(i != r) {
            for(j = c ; j <= col ; j ++)
                swap(mat[i][j],mat[r][j]);
        }
        for(i = r + 1; i < row; i++) {
            if(dcmp(mat[i][c]) != 0) {
                double temp = mat[i][c] / mat[r][c];
                for(j = c; j <= col; j++) mat[i][j] -= mat[r][j] * temp;
            }
        }
    }
    for(i = row - 1 ; i >= 0 ; i --) {
        if(dcmp(mat[i][i]) != 0) x[i] = mat[i][col] / mat[i][i];
        else {
            if(dcmp(mat[i][col]) == 0) x[i] = 0.0;
            else return false;//无解
        }
        for(j = 0; j < i; j++) mat[j][col] -= mat[j][i] * x[i];
    }
    return true;
}

int main() {
    while(~scanf("%d", &n)) {
        scanf("%d%d%d", &A, &B, &C);
        A--, B--, C--;
        for(int i = 0; i < n; i++) {
            vec[i].clear();
        }
        int u, v;
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            u--, v--;
            vec[u].pb(v);
            vec[v].pb(u);
        }
        memset(mat, 0, sizeof(mat));
        for(int i = 0; i < n; i++) {
            if(i == B || i == C) {
                mat[i][i] = 1.0;
                if(i == B) mat[i][n] = 1.0;
            } else {
                mat[i][i] = (double)vec[i].size();
                mat[i][n] = 0.0;
                for(int j = 0; j < vec[i].size(); j++) {
                    int ii = vec[i][j];
                    mat[i][ii] = -1.0;
                }
            }
        }
        gauss(n, n);
        printf("%.6f\n", x[A]);
    }
    return 0;
}

