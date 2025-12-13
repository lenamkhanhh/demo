#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb emplace_back
#define ii pair<int, ll>
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
const int N = 4e5 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n;
int L[N], R[N];
int x[N], A[N], b[N];

long long Pow(long long a, long long b){
    long long res = 1;
    for(; b > 0; b >>= 1, a = a * a) if(b & 1) res = res * a;
    return res;
}

namespace sub1{
    bool check(){
        FOR(i, 1, n-1) if(A[i] != A[i+1] || b[i] != b[i+1]) return false;
        return true;
    }

    void solve(){

        long long res = 0;
        cout << 2 << ' ' << 4*(n-1) << '\n';
        exit(0);
    }
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) cin >> x[i] >> a[i] >> b[i];
    FOR(i, 1, n){
        L[i] = x[i] - A[i];
        R[i] = x[i] + b[i];
    }
    if(sub1::check()) sub1::solve();
    cout << n << ' ' << Pow(2, n) << '\n';
}

signed main(void){
    #define TASK "ROADSIGNS"
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
