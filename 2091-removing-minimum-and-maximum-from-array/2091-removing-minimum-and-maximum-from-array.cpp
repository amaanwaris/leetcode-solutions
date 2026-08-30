class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find index of minimum and maximum
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // minIndex should be the smaller index
        // maxIndex should be the larger index
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // Three possibilities:
        // 1. Remove both from front
        int option1 = right + 1;

        // 2. Remove both from back
        int option2 = n - left;

        // 3. Remove one from front and one from back
        int option3 = (left + 1) + (n - right);

        return min({option1, option2, option3});
    }
};