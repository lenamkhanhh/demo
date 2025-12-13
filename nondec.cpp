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
const int N = 5e4 + 10, M = 21;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q, k;
int A[N], L[5*N], R[5*N];
int Tol[M], F[N][M], sum[M][M];
int res[5*N], FL[N], FR[N];
int suf[N][M], pref[N][M];

void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

void cdq(int l, int r, vector<int> v){
    if(l == r) return;
    int m = (l + r) >> 1;

    FOR(i, l, r){
        FL[i] = FR[i] = 0;
        FOR(j, 1, k) F[i][j] = suf[i][j] = pref[i][j] = 0;
    }
    FOR(i, 1, k){
        Tol[i] = 0;
        FOR(j, 1, k) sum[i][j] = 0;
    }
    for(int i = m; i >= l; i--){
        FL[i] = 1;
        FOR(x, A[i], k) add(FL[i], Tol[x]);
        add(Tol[A[i]], FL[i]);
        add(FL[i], FL[i+1]);

        F[i][A[i]] = 1;
        FOR(x, A[i], k) FOR(y, A[i], x) add(F[i][x], sum[y][x]);
        FOR(x, A[i], k) add(sum[A[i]][x], F[i][x]);
        FOR(x, 1, k) FOR(y, 1, x) add(suf[i][x], sum[y][x]);
    }

    FOR(i, 1, k){
        Tol[i] = 0;
        FOR(j, 1, k) sum[i][j] = 0;
    }
    for(int i = m+1; i <= r; i++){
        FR[i] = 1;
        FOR(x, 1, A[i]) add(FR[i], Tol[x]);
        add(Tol[A[i]], FR[i]);
        add(FR[i], FR[i-1]);

        F[i][A[i]] = 1;
        FOR(x, 1, A[i]) FOR(y, x, A[i]) add(F[i][x], sum[x][y]);
        FOR(x, 1, A[i]) add(sum[x][A[i]], F[i][x]);
        FOR(x, 1, k) FOR(y, x, k) add(pref[i][x], sum[x][y]);
        for(int x = k-1; x >= 1; x--) add(pref[i][x], pref[i][x+1]);
    }

    vector<int> left, right;
    for(int id : v){
        if(R[id] <= m) left.push_back(id);
        else if(L[id] >= m+1) right.push_back(id);
        else{
            int u = L[id], v = R[id];
            res[id] = FL[u] + FR[v];
            if(res[id] >= MOD) res[id] -= MOD;
            FOR(x, 1, k) add(res[id], 1LL * suf[u][x] * pref[v][x] % MOD);
        }
    }
    cdq(l, m, left); cdq(m+1, r, right);
}

void sol(void){
    cin >> n >> k;
    FOR(i, 1, n) cin >> A[i];

    cin >> q;
    vector<int> v;
    FOR(i, 1, q){
        cin >> L[i] >> R[i];
        if(L[i] == R[i]) res[i] = 1;
        else v.pb(i);
    }
    cdq(1, n, v);
    FOR(i, 1, q) add(res[i], 1);
    FOR(i, 1, q) cout << res[i] << '\n';
}

signed main(void){
    #define TASK "nondec"
    if(fopen(TASK".in", "r")){
        freopen(TASK".in", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
//    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}
