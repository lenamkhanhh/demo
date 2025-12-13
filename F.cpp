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
const int N = 2e5 + 10, M = 19;
const int INF = (int)2e9 + 11;
const long long LINF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

struct Query{
    int l, r, w;
}Q[N];
int n, m, node;
int root[N];
int L[N*M], R[N*M], cnt[N*M];
long long sum[N*M];
vector<int> v, add[N], del[N];

void update(int i, int cur, int l, int r, int p, int d){
    if(l == r){
        cnt[i] = cnt[cur] + d;
        sum[i] = sum[cur] + (d == 1 ? 1 : -1) * v[p-1];
        return;
    }
    int m = (l + r) >> 1;
    if(p <= m){
        L[i] = ++node;
        R[i] = R[cur];
        update(L[i], L[cur], l, m, p, d);
    }
    else{
        L[i] = L[cur];
        R[i] = ++node;
        update(R[i], R[cur], m+1, r, p, d);
    }
    cnt[i] = cnt[L[i]] + cnt[R[i]];
    sum[i] = sum[L[i]] + sum[R[i]];
}

long long query(int i, int l, int r, int k){
    long long res = 0;
    while(l < r){
        int m = (l + r) >> 1;
        if(cnt[L[i]] < k){
            k -= cnt[L[i]];
            res += sum[L[i]];
            i = R[i];
            l = m+1;
        }
        else i = L[i], r = m;
    }
    return res + k*v[l-1];
}

void sol(void){
    cin >> n >> m;
    int mx = 0;
    FOR(i, 1, n){
        int l, r, w; cin >> l >> r >> w;
        Q[i] = {l, r, w};
        v.pb(w);
        mx = max(mx, r);
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    FOR(i, 1, n){
        int l = Q[i].l, r = Q[i].r, w = Q[i].w;
        w = lower_bound(all(v), w) - v.begin() + 1;
        add[l].push_back(w);
        del[r+1].push_back(w);
    }    
 
    FOR(i, 1, mx){
        root[i] = (i == 1 ? 0 : root[i-1]);
        for(int w : add[i]){
            int tmp = ++node;
            update(tmp, root[i], 1, sz(v), w, +1); 
            root[i] = tmp;
        }
        for(int w : del[i]){
            int tmp = ++node;
            update(tmp, root[i], 1, sz(v), w, -1); 
            root[i] = tmp; 
        }
    }
    long long pw = 1;
    FOR(i, 1, m){
        int p, D, A, F; cin >> p >> D >> A >> F;
        int E = 1 + (D * pw + A) % F;
        pw = query(root[p], 1, n, E);
        cout << pw << '\n';
    }
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

