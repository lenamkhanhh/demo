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

int n, k;
int A[N], L[N], R[N], cnt[N];
vector<int> v, g[N];

void sol(void){
    cin >> n >> k;
    FOR(i, 1, n){
        cin >> A[i];
        v.pb(A[i]);
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    FOR(i, 1, n){
        A[i] = lower_bound(all(v), A[i]) - v.begin() + 1;
        g[A[i]].push_back(i);
    }

    int res = 0;
    FOR(x, 1, sz(v)){
        int m = 0, l = 0;
        vector<int> &p = g[x];
        while(l < sz(p)){
            int s = 0;
            L[++m] = p[l];
            while(l+1 < sz(p) && p[l] + 1 == p[l+1]){
                l++;
            }
            R[m] = p[l];
            cnt[m] = R[m] - L[m] + 1;
            l++;
        }

        int s = 0, j = 1;
        FOR(i, 1, m){
            res = max(res, min(n, cnt[i] + k));
            s += cnt[i];
            while(j < i && R[i] - L[j] + 1 - s > k) s -= cnt[j++];
            res = max(res, min(n, s + k));
        }
    }
    cout << res << '\n';
}

signed main(void){
    #define TASK "seq"
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

