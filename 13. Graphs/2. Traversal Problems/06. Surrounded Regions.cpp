/*
QUESTION:-
Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded
by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

APPROACH:
- We can use Depth-First Search (DFS) to find all regions that are surrounded by 'X'.
- First, we initialize a copy of the board called 'vis' to store the visited status of each cell.
- Then, we perform a DFS starting from all border cells that have 'O's. During the DFS, we mark all 
connected 'O's as visited by changing them to a special character, such as '#', in the 'vis' matrix.
- After performing DFS from border cells, all remaining '#'s in the 'vis' matrix represent regions that are not surrounded by 'X'.
- Finally, we update the original board by flipping all remaining 'O's to 'X'.

COMPLEXITY ANALYSIS:
- Time Complexity: O(m * n), where m is the number of rows and n is the number of columns in the matrix. In the worst case, we may need to visit all the cells of the matrix during DFS.
- Space Complexity: O(m * n), where m is the number of rows and n is the number of columns in the matrix. We use additional space for the 'vis' matrix.
*/

    void dfs(int row, int col,vector<vector<char>> &mat, vector<vector<int>> &vis, int delrow[], int delcol[]){
        int n = mat.size();
        int m = mat[0].size();
        vis[row][col] = 1;

        for(int i=0; i<4; i++){
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            if(nrow >=0 && nrow<n && ncol >=0 && ncol<m 
                && !vis[nrow][ncol] && mat[nrow][ncol]=='O'){
                    dfs(nrow, ncol, mat, vis, delrow, delcol);
                }
        }
    }
    vector<vector<char>> fill(vector<vector<char>> mat) {
       int n = mat.size();
       int m = mat[0].size();

       vector<vector<int>> vis(n, vector<int>(m,0));
       int delrow[] = {-1,0,+1,0};
       int delcol[] = {0,+1,0,-1};

       // implement dfs on boundaries and mark all connected 'O's as visited
       for(int i=0; i<n;i++){
        if(mat[i][0] == 'O'){
            dfs(i,0,mat,vis,delrow,delcol);
        }
        if(mat[i][m-1]=='O'){
            dfs(i,m-1,mat,vis,delrow,delcol);
        }
       }

       for(int j=0; j<m;j++){
        if(mat[0][j]=='O'){
            dfs(0,j,mat,vis,delrow,delcol);
        }
        if(mat[n-1][j]=='O'){
            dfs(n-1,j,mat,vis,delrow,delcol);
        }
       }
        // flip all unvisited 'O's to 'X's as boundary 'O's and their connected 
        //  'O's are marked as visited
       for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(mat[i][j]=='O' && vis[i][j]==0){
                mat[i][j] = 'X';
            }
        }
       }
       return mat;
    }
