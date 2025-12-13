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
const int N = 3e2 + 10, M = 18;
const int INF = (int)2e9 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m;
int x[N], F[N][N][N][2];

void sol(void){
    cin >> n >> m;
    FOR(i, 1, n) cin >> x[i];
    ++n;
    sort(x+1,x+n+1);

    int s = 1;
    while(x[s] != 0) ++s;
//    for(int i = 1; i <= n; i++) cout << x[i] << " \n"[i == n];

    memset(F, 0x3f, sizeof(F));
    FOR(i, 1, n-1) F[s][s][i][0] = F[s][s][i][1] = 0;
    for(int k = n-1; k >= 1; k--) FOR(d, 1, n) FOR(l, 1, n){
        int r = l + d - 1;
        if(l > 1){
            ckmin(F[l-1][r][k-1][0], F[l][r][k][0] + k * (x[l] - x[l-1]));
            ckmin(F[l-1][r][k-1][0], F[l][r][k][1] + k * (x[r] - x[l-1]));
        }
        if(r < n){
            ckmin(F[l][r+1][k-1][1], F[l][r][k][0] + k * (x[r+1] - x[l]));
            ckmin(F[l][r+1][k-1][1], F[l][r][k][1] + k * (x[r+1] - x[r]));
        }
    }

    int res = 0;
    FOR(l, 1, n) FOR(r, l, n) if(min(F[l][r][0][0], F[l][r][0][1]) != F[0][0][0][0])
        res = max(res, (r-l) * m - min(F[l][r][0][0], F[l][r][0][1]));
    cout << res << '\n';
}

signed main(void){
    #define TASK "beetle"
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
