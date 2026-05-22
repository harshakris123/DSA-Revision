/*
QUESTION:
/*
APPROACH:
- A graph is bipartite if we can divide all nodes into two groups such that no two adjacent nodes belong to the same group.

- To check this, we use DFS and assign colors to nodes:
    - Color 1 → Group A
    - Color -1 → Group B

- We start from an unvisited node and assign it a color.

- During DFS:
    - If a neighboring node is uncolored, we assign it the opposite color and continue DFS.
    - If a neighboring node already has the same color as the current node, it means two 
    adjacent nodes are in the same group, so the graph is NOT bipartite.

- Since the graph may be disconnected, we run DFS for every unvisited node.

- If we are able to color the entire graph without conflicts, the graph is bipartite.

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E)
    - We visit every node once and every edge once.

- Space Complexity: O(V)
    - Extra space is used for:
        1. Color array
        2. DFS recursion stack
*/

bool dfs(int node, int color, vector<vector<int>>& adj, vector<int>& vis){
    vis[node] = color;
    for(auto v : adj[node]){
        if(!vis[v] && !dfs(v, -color, adj, vis)){
            return false;
        }
        if(vis[v] == color){
            return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> vis(n);
    for(int i = 0; i < n; i++){
        if(!vis[i] && !dfs(i, 1, graph, vis)){
            return false;
        }
    }
    return true;
}
