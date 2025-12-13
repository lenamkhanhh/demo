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

int n, m, k;
int c[N];
struct Egde{
    int u, v, w;
    bool operator < (const Egde &p) const{
        return w < p.w;
    }
};
vector<Egde> e;
int par[N];

int Find(int v){
    return par[v] < 0 ? v : par[v] = Find(par[v]);
}

bool Union(int u, int v){
    if((u = Find(u)) == (v = Find(v))) return false;
    if(par[u] > par[v]) swap(u, v);
    par[u] += par[v], par[v] = u;
    return true;
}

namespace sub1{
    void solve(){
        for(auto &[u, v, w] : e){
            if(c[u] > c[v]) swap(u, v);
            cout << (c[u] == 1 && c[v] == 2 ? w : -1) << '\n';
        }
    }
}

namespace sub2{
    bool check(){
        FOR(i, 1, n) if(c[i] != i) return false;
        return true;
    }
    void solve(){
        long long res = 0, cnt = 0;
        FOR(i, 1, n) par[i] = -1;
        for(auto &[u, v, w] : e) if(Union(u, v)){
            ++cnt;
            res += w;
        }
        cout << (cnt < k-1 ? -1 : res) << '\n';
    }
}

namespace sub3{
    int T[N];
    long long res;
    vector<Egde> tmp;

    bool check(){
        int cnt = 0;
        FOR(i, 1, n) if(c[i] == 0) ++cnt;
        return cnt <= 7;
    }

    void dq(int i){
        if(i > n){
            FOR(i, 1, k) par[i] = -1;
            tmp.clear();
            for(auto [u, v, w] : e) if(T[u] != T[v]) tmp.push_back({T[u], T[v], w});
            sort(all(tmp));

            long long sum = 0, cnt = 0;
            for(auto [u, v, w] : tmp) if(Union(u, v)) sum += w, cnt += 1;
            if(cnt == k-1) res = min(res, sum);
            return;
        }
        if(c[i] == 0){
            FOR(col, 1, k){
                T[i] = col;
                dq(i+1);
            }
        }
        else dq(i+1);
    }

    void solve(){
        res = INF;
        FOR(i, 1, n) T[i] = c[i];
        dq(1);
        cout << (res == INF ? -1 : res) << '\n';
    }
}

namespace sub4{
    bool check(){
        FOR(i, 1, n) if(c[i] == 0) return false;
        return true;
    }
    void solve(){

    }
}

namespace sub{
    void solve(){

    }
}

void sol(void){
    cin >> n >> m >> k;
    e.clear();
    FOR(i, 1, n) cin >> c[i];
    FOR(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        if(max(c[u], c[v]) <= k) e.push_back({u, v, w});
    }
    sort(all(e));
    if(k > n) return void(cout << -1 << '\n');
    if(n == 1 || k == 1) return void(cout << 0 << '\n');

    if(n == 2 && m == 1) sub1::solve();
    else if(sub2::check()) sub2::solve();
    else sub3::solve();
}

signed main(void){
    #define TASK "GRAPHZIP"
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
