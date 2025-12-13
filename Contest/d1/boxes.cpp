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
const int N = 1e6 + 10, M = 20 * N;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

#define int long long
int n;
struct Dta{
    int w, s, id;
    void init(int i){
        id = i;
        cin >> w >> s;
    }
    void out(){
        cout << w << ' ' << s << ' ' << id << '\n';
    }
    bool operator < (const Dta &p) const{
        return w + s < p.w + p.s;
    }
}A[N];
set<int> idx;

void sol(void){
    cin >> n;
    FOR(i, 1, n) A[i].init(i);
    sort(A+1,A+n+1);

    int res = 0, sum = 0;
    priority_queue<ii> pq;
    FOR(i, 1, n){
        if(sz(pq) == 0 || sum <= A[i].s){
            sum += A[i].w;
            pq.push({A[i].w, i});
            idx.insert(i);
        }
        else{
            if(A[i].w < pq.top().fi && sum - pq.top().fi <= A[i].s){
                idx.erase(idx.find(pq.top().se));
                sum -= pq.top().fi; pq.pop();
                sum += A[i].w; pq.push({A[i].w, i});
                idx.insert(i);
            }
        }
        res = max(res, sz(pq));
    }
    cout << res << '\n';
    for(int i : idx) cout << A[i].w << ' ' << A[i].s << '\n';
}

signed main(void){
    #define TASK "boxes"
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
