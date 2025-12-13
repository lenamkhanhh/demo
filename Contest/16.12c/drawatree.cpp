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

const int MOD = (int)1e9 + 22071997;
const int mod = 998244353;
const int N = 6e2 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n;
bool ban[N][N];

int par[N];
int Find(int v){
    return par[v] < 0 ? v : par[v] = Find(par[v]);
}

bool Union(int u, int v){
    u = Find(u), v = Find(v);
    if(u == v) return false;
    if(par[u] > par[v]) swap(u, v);
    par[u] += par[v], par[v] = u;
    return true;
}
vector<ii> e;
vector<vector<ii>> res;

void dq(int i, int k){
    if(i > n){
        if(k != n-1) return;
        for(auto &[u, v] : e){
            for(auto &[l, r] : e){
                if(u < l && l <= v && v <= r) return;
                if(l <= u && u <= r && r < v) return;
            }
        }
        int cnt = 0;
        FOR(i, 1, n) par[i] = -1;
        for(auto &[u, v] : e) cnt += Union(u, v);
        if(cnt == n-1){
            vector<ii> tmp;
            for(auto [u, v] : e){
                if(u > v) swap(u, v);
                tmp.push_back(ii(u, v));
            }
            sort(all(tmp));
            res.push_back(tmp);
        }
        return;
    }
    dq(i+1, k);
    FOR(j, 1, n) if(ban[i][j] == false){
        e.push_back({i, j});
        dq(i+1, k+1);
        e.pop_back();
    }
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) ban[i][i] = true;
    FOR(i, 1, n) FOR(j, 1, n-i){
        char ch; cin >> ch;
        ban[i][i+j] = ban[i+j][i] = (ch == 'N');
    }
    dq(1, 0);
    sort(all(res)); res.resize(unique(all(res)) - res.begin());
    cout << sz(res) << '\n';
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
