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

const int MOD = (int)1e9 + 22071997;
const int mod = 998244353;
const int N = 2e5 + 10, M = 18;
const long long INF = (long long)1e9 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

long long Pow(long long a, long long b){
    long long res = 1;
    for(; b > 0; b >>= 1, a = min(a * a, INF)) if(b & 1) res = min(INF, res * a);
    return res;
}

int divs[N];

void solve(void){
    int n; cin >> n;
    int idx = 0;
    long long res = (n-1) / 2;
    for(int i = 1; i*i <= n; i++) if(n % i == 0){
        divs[++idx] = i;
        if(i != n/i) divs[++idx] = n/i;
    }

    FOR(i, 1, idx){
        int X = n / divs[i];
        for(int d = 3; d <= 25; d++){
            int l = 2, r = X, q = -1;
            while(l <= r){
                int m = (l + r + 1) >> 1;
                long long T = Pow(m, d);
                if(T == INF || T-1 > X * (m-1)) r = m-1;
                else l = m+1, q = m;
            }
            if(q > 1 && Pow(q, d) - 1 == X * (q-1)){
//                cout << divs[i] << ' ' << q << ' ' << d << ' ' << X << '\n';
                res++;
            }
        }
    }
    cout << res << ' ';
}

void sol(void){
    int q; cin >> q;
    while(q--) solve();
}

signed main(void){
    #define TASK "GEOMETRIC"
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

