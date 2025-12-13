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
const int N = 2e5 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m;
int R[N], w[N], idx[N];
bool mark[N];
set<int> rem;
set<ii> inQueue;

void sol(void){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> R[i];
    for(int i = 1; i <= m; i++) cin >> w[i];
    for(int i = 1; i <= n; i++) rem.insert(i);

    long long res = 0;
    FOR(id, 1, 2*m){
        int i; cin >> i;
        if(i > 0){
            if(sz(rem) == 0){
                idx[i] = id;
                inQueue.insert(ii(id, i));
                continue;
            }
            auto it = rem.begin();
            idx[i] = *it;
            mark[i] = true;
            res += 1LL * w[i] * R[idx[i]];
            rem.erase(it);
        }
        else{
            i = -i;
            if(mark[i] == true){
                rem.insert(idx[i]);
                if(sz(inQueue) > 0){
                    int v = inQueue.begin()->se;
                    inQueue.erase(inQueue.begin());

                    idx[v] = idx[i];
                    mark[v] = true;
                    res += 1LL * w[v] * R[idx[i]];
                    rem.erase(idx[i]);
                }
            }
            else inQueue.erase(inQueue.find(ii(idx[i], i)));
        }
    }
    cout << res << '\n';
}

signed main(void){
    #define TASK "garage"
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
