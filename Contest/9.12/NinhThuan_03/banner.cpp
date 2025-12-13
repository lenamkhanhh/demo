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
const int N = 5e4 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q;
char A[N];

void add(int &x, const int &y){
    if((x += y) >= MOD) x -= MOD;
}

void sub(int &x, const int &y){
    if((x -= y) < 0) x += MOD;
}

namespace sub1{
    int F[6];
    void solve(){
        while(q--){
            int l, r; cin >> l >> r;
            FOR(i, 1, 5) F[i] = 0;
            F[0] = 1;
            FOR(i, l, r){
                if(A[i] == 'H') add(F[1], F[0]);
                if(A[i] == 'S') add(F[2], F[1]);
                if(A[i] == 'G') add(F[3], F[2]);
                if(A[i] == '2') add(F[4], F[3]);
                if(A[i] == '5') add(F[5], F[4]);
            }
            cout << F[5] << '\n';
        }

    }
}

namespace subThuGian{
    int sum5[N], sum2[N], suf25[N];
    int F1[N][6], F2[N][5], F3[N][4];
    void solve(){
        F1[0][0] = F2[0][0] = F3[0][0] = 1;
        FOR(i, 1, n){
            sum2[i] = sum2[i-1] + bool(A[i] == '2');
            sum5[i] = sum5[i-1] + bool(A[i] == '5');
        }
        for(int i = n; i >= 1; i--){
            suf25[i] = suf25[i+1];
            if(A[i] == '2') add(suf25[i], sum5[n] - sum5[i]);

        }
        FOR(i, 1, n){
            FOR(j, 0, 5) F1[i][j] = F1[i-1][j];
            if(A[i] == 'H') add(F1[i][1], F1[i-1][0]);
            if(A[i] == 'S') add(F1[i][2], F1[i-1][1]);
            if(A[i] == 'G') add(F1[i][3], F1[i-1][2]);
            if(A[i] == '2') add(F1[i][4], F1[i-1][3]);
            if(A[i] == '5') add(F1[i][5], F1[i-1][4]);
        }

        FOR(i, 1, n){
            FOR(j, 0, 4) F2[i][j] = F2[i-1][j];
            if(A[i] == 'S') add(F2[i][1], F2[i-1][0]);
            if(A[i] == 'G') add(F2[i][2], F2[i-1][1]);
            if(A[i] == '2') add(F2[i][3], F2[i-1][2]);
            if(A[i] == '5') add(F2[i][4], F2[i-1][3]);
        }

        FOR(i, 1, n){
            FOR(j, 0, 3) F3[i][j] = F3[i-1][j];
            if(A[i] == 'G') add(F3[i][1], F3[i-1][0]);
            if(A[i] == '2') add(F3[i][2], F3[i-1][1]);
            if(A[i] == '5') add(F3[i][3], F3[i-1][2]);
        }

        while(q--){
            int l, r; cin >> l >> r;
            int res = (F1[r][5] - F1[l-1][5] + MOD) % MOD;

            // (1)(4)
            int T14 = (sum5[r] - sum5[l-1] + MOD) % MOD;
            sub(res, 1LL * F1[l-1][4] * T14 % MOD);

            // (1)(3)
            int T13 = (suf25[l] - suf25[r+1] + MOD) % MOD;
            sub(T13, 1LL * ((sum2[r] - sum2[l-1] + MOD) % MOD) * ((sum5[n] - sum5[r] + MOD) % MOD) % MOD);
            sub(res, 1LL * F1[l-1][3] * T13 % MOD);

            // (1)(2)
            int T12 = (F3[r][3] - F3[l-1][3] + MOD) % MOD;
            sub(T12, 1LL * F3[l-1][1] * T13 % MOD);
            sub(T12, 1LL * F3[l-1][2] * T14 % MOD);
            sub(res, 1LL * F1[l-1][2] * T12 % MOD);

            // (1)(1)
            int T11 = (F2[r][4] - F2[l-1][4] + MOD) % MOD;
            sub(T11, 1LL * F2[l-1][1] * T12 % MOD);
            sub(T11, 1LL * F2[l-1][2] * T13 % MOD);
            sub(T11, 1LL * F2[l-1][3] * T14 % MOD);
            sub(res, 1LL * F1[l-1][1] * T11 % MOD);
            cout << res << '\n';
        }
    }
}

void sol(void){
    cin >> n >> q;
    FOR(i, 1, n) cin >> A[i];
//    if(1LL * n * q <= 1e7) sub1::solve();
    subThuGian::solve();
}

signed main(void){
    #define TASK "banner"
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
