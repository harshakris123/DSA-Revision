/*
QUESTION:
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take 
course bi first if you want to take course ai.

Return true if you can finish all courses. Otherwise, return false.

APPROACH:
- We can model the problem as a directed graph, where each course is a node, 
and a prerequisite pair [ai, bi] indicates a directed edge from course bi to course ai.
- To check if we can finish all courses, we need to ensure that the directed graph is a DAG 
(Directed Acyclic Graph) with no cycles.
- If there are cycles in the graph, it means there is a circular dependency between courses, 
and we cannot finish all courses in such cases.
- To check for cycles, we can use Kahn's algorithm for Topological Sorting.
- If we can perform a successful Topological Sort (i.e., there is no cycle), 
then it means we can finish all courses.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N + E), where N is the number of courses (nodes) and E is the number of prerequisites (edges) in the graph. We perform a BFS-like traversal of all nodes and edges.
- Space Complexity: O(N + E), where N is the number of courses (nodes) and E is the number of prerequisites (edges) in the graph. We use additional space to store the adjacency list and indegree of each node.
*/

 bool canFinish(int V, vector<vector<int>> arr) {
        vector<int> adj[V];
        vector<int> indegree(V, 0);
        
        for(auto it : arr)
        {
            indegree[it[0]]++;
            adj[it[1]].push_back(it[0]);
        }

        queue<int> q;
        for(int i=0; i<V; i++){
            if(indegree[i] == 0) q.push(i);
        }

        vector<int> topo;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push_back(node);

            for(auto it : adj[node])
            {
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }
        if(topo.size() == V) return true;
        return false;
    }
