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
const int N = 5e5 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m, k;
multiset<ii> s;
struct client{
    int c, v;
    bool operator < (const client &p) const{
        return c != p.c ? c > p.c : v > p.v;
    }
}A[N];
vector<int> ans;

void sol(void){
    cin >> n >> m >> k;
    FOR(i, 1, n){
        int c, v; cin >> c >> v;
        s.insert(ii(v, c));
    }
    FOR(i, 1, m){
        int c, v; cin >> c >> v;
        A[i] = {c, v};
    }
    sort(A+1,A+m+1);
    for(int i = 1; i <= m; i++){
        auto &[c, v] = A[i];
        auto it = s.lower_bound(ii(v, 0));
        if(it == s.end()) continue;

        long long profit = c - it->se;
        if(profit <= 0) continue;
        ans.push_back(c - it->se);
        s.erase(it);
    }
    sort(all(ans));
    long long res = 0;
    for(int i = sz(ans)-1; i >= max(0, sz(ans)-k); i--) res += ans[i];
    cout << res << '\n';
}

signed main(void){
    #define TASK "HOTEL"
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
