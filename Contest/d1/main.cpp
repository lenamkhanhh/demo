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
const int N = 4e3 + 10, M = 20;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m;
struct Egde{
    int u, v;
};
vector<Egde> e;
vector<int> adj[N];

void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

namespace sub1{
    bool mark[N][N];
    void solve(){
        for(auto &[u, v] : e) mark[u][v] = mark[v][u] = true;
        vector<int> X;
        FOR(i, 1, n) X.push_back(i);
        do{
            bool flag = true;
            F0R(i, n-1){
                int u = X[i], v = X[i+1];
//                if(mark[u][v] == true)
            }
        }while(next_permutation(all(X)));
    }
}

namespace sub2{
    int F[N][N], G[N][N];

    void dfs(int u, int p = -1){
        F[u][1] = 1;
        for(int v : adj[u]) if(v != p){
            dfs(v, u);
            FOR(i, 2, n) add(F[u][i], F[v][i-1]);
        }
    }

    void DFS(int u, int p = -1){
        for(int v : adj[u]) if(v != p){
            FOR(i, 2, n){
                G[v][i] = G[u][i-1];
                add(G[v][i], F[u][i-1]);
                add(G[v][i], MOD - F[v][i-2]);
            }
            DFS(v, u);
        }
    }

    void solve(){
        for(auto &[u, v] : e){
            adj[u].pb(v);
            adj[v].pb(u);
        }

        FOR(u, 1, n) if(F[u][1] == 0){
            dfs(u);
            DFS(u);
        }

        FOR(k, 1, n){
            int res = 0;
            FOR(u, 1, n){
                add(res, F[u][k]);
                add(res, G[u][k]);
            }
            cout << res << " \n"[k == n];
        }
    }
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, m){
        int u, v; cin >> u >> v;
        e.push_back({u, v});
    }
    if(n <= 10) sub1::solve();
    sub2::solve();
}

signed main(void){
    #define TASK "nhap"
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

