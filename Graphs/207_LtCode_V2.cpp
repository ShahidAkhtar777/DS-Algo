// ::Question::
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
// You are given an array prerequisites where prerequisites[i] = [ai, bi] 
// indicates that you must take course bi first if you want to take course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

// Return true if you can finish all courses. Otherwise, return false.


// Approach we need to find if the directed graph is cyclic
// If its cyclic then can't complete all course.
// Below is DFS implementation 

class Solution {
public:
    bool dfs_helper(int src, vector<int> &visited, vector<int> &path, vector<int> map[]){
        visited[src] = 1;
        path[src] = 1;

        for(auto nbr: map[src]){
            if(path[nbr])
                return false;
            else if(!visited[nbr]){
                bool possible = dfs_helper(nbr, visited, path, map);
                if(!possible)
                    return false;
            }
        }
        path[src] = false;
        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> map[numCourses];

        for(auto course: prerequisites){
            int src = course[1];
            int dest = course[0];
            map[src].push_back(dest);
        }

        vector<int> visited(numCourses+1, 0), path(numCourses+1, 0);

        for(int i=0;i<numCourses;i++){
            if(!visited[i]){
                bool possible = dfs_helper(i, visited, path, map);
                if(!possible)
                    return false;
            }
        }
        return true;
    }
};