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
const int N = 2e5 + 10, M = 18;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n;
int h[N], w[N];

#define C(x) (1LL * (x) * (x+1) / 2 % MOD)
void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

int Pow(int a, int b){
    int res = 1;
    for(; b > 0; b >>= 1, a = 1LL * a * a % MOD) if(b & 1) res = 1LL * res * a % MOD;
    return res;
}

namespace sub1{
    bool check(){
        FOR(i, 1, n-1) if(h[i] != h[i+1]) return false;
        return true;
    }

    void solve(){
        long long sumW = 0;
        FOR(i, 1, n) sumW += w[i];
        long long x = sumW % MOD;
        long long y = (sumW + 1) % MOD;
        int res = 1LL * x * y % MOD * Pow(2, MOD-2) % MOD;
        res = 1LL * res * C(h[1]) % MOD;
        cout << res << '\n';
        exit(0);
    }
}

namespace sub2{
    bool check(){
        FOR(i, 1, n-1) if(h[i] > h[i+1]) return false;
        return true;
    }

    void solve(){
        int res = 0;
        long long sumW = 0;
        for(int i = n; i >= 1; i--){
            add(res, 1LL * C(h[i]) * C(w[i]) % MOD);
            add(res, 1LL * C(h[i]) * w[i] % MOD * (sumW % MOD) % MOD);
            sumW += w[i];
        }
        cout << res << '\n';
        exit(0);
    }
}

namespace sub{
    void solve(){
        int res = 0;
        FOR(i, 1, n){
            int minH = h[i];
            add(res, (1LL * C(minH) * C(w[i]) % MOD));
            for(int j = i-1; j >= 1; j--){
                minH = min(minH, h[j]);
                add(res, 1LL * C(minH) * w[i] % MOD * w[j] % MOD);
            }
        }
        cout << res << '\n';
        exit(0);
    }
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) cin >> h[i];
    FOR(i, 1, n) cin >> w[i];
//    if(sub1::check()) sub1::solve();
    if(sub2::check()) sub2::solve();
    sub::solve();
}

signed main(void){
    #define TASK "rect"
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

