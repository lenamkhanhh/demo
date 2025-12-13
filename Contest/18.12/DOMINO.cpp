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
const int N = 3e5 + 10, M = 5e2;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, m, k;
int x[N], y[N], u[N], v[N];
bool ok[M][M];
int mark[M][M];
queue<ii> pq;

// L, U, R, D
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

bool InGrid(int x, int y){
    if(x < 1 || n < x) return false;
    if(y < 1 || m < y) return false;
    return true;
}

void sol(void){
    cin >> n >> m;
    k = (n * m - 1) / 2;
    FOR(i, 1, k){
        cin >> x[i] >> y[i] >> u[i] >> v[i];
        mark[x[i]][y[i]] = mark[u[i]][v[i]] = i;
    }

    int sx, sy;
    FOR(i, 1, n) FOR(j, 1, m) if(mark[i][j] == 0) sx = i, sy = j;

    pq.push({sx, sy});
    ok[sx][sy] = true;
    while(sz(pq)){
        auto [u, v] = pq.front(); pq.pop();
        F0R(i, 4){
            int x = u + dx[i], y = v + dy[i];
            int nx = x + dx[i], ny = y + dy[i];
            if(InGrid(x, y) && InGrid(nx, ny) && mark[x][y] == mark[nx][ny]){
                if(ok[nx][ny] == false){
                    ok[nx][ny] = true;
                    pq.push(ii(nx, ny));
                }
            }
        }
    }
    set<int> s;
    FOR(i, 1, n) FOR(j, 1, m) if(ok[i][j] == true) s.insert(mark[i][j]);
    cout << sz(s)-1 << '\n';
}

signed main(void){
    #define TASK "domino"
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

