#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const long long INF = 1e18;

struct edge {
    int v;
    ll flow, cap;
    int rev;
};

// Độ phức tạp: O(V^2 E) tổng quát, O(E sqrt(V)) cho mạng đơn vị (ghép cặp).
struct Dinic {
    int n;
    vector<vector<edge>> adj;
    vector<int> level, start;
    Dinic(int n) : n(n), adj(n), level(n), start(n) {}

    // Thêm cạnh CÓ HƯỚNG u -> v. Nếu vô hướng thì gọi hàm này 2 lần
    void add_edge(int u, int v, ll cap) {
        edge a{v, 0, cap, (int)adj[v].size()};
        edge b{u, 0, 0, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : adj[u]) {
                if (level[e.v] < 0 && e.flow < e.cap) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[t] >= 0;
    }

    ll send_flow(int u, int t, ll flow) {
        if (u == t) return flow;
        for (int& i = start[u]; i < (int)adj[u].size(); i++) {
            edge& e = adj[u][i];
            if (level[e.v] == level[u] + 1 && e.flow < e.cap) {
                ll curr_flow = min(flow, e.cap - e.flow);
                ll temp_flow = send_flow(e.v, t, curr_flow);
                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        ll total = 0;
        while (bfs(s, t)) {
            fill(start.begin(), start.end(), 0);
            while (ll flow = send_flow(s, t, LLONG_MAX)) total += flow;
        }
        return total;
    }
};

// TRUY VẾT MIN-CUT
// USAGE: Chỉ gọi hàm này SAU KHI đã chạy dinic.max_flow(s, t)
// Output: In ra các cạnh (u, v) thuộc lát cắt nhỏ nhất (u thuộc S-set, v thuộc T-set)
void find_min_cut(int s, int n, Dinic &dinic) {
    vector<bool> visited(n+1, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& e : dinic.adj[u]) if (!visited[e.v] && e.flow < e.cap) {
            visited[e.v] = true;
            q.push(e.v);
        }
    }
    
    // In cạnh cắt: u thăm được, v không thăm được, và là cạnh xuôi (cap > 0)
    for (int u=1;u<=n;u++) 
        if (visited[u]) 
            for (auto& e : dinic.adj[u]) 
                if (!visited[e.v] && e.cap > 0) cout << u << " " << e.v << "\n";
}

// CIRCULATION WITH DEMANDS (Luồng có cận dưới)
// Bài toán: Mỗi cạnh có flow trong đoạn [low, high].
struct Circulation {
    int n;
    vector<ll> d; // Balance array: d[i] = In_low - Out_low
    
    struct EdgeInfo {
        int u, v;
        ll low, cap;
        int id_in_dinic; // Để truy xuất lại flow thực tế sau khi giải
    };
    vector<EdgeInfo> edges;
    Dinic dinic;
    int SS, TT;  // Super Source, Super Sink

    // Init: n là số đỉnh thực tế. SS, TT tự động gán n+1, n+2
    Circulation(int n) : n(n), d(n + 1, 0), dinic(n + 3) {
        SS = n + 1;
        TT = n + 2;
    }

    // Thêm cạnh: u -> v, bắt buộc chảy tối thiểu `low`, tối đa `high`
    void add_edge(int u, int v, ll low, ll high) {
        d[u] -= low;
        d[v] += low;
        // Thêm vào Dinic cạnh có sức chứa (high - low)
        edges.push_back({u, v, low, high, (int)dinic.adj[u].size()});
        dinic.add_edge(u, v, high - low);
    }

    // Kiểm tra xem có tồn tại phương án (Feasible Flow) thỏa mãn mọi lower_bound không
    bool solve() {
        ll total_demand = 0;
        for (int i = 1; i <= n; ++i) {
            if (d[i] > 0) {
                total_demand += d[i];
                dinic.add_edge(SS, i, d[i]);
            } else if (d[i] < 0) dinic.add_edge(i, TT, -d[i]);
        }
        ll flow = dinic.max_flow(SS, TT);
        return flow == total_demand;
    }

    // Lấy flow thực tế của cạnh thứ i (theo thứ tự add_edge, 0-based)
    ll get_flow(int i) {
        return dinic.adj[edges[i].u][edges[i].id_in_dinic].flow + edges[i].low;
    }
};

/* NOTE: CÁC DẠNG BÀI CIRCULATION THƯỜNG GẶP
   
   Dạng 1: Kiểm tra có phương án thỏa mãn không (Feasible Flow)
     1. Init Circulation(n)
     2. Add edges (low, high)
     3. if (circ.solve()) -> YES else -> NO

   Dạng 2: Max Flow có cận dưới từ S -> T
     1. Init Circulation(n)
     2. Add edges (u, v, low, high)
     3. Add cạnh vô cực từ T về S: circ.add_edge(t, s, 0, INF);  <-- QUAN TRỌNG
     4. if (!circ.solve()) -> Không có lời giải
     5. Kết quả Max Flow chính là flow của cạnh (t->s) vừa thêm ở bước 3.
        Gọi: circ.get_flow(m) (với m là chỉ số cạnh cuối cùng).
*/


#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;
using cd=complex<double>;
const double PI=acos(-1);

void fft(vector<cd> &a,bool invert){
    int n=a.size();
    // Bit-reversal permutation
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j&bit;bit>>1) j^=bit;
        j^=bit;
        if (i<j) swap(a[i],a[j]);
    }
    // Butterfly operations
    for(int len=2;len<=n;len<<=1){
        double ang=2*PI/len*(invert?-1:1);
        cd wlen=cd(cos(ang),sin(ang));
        for(int i=0;i<n;i+=len){
            cd w=1;
            for(int j=0;j<len/2;j++){
                cd u=a[i+j],v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(invert)for(cd &x:a)x/=n;
}

// Multiply two polynomials using FFT
vector<int> mult(const vector<cd> &a,const vector<cd> &b){
    vector<cd> fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1;
    while(n<fa.size()+fb.size())n<<=1;
    fa.resize(n);fb.resize(n);
    fft(fa,false);fft(fb,false);
    // Point-wise multiplication
    for(int i=0;i<n;i++)fa[i]*=fb[i];
    fft(fa,true);
    vector<int> res(n);
    for(int i=0;i<n;i++)res[i]=round(fa[i].real());
    return res;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const long long INF = 1e18;

struct Edge {
    int to;
    ll capacity, flow, cost;
    int rev;
};

struct MCMF {
    int n, s, t;
    ll max_flow = 0, min_cost = 0;
    vector<vector<Edge>> adj;
    vector<ll> dist;
    vector<int> parent_edge, parent_node;
    vector<ll> h; // Potentials (Dijkstra)

    MCMF(int nodes) : n(nodes), adj(nodes + 1) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        Edge a = {v, cap, 0, cost, (int)adj[v].size()};
        Edge b = {u, 0, 0, -cost, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    void add_undirected_edge(int u, int v, ll cap, ll cost) {
        add_edge(u, v, cap, cost);
        add_edge(v, u, cap, cost);
    }

    bool spfa() {
        dist.assign(n + 1, INF);
        parent_node.assign(n + 1, -1);
        parent_edge.assign(n + 1, -1);
        vector<bool> in_queue(n + 1, false);
        queue<int> q;

        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;
            for (int i = 0; i < (int)adj[u].size(); ++i) {
                Edge &e = adj[u][i];
                if (e.capacity - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent_node[e.to] = u;
                    parent_edge[e.to] = i;
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    bool dijkstra() {
        dist.assign(n + 1, INF);
        parent_node.assign(n + 1, -1);
        parent_edge.assign(n + 1, -1);
        
        // Priority Queue {distance, u}
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            ll d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (int i = 0; i < (int)adj[u].size(); ++i) {
                Edge &e = adj[u][i];
                ll new_cost = e.cost + h[u] - h[e.to];
                
                if (e.capacity - e.flow > 0 && dist[e.to] > dist[u] + new_cost) {
                    dist[e.to] = dist[u] + new_cost;
                    parent_node[e.to] = u;
                    parent_edge[e.to] = i;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        return dist[t] != INF;
    }

    // use_dijkstra = true -> Chạy Dijkstra (An toàn)
    // use_dijkstra = false -> Chạy SPFA (Thường nhanh hơn nếu không bị test kill)
    void solve(int source, int sink, int k, bool use_dijkstra = true) {
        s = source; t = sink;
        max_flow = 0; min_cost = 0;
        h.assign(n + 1, 0);
        
        // Nếu đồ thị ban đầu có cạnh âm, phải chạy SPFA 1 lần để init h[]
        // Nếu đồ thị ban đầu toàn dương, h[] = 0 là ok.
        // spfa(); // Bỏ comment dòng này nếu input có cost âm

        while (true) {
            bool found_path = false;
            if (use_dijkstra) found_path = dijkstra();
            else found_path = spfa();

            if (!found_path) break;

            // Cập nhật Potentials sau mỗi lần tìm đường (Quan trọng cho Dijkstra)
            if (use_dijkstra) for (int i = 0; i <= n; ++i) if (dist[i] != INF) h[i] += dist[i];
            if (max_flow >= k) break;
            ll push = k - max_flow;
            int curr = t;
            while (curr != s) {
                int prev = parent_node[curr];
                int idx = parent_edge[curr];
                push = min(push, adj[prev][idx].capacity - adj[prev][idx].flow);
                curr = prev;
            }
            curr = t;
            while (curr != s) {
                int prev = parent_node[curr];
                int idx = parent_edge[curr];
                adj[prev][idx].flow += push;
                int rev_idx = adj[prev][idx].rev;
                adj[curr][rev_idx].flow -= push;
                curr = prev;
            }
            
            max_flow += push;
            
            // Tính cost:
            // Với SPFA: dist[t] là chi phí thực.
            // Với Dijkstra: h[t] là tổng chi phí thực tích lũy từ gốc.
            if (use_dijkstra) min_cost += push * h[t];
            else min_cost += push * dist[t];
        }
    }
};

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
const int G = 3; // Primitive root của 998244353

struct NTT {
    ll power(ll base, ll exp) {
        ll res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    ll modInverse(ll n) {
        return power(n, MOD - 2);
    }
    
    void ntt(vector<ll>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            ll wlen = power(G, (MOD - 1) / len);
            if (invert) wlen = modInverse(wlen);
            
            for (int i = 0; i < n; i += len) {
                ll w = 1;
                for (int j = 0; j < len / 2; j++) {
                    ll u = a[i + j], v = (a[i + j + len / 2] * w) % MOD;
                    a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                    a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                    w = (w * wlen) % MOD;
                }
            }
        }
        if (invert) {
            ll n_inv = modInverse(n);
            for (ll& x : a) x = (x * n_inv) % MOD;
        }
    }

    // Nhân đa thức
    vector<ll> mult(vector<ll> const& a, vector<ll> const& b) {
        vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size()) n <<= 1;
        fa.resize(n); fb.resize(n);
        ntt(fa, false);
        ntt(fb, false);
        for (int i = 0; i < n; i++) fa[i] = (fa[i] * fb[i]) % MOD;
        ntt(fa, true);
        while (fa.size() > 1 && fa.back() == 0) fa.pop_back();
        return fa;
    }
};

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct Tarjan {
    int n, time_counter, scc_count;
    vector<vector<int>> adj;
    vector<int> num, low, scc_id;
    stack<int> st;
    vector<bool> on_stack;

    Tarjan(int n) : n(n), adj(n + 1) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        num[u] = low[u] = ++time_counter;
        st.push(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (num[v] == 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], num[v]);
            }
        }
        if (low[u] == num[u]) {
            scc_count++;
            while (true) {
                int v = st.top();
                st.pop();
                on_stack[v] = false;
                scc_id[v] = scc_count;
                if (u == v) break;
            }
        }
    }

    void run() {
        time_counter = 0;
        scc_count = 0;
        num.assign(n + 1, 0);
        low.assign(n + 1, 0);
        scc_id.assign(n + 1, 0);
        on_stack.assign(n + 1, false);
        while (!st.empty()) st.pop();

        for (int i = 1; i <= n; i++) {
            if (num[i] == 0) dfs(i);
        }
    }
};

#include <bits/stdc++.h>
using namespace std;

struct Kuhn {
    int n, m; // n: số đỉnh trái, m: số đỉnh phải
    vector<vector<int>> adj;
    vector<int> match; // match[v] = u: Đỉnh v (phải) ghép với u (trái)
    vector<int> vis;   // Mảng đánh dấu phiên (timestamp)
    int timestamp;

    Kuhn(int n, int m) : n(n), m(m), adj(n + 1), match(m + 1, 0), vis(n + 1, 0), timestamp(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v); 
    }

    bool dfs(int u) {
        vis[u] = timestamp;
        for (int v : adj[u]) {
            if (match[v] == 0 || (vis[match[v]] != timestamp && dfs(match[v]))) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching() {
        int res = 0;
        vector<bool> used_left(n + 1, false);

        for (int u = 1; u <= n; ++u) {
            for (int v : adj[u]) {
                if (match[v] == 0) {
                    match[v] = u;
                    used_left[u] = true;
                    res++;
                    break;
                }
            }
        }
        for (int u = 1; u <= n; ++u) {
            if (used_left[u]) continue;
            timestamp++;
            if (dfs(u)) res++;
        }
        
        return res;
    }
};

// Nhan ma tran (fibo) 
#include <bits/stdc++.h>
#define ll long long
#define ii pair<int, int>
#define sz(s) (int)(s.size())
#define FOR(i, a, b) for(int i = (a), _b = b; i <= _b; i++)
#define FORd(i, a, b) for(int i = (a), _b = b; i >= _b; i--)
#define F0R(i, a) for(int i = 0; i < (a); i++)
#define F0Rd(i, a) for(int i = (a)-1; i >= 0; i--)
using namespace std;
 
const int N = 2e5 + 10, M = 19;
const int mod = (int)1e9 + 7;
 
struct Matrix{
    vector<vector<int>> mat;
    int row() const{return sz(mat);}
    int col() const{return sz(mat[0]);}
    Matrix(int r, int c): mat(r, vector<int>(c, 0)){}
    Matrix(const vector<vector<int>> &d): mat(d){}
 
    void out(){
        F0R(i, row()) F0R(j, col()) cout << mat[i][j] << " \n"[j == col()-1];
    }
 
    Matrix operator * (const Matrix &p) const{
        Matrix res = Matrix(row(), p.col());
        F0R(i, row()) F0R(j, p.col()) F0R(k, col()) (res.mat[i][j] += 1LL * mat[i][k] * p.mat[k][j] % mod) %= mod;
        return res;
    }
 
    Matrix identity(int n){
        Matrix res = Matrix(n, n);
        F0R(i, n) res.mat[i][i] = 1;
        return res;
    }
 
    Matrix expo(long long b){
        Matrix base = *this, res = identity(row());
        for(; b > 0; b >>= 1, base = base * base) if(b & 1) res = res * base;
        return res;
    }
};
 
void sol(void){
    long long n; cin >> n;
    Matrix x = Matrix(1, 2);
    x.mat[0][1] = 1;
 
    Matrix y = Matrix(2, 2);
    y.mat[0][1] = y.mat[1][0] = y.mat[1][1] = 1;
 
    cout << (x * y.expo(n)).mat[0][0] << '\n';
}
 
signed main(void){
    #define TASK "nhap"
    if(fopen(TASK".inp", "r")){
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
//    cin >> t;
    while(t--) sol();
}