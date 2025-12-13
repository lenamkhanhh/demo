#include <bits/stdc++.h>
#define endl '\n'
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

template<typename T1,typename T2> bool ckmax(T1 &x,const T2 &y){if(x<y){x=y; return 1;} return 0;}
template<typename T1,typename T2> bool ckmin(T1 &x,const T2 &y){if(y<x){x=y; return 1;} return 0;}

const int MOD = (int)1e9 + 7;
const int mod = 998244353;
const int N = 1e3 + 10, M = 1e2;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
long long rand(long long l, long long r){
    return l + rd() % (r - l + 1);
}

const int NumTEST = 1e4;

int par[N], A[N];

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

ii extgcd(int a, int b){
    if(a % b == 0) return make_pair(0, 1);
    ii T = extgcd(b, a % b);
    return make_pair(T.se, T.fi - (a/b) * T.se);
}

bool mark[M][M];

void sol(void){
    FOR(T, 1, NumTEST){
        ofstream fo(("nhap.inp"));
        int n = 2e4;
        fo << n << '\n';
        FOR(i, 1, n) fo << rand(1, 1e9) << " \n"[i == n];
        fo.close();

        system("main.exe");
        system("Code_Trau.exe");
        cout << "#TESTCASE " << T << ": ";
        if(system("fc nhap.out nhap.ans") != 0) return;
        else cout << "ACCEPTED\n";
    }
}

signed main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
//    cin >> t;
    while(t--) sol();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << " ms\n";
}
