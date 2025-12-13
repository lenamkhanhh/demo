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

const int mod = 998244353;
const int N = 2024 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q, MOD;
int A[N];
int dp[N], F1[N][N], F2[N][N];

void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

void sub(int &x, const int &y){
    if((x -= y) < 0) x += MOD;
}

namespace case1{
    int comb[N][N];
    void precalc(){
        FOR(i, 0, n) FOR(j, i, n){
            if(i == 0 || i == j) comb[i][j] = 1;
            else comb[i][j] = (comb[i-1][j-1] + comb[i][j-1]) % MOD;
        }
    }

    namespace sub1{
        void solve(){
            F1[0][0] = 1;
            FOR(i, 1, n) FOR(j, 0, n)
                FOR(k, 0, j/i) add(F1[i][j], 1LL * F1[i-1][j-k*i] * comb[k][A[i]] % MOD);

            F2[n+1][0] = 1;
            for(int i = n; i >= 1; i--) FOR(j, 0, n)
                FOR(k, 0, j/i) add(F2[i][j], 1LL * F2[i+1][j-k*i] * comb[k][A[i]] % MOD);

            FOR(i, 1, q){
                int p, d, s; cin >> p >> d >> s;
                FOR(k, 0, s) dp[k] = 0;
                FOR(k1, 0, s) FOR(k2, 0, s-k1) if(k1 != 0 || k2 != 0)
                    add(dp[k1+k2], 1LL * F1[p-1][k1] * F2[p+1][k2] % MOD);

                dp[0] = 1;
                int res = 0;
                FOR(k, 0, s/p) add(res, 1LL * dp[s-k*p] * comb[k][A[p]-d]);
                cout << res << '\n';
            }
            exit(0);
        }
    }

    void solve(){
        precalc();
        sub1::solve();
    }
}

namespace case2{
    int F[N], IF[N];

    int Pow(int a, int b){
        int res = 1;
        for(; b > 0; b >>= 1, a = 1LL * a * a % MOD) if(b & 1) res = 1LL * res * a % MOD;
        return res;
    }

    void precalc(){
        F[0] = 1;
        FOR(i, 1, n) F[i] = 1LL * F[i-1] * i % MOD;
        IF[n] = Pow(F[n], MOD-2);
        F0Rd(i, n) IF[i] = IF[i+1] * (i+1) % MOD;
    }

    int C(int x, int y){
        return 1LL * F[y] * IF[y-x] % MOD * IF[x] % MOD;
    }

    namespace sub1{
        void solve(){
            F1[0][0] = 1;
            FOR(i, 1, n) FOR(j, 0, n)
                FOR(k, 0, j/i) add(F1[i][j], 1LL * F1[i-1][j-k*i] * C(k, A[i]) % MOD);

            F2[n+1][0] = 1;
            for(int i = n; i >= 1; i--) FOR(j, 0, n)
                FOR(k, 0, j/i) add(F2[i][j], 1LL * F2[i+1][j-k*i] * C(k, A[i]) % MOD);

            FOR(i, 1, q){
                int p, d, s; cin >> p >> d >> s;
                FOR(k, 0, s) dp[k] = 0;
                FOR(k1, 0, s) FOR(k2, 0, s-k1) if(k1 != 0 || k2 != 0)
                    add(dp[k1+k2], 1LL * F1[p-1][k1] * F2[p+1][k2] % MOD);

                dp[0] = 1;
                int res = 0;
                FOR(k, 0, s/p) add(res, 1LL * dp[s-k*p] * C(k, A[p]-d));
                cout << res << '\n';
            }
            exit(0);
        }
    }

    void solve(){
        precalc();
        sub1::solve();
    }
}

void sol(void){
    cin >> n >> q >> MOD;
    FOR(i, 1, n) cin >> A[i];
    memset(F1, 0, sizeof(F1));
    memset(F2, 0, sizeof(F2));
    if(MOD == 2018) case1::solve();
    else case2::solve();
}

signed main(void){
    #define TASK "orangejuice"
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
