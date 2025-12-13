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
const int N = 3e5 + 10, M = 30;
const long long INF = (long long)4e18 + 11;

/*
     /\_/\
    (= ._.)
    / >?  \>$
*/

int n, q;
long long Q[N];

namespace sub1{
    int m;
    ii e[N];
    int st[MASK(20)];

    void build(int i, int l, int r){
        if(l == r){
            st[i] = 1;
            return;
        }
        int m = (l + r) >> 1;
        build(i<<1, l, m);
        build(i<<1|1, m+1, r);
        st[i] = st[i<<1] + st[i<<1|1];
    }


    void update(int i, int l, int r, int p){
        while(l < r){
            int m = (l + r) >> 1;
            if(p <= m) r = m, i = i<<1;
            else l = m+1, i = i<<1|1;
        }
        st[i] = 0;
        while(i > 1){
            i >>= 1;
            st[i] = st[i<<1] + st[i<<1|1];
        }
    }

    int query(int i, int l, int r, int k){
        while(l < r){
            int m = (l + r) >> 1;
            if(st[i<<1] < k){
                k -= st[i<<1];
                l = m+1, i = i<<1|1;
            }
            else r = m, i = i<<1;
        }
        return r;
    }

    void solve(){
        int Max = 1LL * n * (n-1) / 2;
        FOR(i, 1, n) FOR(j, i+1, n) e[++m] = ii(i, j);
        build(1, 1, Max);
        FOR(i, 1, q){
            int idx = query(1, 1, Max, Q[i]);
            update(1, 1, Max, idx);
            cout << e[idx].fi << ' ' << e[idx].se << '\n';
        }
    }
}

namespace sub2{
    ii e[N];
    void solve(){
        #define SQR(x) (1LL * (x) * (x+1) / 2)
        long long L = 1, R = 1LL * n * (n-1) / 2;

        auto query = [&](int i, int x){
            int cnt = 0;
            FOR(j, 1, i-1) cnt += bool(e[j].fi <= x);
            return SQR(n-1) - SQR(n-x-1) - cnt;
        };

        FOR(i, 1, q){
            long long k = Q[i], l = 1, r = n;
            while(l < r){
                int m = (l + r) >> 1;
                if(k <= query(i, m)) r = m;
                else l = m+1;
            }
            int u = r;
            k -= query(i, u-1);

            l = u+1, r = n;
            while(l < r){
                int m = (l + r) >> 1;
                int cnt = 0;
                FOR(j, 1, i-1) if(e[j].fi == u) cnt += bool(e[j].se <= m);
                if(m - u - cnt >= k) r = m;
                else l = m+1;
            }
            int v = r;
            e[i] = ii(u, v);
        }
        FOR(i, 1, q) cout << e[i].fi << ' ' << e[i].se << '\n';
    }
}

namespace sub{
    struct Trie{
        struct Node{
            int cnt;
            int child[2];
            Node(){
                cnt = 0;
                memset(child, -1, sizeof(child));
            }
        };
        vector<Node> node;
        Trie(){
            node.push_back(Node());
        }

        void add(int x){
            int p = 0;
            F0Rd(i, M){
                int c = (x >> i) & 1;
                if(node[p].child[c] == -1){
                    node[p].child[c] = sz(node);
                    node.push_back(Node());
                }
                p = node[p].child[c];
                node[p].cnt++;
            }
        }

        int query(int x){
            x++;
            int p = 0, res = 0;
            F0Rd(i, M){
                int c = (x >> i) & 1;
                if(c == 1 && node[p].child[0] != -1) res += node[node[p].child[0]].cnt;
                if(node[p].child[c] == -1) break;
                p = node[p].child[c];
            }
            return res;
        }
    }trie[100010];

    int ptr;
    map<int, int> mp;
    int HashMap(int u){
        if(mp[u] == 0) mp[u] = ++ptr;
        return mp[u];
    }

    ii e[N];
    void solve(){
        #define SQR(x) (1LL * (x) * (x+1) / 2)
        long long L = 1, R = 1LL * n * (n-1) / 2;

        auto query = [&](int i, int x){
            return SQR(n-1) - SQR(n-x-1) - trie[0].query(x);
        };

        FOR(i, 1, q){
            long long k = Q[i], l = 1, r = n;
            while(l < r){
                int m = (l + r) >> 1;
                if(k <= query(i, m)) r = m;
                else l = m+1;
            }
            int u = r;
            k -= query(i, u-1);

            l = u+1, r = n;
            int T = HashMap(u);
            while(l < r){
                int m = (l + r) >> 1;
                if(m - u - trie[T].query(m) >= k) r = m;
                else l = m+1;
            }
            int v = r;
            e[i] = ii(u, v);
            trie[0].add(u);
            trie[T].add(v);
        }
        FOR(i, 1, q) cout << e[i].fi << ' ' << e[i].se << '\n';
    }
}

void sol(void){
    cin >> n >> q;
    FOR(i, 1, q) cin >> Q[i];
//    if(n <= 5e2) sub1::solve();
//    if(q <= 5e2) sub2::solve();
    sub::solve();
}

signed main(void){
    #define TASK "GENTEST"
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

