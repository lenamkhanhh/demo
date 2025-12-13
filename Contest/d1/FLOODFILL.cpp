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
const int N = 1e3 + 10, M = 1e4 + 10;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

#define int long long
int n, L, r, tms;
int F[N][10*N];
int w[N], T[N], deg[N];
int num[N], tail[N], id[N];
vector<int> adj[N];

void sol(void){
    cin >> n >> L >> r;
    FOR(i, 1, n){
        int m; cin >> m;
        cin >> w[i] >> T[i];
        while(m--){
            int u; cin >> u;
            adj[i].pb(u);
            adj[u].pb(i);
        }
    }

    function<void(int, int)> dfs = [&](int u, int p){
        num[u] = ++tms; id[tms] = u;
        for(int v : adj[u]) if(v != p){
            dfs(v, u);
            w[u] += w[v];
            T[u] += T[v];
        }
        tail[u] = tms;
    };
    dfs(r, -1);
    if(T[r] < L) return void(cout << -1 << '\n');

    memset(F, 0x3f, sizeof(F)); F[0][0] = 0;
    for(int d = n; d >= 1; d--){
        int u = id[d], v = id[tail[u]+1];
        FOR(i, 0, L) F[u][min(L,i+T[u])] = min(F[u][min(L,i+T[u])], F[v][i] + w[u]);

        v = id[num[u]+1];
        FOR(i, 0, L) F[u][i] = min(F[u][i], F[v][i]);
        for(int i = L; i >= 0; i--) F[u][i] = min(F[u][i], F[u][i+1]);
    }
    cout << F[r][L] << '\n';
}

signed main(void){
    #define TASK "floodfill"
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

