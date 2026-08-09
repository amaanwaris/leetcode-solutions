#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    long long weightedSum(vector<int>& parent, vector<int>& nums) {
        int n = parent.size();
        
        // Build adjacency list for the tree
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        
        // Compute depth of each node using BFS
        vector<int> depth(n, 0);
        depth[0] = 1;
        int h = 1;
        
        queue<int> q;
        q.push(0);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            h = max(h, depth[u]);
            
            for (int v : adj[u]) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
        
        // Compute total weighted sum
        long long totalSum = 0;
        for (int i = 0; i < n; ++i) {
            long long weight = (long long)nums[i] * (h - depth[i] + 1);
            totalSum += weight;
        }
        
        return totalSum;
    }
};