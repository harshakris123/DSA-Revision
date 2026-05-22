/*
QUESTION:
Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges, 
check whether it contains any cycle or not.

APPROACH:
- To check for cycles in a directed graph, we can use Depth-First Search (DFS) with backtracking.
- During the DFS, we maintain a visited array to keep track of nodes that have been visited.
- We perform DFS from each unvisited node to explore the graph and check for cycles.
- If we encounter a node that is already visited in the current DFS traversal, it means we have found a cycle, and we return true.
- If we complete the DFS for all nodes without finding any cycle, we return false.
In a directed graph, vis[] alone cannot detect cycles because revisiting a previously explored node does not always form a cycle. 
We need pathVis[] to check whether a node is part of the current DFS recursion path (back edge), which confirms a cycle.

COMPLEXITY ANALYSIS:
- Time Complexity: O(V + E), where V is the number of vertices (nodes) and E is the number of edges in the graph. We visit each node and each edge exactly once during the DFS.
- Space Complexity: O(V), where V is the number of vertices (nodes) in the graph. We use additional space to store the visited status of the nodes.
*/

bool dfscheck(int node, vector<int> adj[], int vis[], int pathvis[])
    {
        vis[node] = 1;
        pathvis[node] = 1;
        for(auto it : adj[node])
        {
            if(!vis[it])
            {
                if(dfscheck(it, adj, vis, pathvis))
                {
                    return true;
                }
            }else if(pathvis[it] == 1)
            {
                return true;
            }
        }

        pathvis[node] = 0;
        return false;
    }
public:
    bool isCyclic(int N, vector<int> adj[]) {
        int vis[N] = {0};
        int pathvis[N] = {0};

        for(int i=0; i<N; i++)
        {
            if(!vis[i])
            {
                if(dfscheck(i, adj, vis, pathvis) == true)
                {
                    return true;
                }
            }
        }
        return false;
    }
