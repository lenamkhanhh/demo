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

int n;
struct Dta{
    int x, y, v;
    void init(){
        cin >> x >> y >> v;
    }
}A[N];

namespace sub1{
    #define SQR(x) (1LL * (x) * (x))
    double dist(const Dta &a, const Dta &b){
        return sqrt(SQR(a.x - b.x) + SQR(a.y - b.y));
    }

    void solve(){
        if(A[1].v < A[2].v) swap(A[1], A[2]);
        double d = dist(A[1], A[2]);
        double D = A[1].v - A[2].v;
        D = max((double)0, D - d);
        D = D / 2;
        cout << fixed << setprecision(6) << A[2].v + D << '\n';
        exit(0);
    }
}

namespace sub2{
    void solve(){

    }
}

void sol(void){
    cin >> n;
    FOR(i, 1, n) A[i].init();
    if(n == 2) sub1::solve();
    if(n == 3) sub2::solve();
}

signed main(void){
    #define TASK "drought"
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
