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
const int N = 1e6, M = 18;
const int INF = (int)2e9 + 11;
const long long LINF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n;
int cnt[N+10];
int minPrime[N+10];

void sol(void){
    cin >> n;
    FOR(i, 2, N) if(minPrime[i] == 0){
        minPrime[i] = i;
        for(int j = 2*i; j <= N; j += i) minPrime[j] = i;
    }
    int m = 0;
    FOR(i, 1, n){
        int x; cin >> x;
        int rem = 1;
        while(x > 1){
            int p = minPrime[x], exp = 0;
            while(x % p == 0) x /= p, exp++;
            if(exp & 1) rem *= p;
        }
        cnt[rem]++;
        m = max(m, rem);
    }
    long long res = 0;
    FOR(i, 1, m) res += 1LL * cnt[i] * (cnt[i]-1) / 2;
    cout << res << '\n';
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

