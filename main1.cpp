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
int A[N+10];
int minPrime[N+10];
long long cnt[N];
vector<int> v;
vector<int> pos[N+10];

int Pow(int a, int b){
    int res = 1;
    for(; b > 0; b >>= 1, a = 1LL * a * a % MOD) if(b & 1) res = 1LL * res * a % MOD;
    return res;
}

void reset(void){
    for(int p : v){
        cnt[p] = 0;
        pos[p].clear();
    }
    v.clear();
}

void sol(void){
    reset();
    cin >> n;
    FOR(i, 1, n) cin >> A[i];
    FOR(i, 1, n){
        int x = A[i];
        while(x > 1){
            int p = minPrime[x];
            while(x % p == 0) x /= p;
            pos[p].push_back(i);
            v.pb(p);
        }
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    for(int p : v){
        cnt[p] = 1LL * n * (n+1) % MOD * Pow(2, MOD-2) % MOD;
        int pre = 0;
        pos[p].push_back(n+1);
        for(int i : pos[p]){
            int len = i - pre - 1;
            if(len > 0){
                cnt[p] -= 1LL * len * (len+1) % MOD * Pow(2, MOD-2) % MOD;
                if(cnt[p] < 0) cnt[p] += MOD;
            }
            pre = i;
        }
    }
    long long res = Pow(2, 1LL*n*(n+1)/2);
    res = Pow(res, MOD-2);
    for(int p : v) res = 1LL * res * Pow(2, cnt[p]) % MOD;
    cout << res << '\n';
}

signed main(void){
    #define TASK "nhap"
    if(fopen(TASK".inp", "r")){
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    FOR(i, 2, N) if(minPrime[i] == 0){
        minPrime[i] = i;
        for(int j = 2*i; j <= N; j += i) minPrime[j] = i;
    }

    int t = 1;
    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}

