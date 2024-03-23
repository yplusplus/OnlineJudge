#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;
string s;
int cnt[30];
bool solve() {
    memset(cnt, 0, sizeof(cnt));
    int len = s.length();
    for(int i = 0; i < len; i++) {
        if(isupper(s[i])) {
            cnt[s[i] - 'A']++;
            if(cnt[s[i] - 'A'] > 1) return false;
        }
    }
    return true;
}

int main() {
    while(1) {
        getline(cin, s);
        if(s == "END") break;
        if(solve()) cout << s << endl;
    }
    return 0;
}

