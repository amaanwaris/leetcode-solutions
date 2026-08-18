class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<int, vector<int>> pos;

        // Store positions of every number
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }

        int ans = -1;

        for (auto &[x, v] : pos) {
            // Set of window starting positions containing x
            vector<pair<int, int>> intervals;

            for (int p : v) {
                int L = max(0, p - k + 1);
                int R = min(p, n - k);

                intervals.push_back({L, R});
            }

            // Merge intervals
            sort(intervals.begin(), intervals.end());

            int covered = 0;
            int L = intervals[0].first;
            int R = intervals[0].second;

            for (int i = 1; i < intervals.size(); i++) {
                if (intervals[i].first <= R + 1) {
                    R = max(R, intervals[i].second);
                } else {
                    covered += R - L + 1;

                    L = intervals[i].first;
                    R = intervals[i].second;
                }
            }

            covered += R - L + 1;

            // x appears in exactly one subarray
            if (covered == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};