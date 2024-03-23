#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string s1, s2;
long long a, b;
int getlen(long long m)
{
    int ret = 0;
    while (m)
    {
        ret++;
        m /= 10;
    }
    return ret;
}
int main()
{
    int ca = 0;
    while (cin >>a >>b)
    {
        if (!a && !b) break;
        cout <<"Problem " <<++ca <<endl;

        long long ans = a * b;
        cout <<string(getlen(ans) - getlen(a), ' ') <<a <<endl;
        cout <<string(getlen(ans) - getlen(b), ' ') <<b <<endl;
        cout <<string(getlen(ans), '-')<<endl;
        s1 = "";
        long long slen = getlen(ans);
        int cnt = 0;
        while (b)
        {
            int now = b % 10;
            if (now == 0) s1 = "0" + s1;
            else
            {
                s2 = string(slen - getlen(now * a), ' ');
                cout <<s2 <<now*a<<s1 <<endl;
                s1.clear();
                cnt++;
            }
            slen--;
            b /= 10;
        }
        if (cnt > 1){
            cout <<string(getlen(ans), '-')<<endl;
            cout <<ans <<endl;
        }
    }
    return 0;
}

