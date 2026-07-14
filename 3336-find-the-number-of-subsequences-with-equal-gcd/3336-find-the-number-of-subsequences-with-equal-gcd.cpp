class Solution {
public:
    static constexpr int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<vector<long long>> dp(mx + 1, vector<long long>(mx + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            auto ndp = dp;

            for (int g1 = 0; g1 <= mx; g1++) {
                for (int g2 = 0; g2 <= mx; g2++) {

                    long long ways = dp[g1][g2];
                    if (ways == 0) continue;

                    // Put x into seq1
                    int ng1 = (g1 == 0) ? x : std::gcd(g1, x);
                    ndp[ng1][g2] = (ndp[ng1][g2] + ways) % MOD;

                    // Put x into seq2
                    int ng2 = (g2 == 0) ? x : std::gcd(g2, x);
                    ndp[g1][ng2] = (ndp[g1][ng2] + ways) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;

        for (int g = 1; g <= mx; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};