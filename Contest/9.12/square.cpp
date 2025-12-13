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

const int MOD = (int)1e9 + 9999;
const int mod = 998244353;
const int N = 1e5 + 10, M = 21;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m, k;
struct Dta{
    int x, y, v;
};
vector<Dta> ban;
void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

namespace sub1{
    ii e[N];
    int T[M][M];
    void solve(){
        int L = n * m;
        int idx = 0, res = 0;
        FOR(i, 1, n) FOR(j, 1, m) e[idx++] = ii(i, j);
        F0R(mask, MASK(L)){
            F0R(i, L) T[e[i].fi][e[i].se] = BIT(mask, i);
            bool flag = true;
            for(auto &[x, y, v] : ban) if(T[x][y] != v) flag = false;
            FOR(i, 2, n) FOR(j, 2, m){
                int num = T[i-1][j-1] + T[i][j] + T[i][j-1] + T[i][j];
                if(num & 1) flag = false;
            }
            res += flag;
        }
        cout << res << '\n';
        exit(0);
    }
}

namespace sub2{
    int Pow(int a, int b){
        int res = 1;
        for(; b > 0; b >>= 1, a = 1LL * a * a % MOD) if(b & 1) res = 1LL * res * a % MOD;
        return res;
    }
    void solve(){
        cout << Pow(2, n+m-1) << '\n';
        exit(0);
    }
}

namespace sub3{
    int F[1001][MASK(12)];
    vector<ii> row[1001];
    vector<int> adj[MASK(12)];

    bool check(int mask1, int mask2){
        FOR(i, 1, m-1){
            int sum = BIT(mask1, i-1) + BIT(mask1, i) + BIT(mask2, i-1) + BIT(mask2, i);
            if(sum & 1) return false;
        }
        return true;
    }

    void solve(){
        for(auto &[x, y, v] : ban) row[x].push_back({y, v});
        F0R(mask, MASK(m)) F0R(nxt_mask, MASK(m)) if(check(mask, nxt_mask)) adj[mask].push_back(nxt_mask);
        F0R(mask, MASK(m)){
            bool flag = true;
            for(auto [y, v] : row[1]) if(BIT(mask, y-1) != v) flag = false;
            F[1][mask] = flag;
        }
        FOR(i, 2, n){
            F0R(mask, MASK(m)) if(F[i-1][mask] > 0){
                for(int nxt_mask : adj[mask]){
                    bool flag = true;
                    for(auto [y, v] : row[i]) if(BIT(nxt_mask, y-1) != v) flag = false;
                    if(flag == false) continue;
                    add(F[i][nxt_mask], F[i-1][mask]);
                }
            }
        }
        int res = 0;
        F0R(mask, MASK(m)) add(res, F[n][mask]);
        cout << res << '\n';
    }
}

void sol(void){
    cin >> n >> m >> k;
    FOR(i, 1, k){
        int x, y, v; cin >> x >> y >> v;
        ban.push_back({x, y, v});
    }
    if(1LL * n * m <= 20) sub1::solve();
    if(k == 0) sub2::solve();
    sub3::solve();
}

signed main(void){
    #define TASK "square"
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
