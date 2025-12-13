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
const int N = 2e5 + 10, M = 21;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, k;
int A[N];
namespace sub1{
    long long F[5007][5007][2];
    void solve(){
        memset(F, 0x3f, sizeof(F)); F[0][0][0] = 0;
        FOR(i, 1, n) FOR(j, 0, k){
            F[i][j][0] = min(F[i-1][j][0], F[i-1][j][1]);
            if(i > 1 && j > 0) F[i][j][1] = min(F[i][j][0], F[i-1][j-1][0] + A[i] - A[i-1]);
        }
        cout << min(F[n][k][0], F[n][k][1]) << '\n';
        exit(0);
    }
}

namespace sub{
    struct Dta{
        int l, r, diff;
        bool operator < (const Dta &p) const{
            return diff > p.diff;
        }
    };
    priority_queue<Dta> pq;
    bool mark[N];
    int res;
    int L[N], R[N], par[N], sum[N][2];

    int Find(int v){
        return par[v] < 0 ? v : par[v] = Find(par[v]);
    }

    void Union(int u, int v){
        u = Find(u), v = Find(v);
        if((-par[u]) & 1 || (-par[v]) & 1) return;
        if(par[u] > par[v]) swap(u, v);
        par[u] += par[v], par[v] = u;
        sum[u][0] += sum[v][0];
        sum[u][1] += sum[v][1];
    }

    void Merge(int u, int v){
        if(u+1 == v){
            par[u] += par[v], par[v] = u;
            sum[u][1] = A[u], sum[u][0] = A[v];
        }
        else{
            int x = Find(u+1), siz = -par[x];
            res -= sum[x][0] - sum[x][1];

            sum[x][(siz+1)&1] += A[v];
            swap(sum[x][0], sum[x][1]);
            sum[x][1] += A[u];

            par[x] += par[u] + par[v];
            par[u] = par[v] = x;
        }
        res += sum[Find(u)][0] - sum[Find(u)][1];

        if(u > 1) Union(u-1, u);
        if(v < n) Union(v, v+1);

        int x = L[u], y = R[v];
        if(x > 0 && y > 0){
            R[x] = y, L[y] = x;
            int z = Find(u);
            pq.push({x, y, 2*(sum[z][1] - sum[z][0]) + A[y] - A[x]});
        }
    }

    void solve(){
        FOR(i, 1, n){
            if(i > 1) L[i] = i-1;
            if(i < n) R[i] = i+1;
        }
        FOR(i, 2, n) pq.push({i-1, i, A[i] - A[i-1]});
        memset(par, -1, sizeof(par));
        while(sz(pq)){
            int l = pq.top().l;
            int r = pq.top().r;
            int diff = pq.top().diff;
            pq.pop();
            if(mark[l] || mark[r]) continue;
            mark[l] = mark[r] = true;
            if(k-- == 0) break;
            Merge(l, r);
        }
        cout << res << '\n';
    }
}

void sol(void){
    cin >> n >> k;
    FOR(i, 1, n) cin >> A[i];
    sort(A+1,A+n+1);
//    FOR(i, 1, n) cout << A[i] << " \n"[i == n];
//    if(n <= 5e3) sub1::solve();
    sub::solve();
}

signed main(void){
    #define TASK "dan"
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

