/*
QUESTION:
Given a sorted dictionary of an alien language having N words and k starting alphabets of the standard dictionary. 
Find the order of characters in the alien language.

APPROACH:
- We are given a sorted dictionary of an alien language.
- To find the order of characters in the alien language, we can use a directed graph approach along with topological sorting.
- We create a directed graph where each node represents a character, and there is a directed edge from node 'a' to node 'b' 
if character 'a' comes before character 'b' in the alien language.
- We also keep track of the indegree of each node, which represents the number of characters that come before it in the alien language.
- We iterate through the dictionary and set the directed edges and indegrees accordingly.
- We then start with the nodes having an indegree of 0 (i.e., the characters that come first in the alien language) and perform a BFS-like traversal.
- During the traversal, we keep reducing the indegree of the nodes that come after the current node.
- The characters that become terminal nodes (i.e., their indegree becomes 0) during the traversal are the characters that come last in the alien language.
- We construct the order of characters based on the BFS traversal, and that will be the correct order of characters in the alien language.

COMPLEXITY ANALYSIS:
- Time Complexity: O(N), where N is the number of words in the dictionary. We iterate through the dictionary once to set the directed edges and indegrees.
- Space Complexity: O(K), where K is the number of starting alphabets in the standard dictionary. We use additional space to store the directed graph and indegrees.
*/

vector<int> toposort(int v, vector<int> adj[])
    {
        vector<int> indegree(v,0);
        for(int i=0; i<v; i++)
        {
            for(auto it : adj[i])
            {
                indegree[it]++;
            }
        }
        queue<int> q;
        for(int i=0; i<v; i++)
        {
            if(indegree[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> topo;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }   
        return topo;
    }
public:
	string findOrder(string dict[], int N, int K) {
		vector<int> adj[K];
        for(int i=0; i<N-1;i++)
        {
            string s1 = dict[i];
            string s2 = dict[i+1];
            int len = min(s1.size(), s2.size());

            for(int j=0; j<len;j++)
            {
                if(s1[j] != s2[j])
                {
                    adj[s1[j]-'a'].push_back(s2[j]-'a');
                    break;
                }
            }
        }
        vector<int> topo = toposort(K, adj);
        string s;
        for(int i=0; i<K;i++){
            s = s + char(topo[i]+'a');
        }
        return s;
	}
