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
using namespace std;

template<typename T1, typename T2> bool ckmax(T1 &A, const T2 &B){if(A < B){A = B;return true;} return false;}
template<typename T1, typename T2> bool ckmin(T1 &A, const T2 &B){if(A > B){A = B;return true;} return false;}

const int MOD = (int)1e9 + 7; // 998244353
const int N = 2e6, M = 18;
const int INF = (int)2e9 + 11;
const long long LINF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

#define int unsigned long long
int n, m;
int A[N+1000], b[N+10];

long long calc(int x, int y){
    FOR(i, 1, m){
        while(x % b[i] == 0 && y % b[i] == 0){
            x /= b[i];
            y /= b[i];
        }
    }
    return x + y;
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, n) cin >> A[i];
    FOR(i, 1, m) cin >> b[i];
    long long res = 0;
    FOR(i, 1, n) FOR(j, i+1, n) res += calc(A[i], A[j]);
    cout << res << '\n';
}

signed main(void){
    #define TASK "nhap"
    if(fopen(TASK".inp", "r")){
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".ans", "w", stdout);
    }
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
//    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}

