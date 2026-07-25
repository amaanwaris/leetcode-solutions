class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return 1;

        unordered_set<int> pairXor;
        unordered_set<int> ans;

        // Store all unique XORs of two distinct elements
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairXor.insert(nums[i] ^ nums[j]);
            }
        }

        // Combine every pair XOR with every element
        for (int x : pairXor) {
            for (int num : nums) {
                ans.insert(x ^ num);
            }
        }

        return ans.size();
    }
};