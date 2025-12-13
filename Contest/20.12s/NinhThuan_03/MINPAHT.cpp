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
const int N = 5e3 + 1, M = 10;
const int inf = (int)2e9 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int n, m, q;
int A[M][N];
struct Query{
    int u, v, x, y, id;
    void init(int i){
        id = i;
        cin >> u >> v >> x >> y;
    }
}Q[N];

bool InGrid(int x, int y){
    if(x < 1 || n < x) return false;
    if(y < 1 || m < y) return false;
    return true;
}

struct Dta{
    int u, v;
    long long cost;
    bool operator < (const Dta &p) const{
        return cost > p.cost;
    }
};

namespace sub1{
    int d[M][N];
    priority_queue<Dta> pq;
    long long calc(int s, int t, int x, int y){
        while(sz(pq)) pq.pop();
        FOR(i, 1, n) FOR(j, 1, m) d[i][j] = inf;
        d[s][t] = A[s][t];
        pq.push({s, t, A[s][t]});
        while(sz(pq)){
            auto [u, v, cost] = pq.top(); pq.pop();
            if(d[u][v] < cost) continue;
            for(int dx : {-1, 0, 1}) for(int dy : {-1, 0, 1}) if(abs(dx) != abs(dy)){
                int nx = u + dx;
                int ny = v + dy;
                if(InGrid(nx, ny) && ckmin(d[nx][ny], d[u][v] + A[nx][ny])){
                    pq.push({nx, ny, d[nx][ny]});
                }
            }
        }
        return d[x][y];
    }
    void solve(){
        FOR(i, 1, q){
            int u = Q[i].u, v = Q[i].v;
            int x = Q[i].x, y = Q[i].y, id = Q[i].id;
            cout << calc(u, v, x, y) << '\n';
        }
        exit(0);
    }
}

namespace sub2{
    int d[2][N];
    int res[2][N][2][N];

    priority_queue<Dta> pq;
    void calc(int s, int t){
        while(sz(pq)) pq.pop();
        FOR(i, 1, n) FOR(j, t, m) d[i][j] = inf;
        d[s][t] = A[s][t];
        pq.push({s, t, A[s][t]});
        while(sz(pq)){
            auto [u, v, cost] = pq.top(); pq.pop();
            if(d[u][v] < cost) continue;
            res[s][t][u][v] = cost;
            for(int dx : {-1, 0, 1}) for(int dy : {-1, 0, 1}) if(abs(dx) != abs(dy)){
                int x = u + dx;
                int y = v + dy;
                if(t <= y && InGrid(x, y) && ckmin(d[x][y], d[u][v] + A[x][y])){
                    pq.push({x, y, d[x][y]});
                }
            }
        }
    }

    void solve(){
        FOR(i, 1, n) FOR(j, 1, m) calc(i, j);
        FOR(i, 1, q){
            int u = Q[i].u, v = Q[i].v;
            int x = Q[i].x, y = Q[i].y, id = Q[i].id;
            if(y > v){
                swap(x, u);
                swap(y, v);
            }
            cout << res[x][y][u][v] << '\n';
        }
        exit(0);
    }
}

namespace sub3{
    int d[8][1001][8][1001];

    priority_queue<Dta> pq;
    void calc(int s, int t){
        while(sz(pq)) pq.pop();
        FOR(i, 1, n) FOR(j, 1, m) d[s][t][i][j] = inf;
        d[s][t][s][t] = A[s][t];
        pq.push({s, t, A[s][t]});
        while(sz(pq)){
            auto [u, v, cost] = pq.top(); pq.pop();
            if(d[s][t][u][v] < cost) continue;
            for(int dx : {-1, 0, 1}) for(int dy : {-1, 0, 1}) if(abs(dx) != abs(dy)){
                int x = u + dx, y = v + dy;
                if(InGrid(x, y) && ckmin(d[s][t][x][y], d[s][t][u][v] + A[x][y])){
                    pq.push({x, y, d[s][t][x][y]});
                }
            }
        }
    }

    void solve(){
        FOR(i, 1, n) FOR(j, 1, m) calc(i, j);
        FOR(i, 1, q){
            int u = Q[i].u, v = Q[i].v, x = Q[i].x, y = Q[i].y;
            cout << d[x][y][u][v] << '\n';
        }
        exit(0);
    }
}

void sol(void){
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m) cin >> A[i][j];
    cin >> q;
    FOR(i, 1, q) Q[i].init(i);
    if(max(m, q) <= 5e2) sub1::solve();
    if(1LL * n * m <= 7e3) sub3::solve();
    sub2::solve();
}

signed main(void){
    #define TASK "MINPAHT"
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

