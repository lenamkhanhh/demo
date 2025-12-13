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

int n, k, m;
int idx[N], cnt[N], F[N], L[N], res[N];
vector<ii> Line, tmp;

void sol(void){
    cin >> n >> k >> m;
    FOR(i, 1, m){
        int l, r, d; cin >> l >> r >> d;
        if(d == 0) cnt[l]++, cnt[r+1]--;
        else Line.push_back(ii(l, r));
    }

    FOR(i, 1, n){
        cnt[i] += cnt[i-1];
        if(cnt[i] == 0) idx[++idx[0]] = i;
    }
    if(idx[0] == k){
        FOR(i, 1, idx[0]) cout << idx[i] << '\n';
        return;
    }

    for(auto &[l, r] : Line){
        l = lower_bound(idx+1, idx+idx[0]+1, l) - idx;
        r = upper_bound(idx+1, idx+idx[0]+1, r) - idx - 1;
        if(l <= r) tmp.push_back(ii(l, r));
    }
    Line = tmp;
    sort(begin(Line), end(Line), [&](ii &x, ii &y){
        return x.fi != y.fi ? x.fi < y.fi : x.se > y.se;
    });
    vector<ii>().swap(tmp);
    for(auto &[l, r] : Line){
        while(sz(tmp) && tmp.back().se >= r) tmp.pop_back();
        tmp.push_back(ii(l, r));
    }
    Line = tmp;

    F0R(i, sz(Line)) L[i] = Line[i].fi;
    int pt = idx[idx[0]], tms = 0;
    F0Rd(i, sz(Line)){
        if(Line[i].se < pt){
            ++tms;
            pt = Line[i].fi;
        }
        F[i] = tms;
    }

    pt = -1, tms = 0;
    for(auto &[l, r] : Line) if(pt < l){
        if(l == r) res[++res[0]] = l;
        else{
            int T = upper_bound(L, L + sz(Line), r-1) - L;
            if(tms + 1 + F[T] > k) res[++res[0]] = r;
        }
        ++tms;
        pt = r;
    }

    if(res[0] == 0) return void(cout << -1 << '\n');
    FOR(i, 1, res[0]) cout << idx[res[i]] << '\n';
}

signed main(void){
    #define TASK "guard"
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
