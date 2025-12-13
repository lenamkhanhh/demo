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
const int N = 1e5 + 10, M = 18;
const int INF = (int)2e9 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n;
int A[N], Max[N], Min[N];
int p[N], b[2][N];
vector<int> v;

void update(int *bit, int idx, int d){
    for(; idx <= sz(v); idx += (idx & -idx)) bit[idx] += d;
}

int query(int *bit, int idx){
    int res = 0;
    for(; idx > 0; idx -= (idx & -idx)) res += bit[idx];
    return res;
}

long long cdq(int l, int r){
    if(l == r) return 1;
    int m = (l + r) >> 1;
    long long res = cdq(l, m) + cdq(m+1, r);
    Max[m] = Min[m] = A[m];
    for(int i = m-1; i >= l; i--){
        Max[i] = max(Max[i+1], A[i]);
        Min[i] = min(Min[i+1], A[i]);
    }

    Max[m+1] = Min[m+1] = A[m+1];
    for(int i = m+2; i <= r; i++){
        Max[i] = max(Max[i-1], A[i]);
        Min[i] = min(Min[i-1], A[i]);
    }

    v.clear();
    FOR(i, l, r) v.pb(Min[i]);
    sort(all(v)); v.resize(unique(all(v)) - v.begin());
    FOR(i, l, r) p[i] = lower_bound(all(v), Min[i]) - v.begin() + 1;

    int j = m;
    for(int i = m; i >= l; i--){
        while(j < r && Max[j+1] <= Max[i]){
            j++;
            update(b[Min[j] & 1], p[j], +1);
        }
        int T = query(b[Max[i] & 1], p[i]);
        res += T;
        T += query(b[(Max[i]&1)^1], p[i]);
        res += ((Max[i] - Min[i]) % 2 == 0 ? (j-m) - T : 0);
    }
    FOR(i, m+1, j) update(b[Min[i] & 1], p[i], -1);

    j = m+1;
    for(int i = m+1; i <= r; i++){
        while(l < j && Max[j-1] < Max[i]){
            j--;
            update(b[Min[j] & 1], p[j], +1);
        }
        int T = query(b[Max[i] & 1], p[i]);
        res += T;
        T += query(b[(Max[i]&1)^1], p[i]);

        res += ((Max[i] - Min[i]) % 2 == 0 ? (m-j+1) - T : 0);
    }
    FOR(i, j, m) update(b[Min[i] & 1], p[i], -1);
    return res;
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) cin >> A[i];
    cout << cdq(1, n) << '\n';
}

signed main(void){
    #define TASK "evensub"
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

