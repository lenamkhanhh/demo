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
const int N = 3e5 + 10, M = 20;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m, tms;
int s[N], ord[N];
int num[N], tp[N], par[N];
int lzCnt[MASK(M)];
long long A[N], lzW[MASK(M)], res[N];
vector<int> adj[N];
struct Egde{
    int s, t, w;
    bool operator < (const Egde &p) const{
        return w > p.w;
    }
}e[N];

void dfs(int u, int p = -1){
    s[u] = 1;
    for(int v : adj[u]) if(v != p){
        dfs(v, u);
        s[u] += s[v];
    }
}

void hld(int u, int p, int top){
//    cout << u << ' ';
    int mx = -1, bigC = -1;
    tp[u] = top, par[u] = p, num[u] = ++tms;
    for(int v : adj[u]) if(v != p && ckmax(mx, s[v])) bigC = v;
    if(bigC != -1) hld(bigC, u, top);
    for(int v : adj[u]) if(v != p && v != bigC) hld(v, u, v);
}

void fixed(int i){
    long long &d1 = lzW[i];
    int &d2 = lzCnt[i];
    if(d1 == 0 && d2 == 0) return;
    lzW[i<<1] += d1, lzCnt[i<<1] += d2;
    lzW[i<<1|1] += d1, lzCnt[i<<1|1] += d2;
    d1 = d2 = 0;
}

int query(int i, int l, int r, int id){
    int p = num[id];
    while(l < r){
        fixed(i);
        int m = (l + r) >> 1;
        if(p <= m) r = m, i = i<<1;
        else l = m+1, i = i<<1|1;
    }
    return lzW[i] - A[id] * lzCnt[i];
}

void update(int i, int l, int r, int u, int v, int w){
    if(r < u || v < l) return;
    if(u <= l && r <= v){
        lzCnt[i]++;
        lzW[i] += w;
        return;
    }
    fixed(i);
    int m = (l + r) >> 1;
    update(i<<1, l, m, u, v, w);
    update(i<<1|1, m+1, r, u, v, w);
}

void update(int u, int v, int w){
    while(num[tp[u]] != num[tp[v]]){
        if(num[tp[u]] < num[tp[v]]) swap(u, v);
        update(1, 1, n, num[tp[u]], num[u], w);
        u = par[tp[u]];
    }
    if(num[u] > num[v]) swap(u, v);
    update(1, 1, n, num[u], num[v], w);
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, n-1){
        int u, v; cin >> u >> v;
        adj[u].pb(v), adj[v].pb(u);
    }
    FOR(i, 1, n) cin >> A[i];
    dfs(1); hld(1, 0, 1);

    FOR(i, 1, n) ord[i] = i;
    sort(ord+1,ord+n+1, [&](const int &x, const int &y){
         return A[x] > A[y];
    });
    FOR(i, 1, m){
        int s, t, w; cin >> s >> t >> w;
        e[i] = {s, t, w};
    }

    sort(e+1,e+m+1);
    int j = 1;
    FOR(i, 1, m){
        int s = e[i].s, t = e[i].t, w = e[i].w;
        while(j <= n && A[ord[j]] >= w){
            res[ord[j]] = query(1, 1, n, ord[j]);
            j++;
        }
        update(s, t, w);
    }
    while(j <= n){
        res[ord[j]] = query(1, 1, n, ord[j]);
        j++;
    }
    FOR(i, 1, n) cout << res[i] << ' ';
}

signed main(void){
    #define TASK "tree"
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

