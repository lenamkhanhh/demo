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
const int N = 1e5 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m, q, tms;
bool mark[N];
int h[N], up[N][M];
int num[N], tail[N], low[N];
vector<int> adj[N];

void dfs(int u, int p = -1){
    int child = 0;
    num[u] = low[u] = ++tms;
    for(int v : adj[u]) if(v != p){
        if(num[v] == 0){
            h[v] = h[u] + 1, up[v][0] = u;
            FOR(i, 1, __lg(h[v])) up[v][i] = up[up[v][i-1]][i-1];
//            cout << u << ' ' << v << '\n';
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
        if(p != -1 && num[u] <= low[v]) mark[u] = true;
        ++child;
    }
    tail[u] = tms;
    if(p == -1 && child > 1) mark[u] = true;
}

bool subtree(int u, int v){
    return num[u] <= num[v] && num[v] <= tail[u];
}

bool query1(int a, int b, int g1, int g2){
    if(num[g1] > num[g2]) swap(g1, g2);
    if(num[g1] >= low[g2]) return true;
    return (subtree(g2, a) ^ subtree(g2, b) == false);
}

int Jump(int u, int k){
    if(k < 0) return 0;
    for(int i = __lg(h[u]); i >= 0; i--) if((k >> i) & 1) u = up[u][i];
    return u;
}

bool query2(int a, int b, int c){
    if(mark[c] == false) return true;
    bool mark1 = subtree(c, a), mark2 = subtree(c, b);
    int s = Jump(a, h[a] - h[c] - 1);
    int t = Jump(b, h[b] - h[c] - 1);

    if(mark1 == false && mark2 == false) return true;
    if(mark1 == false && num[c] > low[t]) return true;
    if(num[c] > low[s] && mark2 == false) return true;
    if(mark1 == true && mark2 == true && num[c] > max(low[s], low[t])) return true;
    return s == t;
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, m){
        int u, v; cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    dfs(1);
    cin >> q;
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int a, b, c, d; cin >> a >> b >> c >> d;
            cout << (query1(a, b, c, d) ? "DA" : "NE") << '\n';
        }
        else{
            int a, b, c; cin >> a >> b >> c;
            cout << (query2(a, b, c) ? "DA" : "NE") << '\n';
        }
    }
}

signed main(void){
    #define TASK "POLICIJA"
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
