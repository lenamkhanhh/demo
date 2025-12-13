
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
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m;
int t[N];
int l[N], r[N];

namespace sub1{
    int L[N], R[N];
    int b[N], ans[N], pref[N];
    void solve(){
        int res = 0;
        FOR(i, 1, m){
            L[i] = lower_bound(t+1, t+n+1, l[i]) - t;
            R[i] = upper_bound(t+1, t+n+1, r[i]) - t - 1;
        }

        F0R(mask, MASK(n)){
            F0R(i, n) b[i+1] = (BIT(mask, i) ? 1 : 2);
            FOR(i, 1, n) pref[i] = pref[i-1] + (b[i] == 1);
            int cnt = 0, i1 = 0, i2 = 0;
            FOR(i, 1, m){
                int i1 = L[i], i2 = R[i];
                if(i1 <= i2){
                    int k = pref[i2] - pref[i1-1];
                    int L = i2 - i1 + 1;
                    if(abs(2*k - L) <= 1) ++cnt;
                }
            }
            if(ckmax(res, cnt)) FOR(i, 1, n) ans[i] = b[i];
        }
        cout << res << '\n';
        FOR(i, 1, n) cout << (ans[i] == 1 ? "S" : "C");
    }
}

namespace sub2{
    bool check(){
        FOR(i, 1, m-1) if(r[i] >= l[i+1]) return false;
        return true;
    }

    void solve(){
        cout << m << '\n';
        int i1 = 0, i2 = 0;
        FOR(i, 1, m){
            while(i2 < n && t[i2+1] <= r[i]) ++i2;
            while(i1 <= n && t[i1] < l[i]) ++i1;
            if(i1 <= i2){
                int k = (i2 - i1 + 1) / 2;
                FOR(j, i1, i1+k-1) cout << "S";
                FOR(j, i1+k, i2) cout << "C";
            }
        }
        cout << '\n';
        exit(0);
    }
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, n) cin >> t[i];
    FOR(i, 1, m) cin >> l[i] >> r[i];
    sort(t+1, t+n+1);
    if(sub2::check()) sub2::solve();
    if(n <= 20) sub1::solve();
}

signed main(void){
    #define TASK "tea"
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
