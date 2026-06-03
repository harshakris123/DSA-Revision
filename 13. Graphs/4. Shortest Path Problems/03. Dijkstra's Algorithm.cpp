/*
QUESTION:
Given a weighted, undirected, and connected graph of V vertices and an adjacency list 'adj', where 'adj[i]' is a list of lists containing two integers where the first integer of each list j denotes there is an edge between node i and node j, and the second integer corresponds to the weight of that edge. You are also given the source vertex S. You need to find the shortest distance of all vertices from the source vertex S. You have to return a list of integers denoting the shortest distance between each node and the source vertex S.

APPROACH:
- We can use Dijkstra's algorithm to find the shortest distance from the source vertex to all other vertices in a weighted graph.
- The algorithm maintains a priority queue (min-heap) to store the vertices based on their tentative distances from the source vertex. We start with the source vertex and update the distances of its neighbors, pushing them into the priority queue.
- We continue this process until all vertices are visited and their distances are finalized. The priority queue ensures that we always pick the vertex with the minimum tentative distance for processing.
- We initialize the distance array 'dis' with a large value (infinity) for all vertices, except the source vertex whose distance is set to 0.
- We push the source vertex into the priority queue along with its distance, and then perform Dijkstra's algorithm.
- After the algorithm completes, we have the shortest distances of all vertices from the source vertex in the 'dis' array.

COMPLEXITY ANALYSIS:
- Time Complexity: O(E + log(V)), where E is the number of edges and V is the number of vertices in the graph. The time complexity is dominated by the priority queue operations in Dijkstra's algorithm.
- Space Complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph. We use additional space for the adjacency list, the distance array, and the priority queue.
*/

#define P pair<int,int>

class Solution{
public:
    vector<int> dijkstra(int V, vector<vector<int>> edges, int S) {
        priority_queue<P, vector<P>, greater<P>> pq;
         vector<vector<vector<int>>> adj(V);
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];
            
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt}); // assuming undirected graph
        }
               
        vector<int> dist(V, 1e9);
        dist[S] = 0;
        pq.push({0,S});

        while(!pq.empty())
        {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for(auto it : adj[node])
            {
                int adjnode = it[0];
                int wt = it[1];

                if(dis + wt < dist[adjnode])
                {
                    dist[adjnode] = dis + wt;
                    pq.push({dist[adjnode], adjnode});
                }
            }
        }
        return dist;
    }
};
