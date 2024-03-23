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
using namespace std;
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

string name[10050];
struct Team {
    int kick, lost, score;
    int id;
    bool operator <(const Team &a) const {
        if(score != a.score) return score > a.score;
        if(kick - lost != a.kick - a.lost) return (kick - lost) > (a.kick - a.lost);
        if(kick != a.kick) return kick > a.kick;
        return name[id] < name[a.id];
    }
}t[10050];

map<string, int> mp; 
char a[10050], b[10050], c[10050];
int n;

int main() {
    int x, y;
    while(~scanf("%d", &n)) {
        mp.clear();
        int cnt = 0;
        for(int i = 0; i < 10050; i++) {
            t[i].kick = t[i].lost = t[i].score = 0;
            t[i].id = i;
        }
        for(int i = 0; i < n * (n - 1); i++) {
            scanf("%s%s%s%d:%d", a, c, b, &x, &y);
            if(mp.find((string)a) == mp.end()) name[cnt] = (string)a, mp[a] = cnt++;
            if(mp.find((string)b) == mp.end()) name[cnt] = (string)b, mp[b] = cnt++;
            int t1 = mp[(string)a], t2 = mp[(string)b];
            t[t1].kick += x, t[t1].lost += y;
            t[t2].kick += y, t[t2].lost += x;
            if(x < y) t[t2].score += 3;
            else if(x > y) t[t1].score += 3;
            else t[t1].score += 1, t[t2].score += 1;
        }
        sort(t, t + n);
        for(int i = 0; i < n; i++) {
            printf("%s %d\n", name[t[i].id].c_str(), t[i].score);
        }
        printf("\n");

    }
    return 0;
}
