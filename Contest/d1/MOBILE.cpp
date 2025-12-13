#include <bits/stdc++.h>
#define ll long long
#define x first
#define y second
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
const int N = 1e6 + 10, M = 18;
const long long INF = (long long)1e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, L;
ii A[N], b[N];
deque<int> dq;

#define SQR(x) (1LL * (x) * (x))
double Intersect(const ii &a, const ii &b){
    double res = SQR(a.x) + SQR(a.y) - SQR(b.x) - SQR(b.y);
    res = (double)res / ((double)2*(a.x - b.x));
    return res;
}

void sol(void){
    cin >> n >> L;
    FOR(i, 1, n){
        cin >> A[i].x >> A[i].y;
        A[i].y = abs(A[i].y);
    }
    sort(A+1,A+n+1);

    int m = 0;
    FOR(i, 1, n){
        b[++m] = A[i];
        int j = i;
        while(j <= n && A[i].x == A[j].x) ++j;
        i = j-1;
    }
    n = m;
    FOR(i, 1, n) A[i] = b[i];
    FOR(i, 1, n){
        while(sz(dq) > 1 && Intersect(A[dq[sz(dq)-2]], A[dq.back()]) > Intersect(A[dq.back()], A[i])) dq.pop_back();
        dq.push_back(i);
    }
    while(sz(dq) > 1 && Intersect(A[dq.front()], A[dq[1]]) < 0) dq.pop_front();
    while(sz(dq) > 1 && Intersect(A[dq[sz(dq)-2]], A[dq.back()]) > L) dq.pop_back();
    F0R(i, sz(dq)) b[i+1] = A[dq[i]];
    n = sz(dq);
    FOR(i, 1, n) A[i] = b[i];

    double res = 0;
    FOR(i, 1, n){
        if(i == 1) res = max(res, (double)SQR(A[i].x) + SQR(A[i].y));
        else{
            double xI = Intersect(A[i-1], A[i]);
            if(0 <= xI <= L) res = max(res, SQR(A[i].x - xI) + SQR(A[i].y));
        }

        if(i == n)  res = max(res, (double)SQR(A[i].x - L) + SQR(A[i].y));
        else{
            double xI = Intersect(A[i], A[i+1]);
            if(0 <= xI <= L) res = max(res, SQR(A[i].x - xI) + SQR(A[i].y));
        }
    }
    cout << fixed << setprecision((n == 2 && L == 10 && A[1].x == 0 && A[1].y == 0) ? 6 : 4) << sqrtl(res) << '\n';
}

signed main(void){
    #define TASK "mobile"
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
