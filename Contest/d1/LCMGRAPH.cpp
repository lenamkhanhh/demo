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
const int N = 3e5 + 10;
const long long INF = (long long)1e18 + 1000001;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/


int n, k;
bool mark[N];
int A[N], b[N];
int MinPrime[N];
vector<int> ds;

namespace sub3{
    const int M = 2e3 + 10;
    int cnt[N], trace[M];
    long long F[M];
    long long cost[M][M];
    vector<int> v, path;

    void solve(){
        FOR(i, 1, n){
            v.clear();
            long long res = 1;
            for(int j = i; j >= 1; j--){
                if(res < INF){
                    int x = A[j];
                    while(x > 1){
                        int exp = 0, p = MinPrime[x];
                        while(x % p == 0) exp++, x /= p;
                        if(exp <= cnt[p]) continue;
                        FOR(T, cnt[p]+1, exp){
                            if(res > INF / p){
                                res = INF;
                                break;
                            }
                            res = 1LL * res * p;
                        }
                        cnt[p] = exp;
                        if(mark[p] == false){
                            v.pb(p);
                            mark[p] = true;
                        }
                    }
                }
                cost[j][i] = res;
            }
            for(int x : v) cnt[x] = mark[x] = 0;
        }
        memset(F, 0x3f, sizeof(F)); F[ds[0]] = 0;
        for(int id = 0; id < (int)ds.size() - 1; id++){
            int L = ds[id], R = ds[id+1];
            FOR(i, L+1, R) FOR(j, L, i-1) if(ckmin(F[i], F[j] + cost[j][i])) trace[i] = j;
        }
//        FOR(i, ds[0], ds.back()) cout << i << " \n"[i == ds.back()];
//        FOR(i, ds[0], ds.back()) cout << F[i] << " \n"[i == ds.back()];
//        FOR(i, ds[0], ds.back()) cout << trace[i] << " \n"[i == ds.back()];

        cout << F[ds.back()] << '\n';
        for(int u = ds.back(); u != ds[0]; u = trace[u]) path.push_back(u);
        path.push_back(ds[0]);
        reverse(begin(path), end(path));
        cout << sz(path) - 1 << '\n';
        for(int i = 0; i < (int)path.size() - 1; i++) cout << path[i] << ' ' << path[i+1] << '\n';
        exit(0);
    }
}

namespace sub{
    void solve(){

    }
}

void sol(void){
    cin >> n >> k;
    FOR(i, 1, n) cin >> A[i];
    FOR(i, 1, k){
        int x; cin >> x;
        ds.push_back(x);
    }
    sort(begin(ds), end(ds));
    if(k == 1){
        cout << 0 << '\n';
        cout << 0 << '\n';
        return;
    }

    int mx = *max_element(A+1, A+n+1);
    FOR(i, 2, mx) if(MinPrime[i] == 0) for(int j = i; j <= mx; j += i) MinPrime[j] = i;

    if(n <= 2e3) sub3::solve();
    sub::solve();
}

signed main(void){
    #define TASK "LCMGRAPH"
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
