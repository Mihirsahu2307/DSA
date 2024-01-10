// This is slightly wrong, need to also create a reach vector of pair of ints
// that will tell me the minimum edge needed to reach a node and the corresponding parent
// check cpalgo implementation using a set, Note: Use a set over pq to avoid MLE
// There the reach vector is replaced by min_e vector

int mst_cost() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    // need vis array because each node will be visited exactly once
    int vis[n] = {}, ans = 0, tot_vis = 0;
    while(!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if(vis[cur.second]) continue;
        vis[cur.second] = 1;
        ans += cur.first; 
        // here, we don't need a relaxation, we only update
        // ans when we visit a new node, that means a total of n - 1 edges will be included
        tot_vis ++; // just to check whether all of the n nodes are included finally
        for(auto& e : G[cur.second]) {
            if(vis[e.first]) continue;
            pq.push({e.second, e.first}); 
            // sort pq by edge weight, not sum of path
            // note that we include all edges to unvisited nodes,
            // and later choose the best one to visit some node
        }
    }
}