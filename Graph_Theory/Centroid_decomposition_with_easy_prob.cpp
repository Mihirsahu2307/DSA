#include <bits/stdc++.h>
// #define int long long
#define endl "\n"

// Centroid decomposition:
// Recursively split the subtrees about the centroid

// *** Important observation in the CD Tree ***
// The path joining 2 nodes A and B in og tree, will pass through the LCA of A and B in the
// CD tree

// Read: https://www.quora.com/profile/Abbas-Rangwala-13/Centroid-Decomposition-of-a-Tree
// and it will become obvious
// Proof: Consider A and B be the subtrees of node c in CD Tree,
// then for u in A and v in B, the path btw u and v must pass through c,
// this is because c is the node that splits the 2 trees A and B (kinda like articulation point)

// This property allows us to run most O(N) operations of the og tree in O(log N) in CD tree
// eg sum of weights on path u - v can be solved by knowing u - lca(u,v) and lca(u, v) - v


// Problem: https://codeforces.com/contest/321/problem/C
// For this problem, consider a solution where we assign the topmost level A, second level B
// and so on...

// This would work if the number of levels is <= 26
// Apply the same idea on the CD tree, where the number of levels is O(log N)

// Now think why does it work
// From the above mentioned property it is obvious that the centroids above the current level
// will exist in the path btw 2 nodes of current level, so the constraint of the problem
// is satisified (for this problem, the application was too obvious)


using namespace std;

const int N = 1e5 + 5;
vector<int> G[N];
int n, a, b, sub[N], rem[N];
char RANK[N];
// rem[u] tells me whether u has been removed from og tree (while decomposing)


// this dfs function will be called multiple times, because after splitting sub[u] will change
void dfs(int u, int p) {
    sub[u] = 1;
    for (auto& c : G[u]) {
        if (c != p && !rem[c]) {
            dfs(c, u);
            sub[u] += sub[c];
        }
    }
}

// idea: simply go to subtree with more than n / 2 nodes, until you reach a node
// where no subtrees satisfy the above condition
int centroid(int u, int p, int sz) {
    for (auto& c : G[u]) {
        // n needs to be replaced with current subtree size
        if (c != p && !rem[c] && sub[c] > sz / 2) {
            return centroid(c, u, sz);
        }
    }
    return u;
}

// for this problem, we don't really need to construct the CD tree,
// we can just go to the centroids and assign RANK
void decompose(int u, char r) {
    // consider we are given a tree rooted at u, and we want to decompose it
    // so first find the centroid of the tree and then decompose all the split trees
    // then we simply get centroids from each of those trees, and connect it to
    // current node u

    dfs(u, u); // find sub[u] for u in current tree
    int cn = centroid(u, u, sub[u]);
    RANK[cn] = r;
    rem[cn] = 1;

    for (auto& c : G[cn]) {
        // obviously, we need to check if that node (and consequently that subtree)
        // has already been removed
        if (!rem[c]) {
            decompose(c, r + 1);
        }
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
        cin >> n;
        for (int i = 0; i < n - 1; i ++) {
            cin >> a >> b;
            a--, b--;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        decompose(0, 'A');
        // cout << sub[8] << endl;
        // cout << centroid(0, 0) << endl;

        for (int i = 0; i < n; i ++) {
            cout << RANK[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}