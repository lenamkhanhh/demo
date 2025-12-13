#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pb emplace_back
#define ii pair<ll, ll>
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
const int N = 3e5 + 10, M = 18;
const long long INF = (long long)1e15 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

struct Dta1{
    ll T, d, lim;
    bool operator < (const Dta1 &p) const{
        return T > p.T;
    }
};

struct Dta2{
    ll T, d, lim;
    bool operator < (const Dta2 &p) const{
        return T < p.T;
    }
};

int n, q;
ii Q[N];
ll posL[N], posR[N], Time[N], res[N];
priority_queue<Dta2> L;
priority_queue<Dta1> R;

void sol(void){
    cin >> n >> q;
    FOR(i, 1, n){
        char ch; cin >> ch;
        ll d, c; cin >> d >> c;
        if(ch == 'L') d = -d;

        ll lim = (d > INF / c ? INF : d * c);
        if(ch == 'L') L.push({d, d, lim});
        else R.push({d, d, lim});
    }

    FOR(i, 1, q){
        ll T; cin >> T;
        Q[i] = ii(T, i);
    }
    sort(Q+1,Q+q+1);

    ll T = 1;
    int d = 1, m = 0;
    while(true){
        posL[++m] = T;
        Time[m] = Time[m-1] + abs(posR[m-1] - posL[m-1]) + 1;
        if(Time[m] > Q[q].fi) break;
        if(d == 1){
            if(sz(R) == 0){
                posR[m] = INF;
                break;
            }
            Dta1 nxt = R.top(); R.pop();
            posR[m] = nxt.T;
            if(nxt.T < nxt.lim) R.push({nxt.T + nxt.d, nxt.d, nxt.lim});
            d = -1;
            T = posR[m] - 1;
        }
        else{
            if(sz(L) == 0){
                posR[m] = -INF;
                break;
            }
            Dta2 nxt = L.top(); L.pop();
            posR[m] = nxt.T;
            if(nxt.T < nxt.lim) L.push({nxt.T + nxt.d, nxt.d, nxt.lim});
            d = +1;
            T = posR[m] + 1;
        }
    }

//    FOR(i, 1, m) cout << posL[i] << ' ' << posR[i] << ' ' << Time[i] << endl;

    FOR(i, 1, q){
        int p = upper_bound(Time+1, Time+m+1, Q[i].fi) - Time - 1;
        res[Q[i].se] = (posL[p] <= posR[p] ? posL[p] + Q[i].fi - Time[p] : posL[p] - Q[i].fi + Time[p]);
    }
    FOR(i, 1, q) cout << res[i] << '\n';
}

signed main(void){
    #define TASK "mirror"
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

