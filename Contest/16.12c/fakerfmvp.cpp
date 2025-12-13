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

int n, m, k, SCC;
struct Egde{
    int u, v;
};
vector<Egde> e1, e2;
int F[N], G[N];
int scc[N], deg[N];
bool Cycle;
queue<int> pq;
vector<int> topo;
vector<int> adj[N], g[N], group[N], d[N];

void dfs(int u, int p = -1){
    if(scc[u] > 0){
        Cycle = true;
        return;
    }
    scc[u] = SCC;
    group[SCC].push_back(u);
    int cnt = 0;
    for(int v : adj[u]){
        if(v == p){
            ++cnt;
            continue;
        }
//        cout << u << ' ' << v << '\n';
        dfs(v, u);
    }
    if(cnt > 1) Cycle = true;
}

void update(int &b1, int &b2, const int v){
    if(v > b1) b2 = b1, b1 = v;
    else b2 = max(b2, v);
}

void dfs1(int u, int p = -1){
    for(int v : adj[u]) if(v != p){
//        cout << u << ' ' << v << '\n';
        dfs1(v, u);
        F[u] = max(F[u], F[v] + 1);
    }
    for(int v : d[u]) F[u] = max(F[u], F[v] + 1);
}

void dfs2(int u, int p = -1){
    int b1 = 0, b2 = 0;
    for(int v : adj[u]) if(v != p) update(b1, b2, F[v] + 1);
    for(int v : adj[u]) if(v != p){
        G[v] = max(G[u], b1 == F[v] + 1 ? b2 : b1) + 1;
        dfs2(v, u);
    }
}

void reset(void){
    SCC = 0;
    Cycle = false;
    e1.clear(); e2.clear(); topo.clear();
    while(sz(pq)) pq.pop();
    FOR(i, 1, n){
        F[i] = G[i] = scc[i] = deg[i] = 0;
        adj[i].clear(); d[i].clear();
        g[i].clear(); group[i].clear();
    }
}

void sol(void){
    cin >> n >> m >> k;
    reset();
    FOR(i, 1, m){
        int u, v; cin >> u >> v;
        e1.push_back({u, v});
    }
    FOR(i, 1, k){
        int u, v; cin >> u >> v;
        d[u].push_back(v);
        e2.push_back({u, v});
    }
    if(m > n-1) return void(cout << -1 << '\n');
    for(auto &[u, v] : e1){
        adj[u].pb(v);
        adj[v].pb(u);
    }
    FOR(i, 1, n) if(scc[i] == 0){
        SCC++;
        dfs(i);
    }
    if(Cycle == true) return void(cout << -1 << '\n');
    for(auto &[u, v] : e2){
        if(scc[u] == scc[v]) return void(cout << -1 << '\n');
        int x = scc[u], y = scc[v];
        g[y].push_back(x);
        deg[x]++;
    }
    FOR(i, 1, SCC) if(deg[i] == 0) pq.push(i);
    while(sz(pq)){
        int u = pq.front(); pq.pop();
        topo.push_back(u);
        for(int v : g[u]) if(--deg[v] == 0) pq.push(v);
    }
    if(sz(topo) < SCC) return void(cout << -1 << '\n');
    for(int id : topo){
//        cout << "----\n";
//        cout << id << ":\n";
        for(int u : group[id]){
            dfs1(u);
            dfs2(u);
            break;
        }
//        for(int u : group[id]) cout << u << ' ' << F[u] << ' ' << G[u] << '\n';
        for(int u : group[id]) F[u] = max(F[u], G[u]);
    }
    cout << *max_element(F+1,F+n+1)<< '\n';
}

signed main(void){
    #define TASK "fakerfmvp"
    if(fopen(TASK".inp", "r")){
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}
