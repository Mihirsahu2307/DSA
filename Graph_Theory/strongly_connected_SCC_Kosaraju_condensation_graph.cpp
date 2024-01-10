#include <bits/stdc++.h>
#define int long long
#define endl "\n"

using namespace std;


// Problem Link: https://codeforces.com/contest/999/problem/E

// Solution Idea:
// The previous solution didn't work because it was essentially just finding the number
// of connected components (directionless) in the graph (verify why)

// But the problem is, not all nodes in that component would be reachable from the
// entry node of our choice
// So either we need to choose an appropriate entry node to connect to the capital
// such that all other nodes are in the subtree of that node
// or we need to ensure that each node in the component is reachable from every other node (SCC)

// Note that the first option of choosing appt. entry node will not always be possible
// besides, we already have a hint about SCC from our second point, so explore in that direction

// Another observation to make is while trying out few examples, we see a topological pattern
// That hints us that the problem can be solved via SCC condensation

// Now that we have a hint about SCC, we can also realize that we just need to count the number
// of SCC in the graph which aren't already connected to the capital SCC
// Further, it can be easily deduced that any SCC that is reachable from another SCC doesn't need
// to be connected directly to the capital, we can just connect the parent SCC

// So 1 solution could be to count the number of SCC with indegree = 0, except the capital SCC

// Now, if we prove the optimality, we are done. Intuitively it seems correct so let's just go with it


// Intuition of Kosaraju Algo:
// DFS1 is simply topological sort, when we reverse the tout array
// we end up with the root nodes first and then the rest

// DFS2 requires transposing the graph, this can be understood by visualising on paper
// Note that the condensated graph is a DAG, this is important to know because
// if we reverse the edges of the condensated graph and start from the root, then we won't
// be visiting any other nodes

// This is exactly what transposing the graph does
// When we sort the nodes after DFS1, we have the components in reversed topological order
// of the condensated graph, when we reverse this graph: call it Gct
// then we will visit the components of Gct in reversed topological order
// this means there is no way to reach the nodes of another component from DFS2,
// because:
// 1) the original edges u (current SCC) -> v (different SCC) have been reversed
// 2) Edges of type v (diff SCC) -> u (current SCC) will not be visited as we are visiting
// the components in reversed topological order


const int N = 1e5 + 5;
vector<int> G[N], GT[N], G_condense[N]; // assume atmost N SCCs
int n, m, s, u, v, cur = 1, vis[N] = {}, C[N] = {}, indeg[N] = {};


// The 2 main dfs functions needed:
void dfs1(int u, vector<int> &order) {
    vis[u] = 1;
    for (auto& c : G[u]) {
        if (!vis[c]) dfs1(c, order);
    }
    order.push_back(u);
}

void dfs2(int u, vector<int> &comp) {
    vis[u] = 1;
    comp.push_back(u);
    for (auto& c : GT[u]) {
        if (!vis[c]) dfs2(c, comp);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int T = 1;
    // cin >> T;
    for (int t = 1; t < T + 1; t ++) {
        // for the first component (including the source), we can't include nodes
        // that run into this component. For the rest, we can

        cin >> n >> m >> s;
        for (int i = 0 ; i < m; i ++) {
            cin >> u >> v;
            G[u].push_back(v);
            GT[v].push_back(u);
        }

        vector<int> order;
        for (int i = 1; i <= n; i ++) {
            if (!vis[i]) {
                dfs1(i, order);
            }
        }
        reverse(order.begin(), order.end()); // don't forget to reverse!


        vector<int> comp_roots;
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; i ++) {
            int u = order[i];
            if (!vis[u]) {
                // Here we will find the connected components
                vector<int> comp;
                dfs2(u, comp);
                comp_roots.push_back(u); // This vector comes in handy when you want to iterate over components

                int is_capital = 0;
                for (auto& c : comp) {
                    if (c == s) is_capital = 1;
                    C[c] = u;
                }
                if (is_capital) {
                    comp_roots.pop_back();
                    comp_roots.push_back(s);
                    for (auto& c : comp) {
                        C[c] = s;
                    }
                }
            }
        }

        // here we will build the condensation graph (not needed for the problem tho)
        for (int i = 1; i <= n; i ++) {
            for (auto& c : G[i]) {
                if (C[i] != C[c]) {
                    // different components
                    G_condense[C[i]].push_back(C[c]);
                    indeg[C[c]] ++;
                }
            }
        }
        // cout << indeg[3] << endl;
        int ans = 0;
        for (auto& root : comp_roots) {
            if (root == s) continue;
            ans += (indeg[root] == 0);
        }
        cout << ans << endl;
    }

    return 0;
}