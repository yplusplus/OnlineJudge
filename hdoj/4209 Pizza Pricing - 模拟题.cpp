#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

int n,ans,a,b;
int cas;

int main(){
    cas=0;
    while (~scanf("%d",&n)){
        if (n==0) break;
        double minn=(1<<20)*1.0;
        for (int i=0; i<n; i++){
            scanf("%d%d",&a,&b);
            if (minn>(b*1.0)/(a*a*1.0)){
                minn=(b*1.0)/(a*a*1.0);
                ans=a;
            }
        }
        cas++;
        cout << "Menu " << cas << ": " << ans << endl;
    }
}

