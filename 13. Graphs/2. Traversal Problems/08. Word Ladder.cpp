/*
QUESTION:
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a 
sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
1. Every adjacent pair of words differs by a single letter.
2. Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
3. sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words 
in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

APPROACH:
    We can think of this problem as a graph problem, where:
    Each word acts as a node
    There is an edge between two words if they differ by exactly one character.
    Since every transformation changes one letter at a time, and we need the shortest transformation sequence, 
    this becomes a shortest path problem in an unweighted graph.
    For shortest path in an unweighted graph, Breadth First Search (BFS) is the best choice because:
    BFS explores level by level
    The first time we reach the targetWord, it is guaranteed to be the minimum number of transformations.

    Instead of explicitly building an adjacency list (which is expensive), we generate neighbours dynamically.
    For every word:
    Change each character position one by one
    Try all characters from 'a' to 'z'
    If the newly formed word exists in wordList, it is a valid transformation.
    */

    int wordLadderLength(string startWord, string targetWord,
                         vector<string> &wordList) {
        queue<pair<string,int>> q;
        set<string> st(wordList.begin(), wordList.end());
        st.erase(startWord);
        q.push({startWord, 1});

        while(!q.empty())
        {
            string word = q.front().first;
            int steps =  q.front().second;
            if(word == targetWord) return steps;
            q.pop();

            for(int i=0; i<word.size(); i++)
            {
                char original = word[i];
                for(char ch='a'; ch <='z'; ch++)
                {
                    word[i] = ch;
                    if(st.find(word) != st.end())
                    {
                        st.erase(word);
                        q.push({word, steps+1});
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
