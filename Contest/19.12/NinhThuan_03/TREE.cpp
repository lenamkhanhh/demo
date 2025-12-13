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
const int N = 1e5 + 10, M = 19;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q;
int A[N];
int h[N], up[N][M];
vector<int> adj[N];

void DFS(int u, int p = -1){
    for(int v : adj[u]) if(v != p){
        h[v] = h[u] + 1, up[v][0] = u;
        FOR(i, 1, __lg(h[v])) up[v][i] = up[up[v][i-1]][i-1];
        DFS(v, u);
    }
}

int lca(int u, int v){
    if(h[u] != h[v]){
        if(h[u] < h[v]) swap(u, v);
        int k = h[u] - h[v];
        F0Rd(i, __lg(k)+1) if((k >> i) & 1) u = up[u][i];
    }
    if(u == v) return u;
    F0Rd(i, __lg(h[u])+1) if(up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
    return up[u][0];
}


namespace sub1{
    int tp[N];
    int T[N][M];
    void dfs(int u, int p = -1){
        if(tp[u] == 0) tp[u] = u;
        for(int v : adj[u]) if(v != p){
            if(A[u] == A[v]) tp[v] = tp[u];
            else{
                T[v][0] = u;
                tp[v] = v;
                FOR(i, 1, __lg(h[v])) T[v][i] = T[T[v][i-1]][i-1];
            }
            dfs(v, u);
        }
    }
    void solve(){
        dfs(1);
        while(q--){
            int u, v; cin >> u >> v;
            int p = lca(u, v);
            if(A[u] == 2) u = T[u][0];
            if(A[v] == 2) v = T[v][0];
            if(h[u] < h[p]) u = p;
            if(h[v] < h[p]) v = p;

            int res = 0;
            F0Rd(i, M){
                int x = T[u][i];
                if(x == 0) continue;
                if(h[x] < h[p]) break;
                res += MASK(i);
                u = x;
            }

            F0Rd(i, M){
                int x = T[v][i];
                if(x == 0) continue;
                if(h[x] < h[p]) break;
                res += MASK(i);
                v = x;
            }
            cout << res+1 << '\n';
        }
    }
}

void sol(void){
    cin >> n >> q;
    FOR(i, 1, n) cin >> A[i];
    FOR(i, 1, n-1){
        int u, v; cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    DFS(1);
    sub1::solve();
}

signed main(void){
    #define TASK "TREE"
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


