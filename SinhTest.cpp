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
const int N = 1e2 + 10, M = 1e2;
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

const int NumTEST = 1e6;
bool used[M][M];

string gene(int n){
    string s = {};
    s.push_back((char)(rand(1,9) + '0'));
    FOR(i, 1, n-1) s.push_back((char)(rand(0,9) + '0'));
    return s;
}

const int L = 1;
void sol(void){
    FOR(T, 1, NumTEST){
        ofstream fo(("nhap.inp"));
        int n = rand(3, 3);
        fo << n << ' ' << 3 << '\n';
        FOR(i,1,n)  fo << rand(1, 10) << ' ';
        fo << '\n';
        fo << 2 << ' ' << 3 << ' ' << 5 << '\n';
        fo.close();

        system("main.exe");
        system("CodeTrau.exe");
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
