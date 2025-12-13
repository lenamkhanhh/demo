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
const int N = 3e5 + 10, M = 26;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q;
int L[N], A[N];
string s[N];
struct Query{
    int l, r;
}Q[N];

#define SQR(x) (1LL * (x) * (x))
namespace sub3{
    bool check(){
        FOR(i, 1, n) F0R(j, L[i]-1) if(s[i][j] != s[i][j+1]) return false;
        return true;
    }

    int st[N][M][M], T[M];

    void solve(){
        FOR(i, 1, n) st[i][0][s[i][0]-'a'] = sz(s[i]);
        FOR(j, 1, __lg(n)) FOR(i, 1, n-MASK(j)+1) F0R(ch, M)
            st[i][j][ch] = max(st[i][j-1][ch], st[i+MASK(j-1)][j-1][ch]);

        auto query = [&](int l, int r, int ch){
            int k = __lg(r-l+1);
            return max(st[l][k][ch], st[r-MASK(k)+1][k][ch]);
        };

        FOR(i, 1, q){
            auto &[l, r] = Q[i];
            int sum = 0;
            long long res = 0;
            F0R(ch, M){
                T[ch] = query(l, r, ch);
                sum += T[ch];
//                cout << (char)(ch + 'a') << ' ' << T[ch] << '\n';
            }
            F0R(ch, M) if(T[ch] > 0){
                res += 2*T[ch]-1;
                sum -= T[ch];
                res += 1LL * T[ch] * sum;
                sum += T[ch];
            }
            cout << res << '\n';
        }
        exit(0);
    }
}

namespace sub1{
    long long base = 31, Pow[3005], F[3005][3005];
    int getHash(int l, int r, int id){
        return (F[id][r] - F[id][l-1] * Pow[r-l+1] + 1LL * MOD * MOD) % MOD;
    }

    void solve(){
        int m = *max_element(L+1,L+n+1);
        Pow[0] = 1;
        FOR(i, 1, m) Pow[i] = Pow[i-1] * base % MOD;
        FOR(i, 1, n){
            s[i] = ' ' + s[i];
            FOR(j, 1, L[i]) F[i][j] = (F[i][j-1] * base + (s[i][j] - 'a' + 1)) % MOD;
        }

        FOR(id, 1, q){
            int idx = 0;
            auto &[l, r] = Q[id];
            FOR(i, l, r) FOR(j, l, r){
                FOR(d1, 1, L[i]) for(int d2 = L[j]; d2 >= 1; d2--){
                    int T = 1LL * F[i][d1] * Pow[L[j]-d2+1] % MOD;
                    T = (T + getHash(d2, L[j], j)) % MOD;
                    A[++idx] = T;
                }
            }
            sort(A+1,A+idx+1);
            int res = 0;
            FOR(i, 1, idx){
                int j = i;
                while(j <= idx && A[i] == A[j]) ++j;
                res++;
                i = j-1;
            }
            cout << res << '\n';
        }
    }
}

void sol(void){
    cin >> n >> q;
    FOR(i, 1, n) cin >> s[i];
    FOR(i, 1, q) cin >> Q[i].l >> Q[i].r;
    FOR(i, 1, n) L[i] = sz(s[i]);
    if(sub3::check()) sub3::solve();
    sub1::solve();
}

signed main(void){
    #define TASK "preandsuf"
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
