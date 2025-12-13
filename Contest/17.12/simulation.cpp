#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb emplace_back
#define ii pair<int, int>
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define sz(s) (int)((s).size())
#define all(a) a.begin(), a.end()
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define F0R(i, b) for (int i = 0, _b = (b); i < _b; ++i)
#define FORd(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define F0Rd(i, b) for (int i = (b)-1; i >= 0; i--)
#define debug(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
using namespace std;

template<typename T1,typename T2> bool ckmax(T1 &x,const T2 &y){if(x<y){x=y; return 1;} return 0;}
template<typename T1,typename T2> bool ckmin(T1 &x,const T2 &y){if(y<x){x=y; return 1;} return 0;}

const int MOD = (int)1e9 + 7;
const int mod = 998244353;
const int N = 3e5 + 10, M = 18;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q;
ii A[N];
struct Query{
    char ch;
    int i, x, y;
    Query(){
        ch = 'A';
        i = x = y = 0;
    }
    void out(){
        cout << ch << ' ' << i << ' ' << x << ' ' << y << '\n';
    }
}Q[N];

namespace sub1{
    int res;
    int X[N], Y[N];

    void rebuild(void){
        res = 0;
        F0R(i, n){
            res += bool(1LL * X[i] * X[i+1] < 0);
            res += bool(1LL * Y[i] * Y[i+1] < 0);
        }
//        cout << "----\n";
//        FOR(i, 0, n) cout << X[i] << ' ' << Y[i] << '\n';
    }

    void solve(){
        X[0] = Y[0] = 1;
        FOR(i, 1, n){
            X[i] = X[i-1] + A[i].fi;
            Y[i] = Y[i-1] + A[i].se;
        }

        rebuild();
        FOR(i, 1, q){
            auto &[ch, id, x, y] = Q[i];
            if(ch == 'Q') cout << res << '\n';
            else{
                int dx = x - A[id].fi;
                int dy = y - A[id].se;
                A[id] = ii(x, y);
                FOR(j, id, n) X[j] += dx, Y[j] += dy;
                rebuild();
            }
        }
    }
}

namespace sub{
    void solve(){

    }
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) cin >> A[i].fi >> A[i].se;

    int m = 0, idx = 1;
    cin >> q;
    while(q--){
        char ch; cin >> ch;
        if(ch == 'Q') Q[++m].ch = 'Q';
        if(ch == 'F') idx += bool(idx < n);
        if(ch == 'B') idx -= bool(idx > 1);
        if(ch == 'C'){
            Q[++m].ch = 'C';
            int nx, ny; cin >> nx >> ny;
            Q[m].i = idx, Q[m].x = nx, Q[m].y = ny;
        }
    }
    q = m;
    sub1::solve();
}

signed main(void){
    #define TASK "simulation"
    if(fopen(TASK".inp", "r")){
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
//    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}

