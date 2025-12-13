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

#define int long long
int n;
int x[N];
int L, radius;

namespace sub{
    int pref[N], cnt[N];
    int mL[N], mR[N];
    void solve(){
        FOR(i, 1, n){
            mL[i] = -1;
            mR[i] = MOD;
        }
        int lst = L;
        for(int i = n; i >= 1; i--){
            int l = x[i] - radius, r = x[i] + radius;
            if(r < lst) break;
            mL[i] = l;
        }

        lst = 0;
        for(int i = 1; i <= n; i++){
            int l = x[i] - radius, r = x[i] + radius;
            if(lst < l) break;
            mR[i] = r;
        }

        int res = INF;
        FOR(r, 1, n) for(int l = r; l >= 1; l--){
            if(0 <= mR[l-1] && mL[r+1] <= L){
                int LEN = mL[r+1] - mR[l-1] - 1;
                if(1LL * (r-l+1) * (2LL * radius + 1) < LEN) continue;

                bool goL = (mR[l-1] < x[l] - radius);
                bool goR = (x[r] + radius < mL[r+1]);

                int lst = mR[l-1];
                bool onlyR = true;
                FOR(i, l, r){
                    int pL = x[i] - radius, pR = x[i] + radius;
                    if(lst < pL) onlyR = false;
                    lst = pR;
                }
                if(goL == false && goR && onlyR && mL[r+1] <= lst) res = min(res, x[r]);

                // -------------------------- //
                if(goL == false && goR == true) res = min(res, mL[r+1] - 2 * radius - 1);
            }
        }
        cout << res << '\n';
    }
}

void sol(void){
    cin >> n >> L >> radius;
    FOR(i, 1, n) cin >> x[i];
    if(1LL * n * (2LL * radius + 1) < L+1) return void(cout << -1 << '\n');
    sub::solve();
}

signed main(void){
    #define TASK "robot"
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
