#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define eps 1e-8

using namespace std;

struct Point {
    double a[13];
    double s;
}p[20];
double mat[20][20];
double x[20];

//下标从0开始
inline int dcmp(double d) {
    return (d < -eps) ? -1 : (d > eps);
}
//mat[][] 增广矩阵
//row 行数，col 列数 x[i] 变量i的值
bool gauss(int row, int col) {
    int r , c , i , j;
    for(r = c = 0; r < row && c < col; r++, c++) {
        for(i = r ; i < row ; i ++) if(dcmp(mat[i][c]) != 0) break;
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

double doubleFix(double x) {
    return fabs(x) < eps ? 0.0 : x;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        for (int i=0; i<12; i++) {
            for (int j=0; j<11; j++) {
                scanf("%lf",&p[i].a[j]);
            }
            scanf("%lf",&p[i].s);
            p[i].s=p[i].s*p[i].s;
        }
        p[12]=p[0];
        double s1,s2;
        for (int i=0; i<12; i++) {
            s1=p[i].s;
            for (int j=0; j<11; j++) {
                s1-=p[i].a[j]*p[i].a[j];
            }
            s2=p[i+1].s;
            for (int j=0; j<11; j++) {
                s2-=p[i+1].a[j]*p[i+1].a[j];
            }
            for (int j=0; j<11; j++) {
                mat[i][j]=-1.0*p[i].a[j]*2-(-1.0*p[i+1].a[j]*2);
            }
            mat[i][11]=s1-s2;
        }
        /*
        for (int i=0; i<12; i++) {
            for (int j=0; j<12; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        */
        gauss(11,11);
        for (int i=0; i<11; i++) {
            printf("%.2f%c", doubleFix(x[i]), i == 10 ? '\n' : ' ');
        }
    }
}
