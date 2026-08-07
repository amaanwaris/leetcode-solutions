#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    // Prime factor counts (2, 3, 5, 7) for digits 0-9
    const int digit_factors[10][4] = {
        {0, 0, 0, 0}, // 0
        {0, 0, 0, 0}, // 1
        {1, 0, 0, 0}, // 2
        {0, 1, 0, 0}, // 3
        {2, 0, 0, 0}, // 4
        {0, 0, 1, 0}, // 5
        {1, 1, 0, 0}, // 6
        {0, 0, 0, 1}, // 7
        {3, 0, 0, 0}, // 8
        {0, 2, 0, 0}  // 9
    };

    // Calculate minimum number of digits required to satisfy remaining factors (r2, r3, r5, r7)
    int min_digits(int r2, int r3, int r5, int r7) {
        r2 = max(0, r2);
        r3 = max(0, r3);
        r5 = max(0, r5);
        r7 = max(0, r7);

        int base_len = r5 + r7;
        int min_23 = 1e9;

        // Try using k sixes (k = 0 or 1)
        for (int k = 0; k <= 1; ++k) {
            int rem2 = max(0, r2 - k);
            int rem3 = max(0, r3 - k);
            int d2 = (rem2 + 2) / 3; // Pack 2s into 8s
            int d3 = (rem3 + 1) / 2; // Pack 3s into 9s
            min_23 = min(min_23, k + d2 + d3);
        }

        return base_len + min_23;
    }

    // Greedily fill a string of length 'len' to satisfy required prime factors
    string fill_greedy(int len, vector<int> req) {
        string res = "";
        for (int i = 0; i < len; ++i) {
            int rem_len = len - 1 - i;
            for (int d = 1; d <= 9; ++d) {
                vector<int> next_req = req;
                for (int k = 0; k < 4; ++k) {
                    next_req[k] = max(0, next_req[k] - digit_factors[d][k]);
                }
                if (min_digits(next_req[0], next_req[1], next_req[2], next_req[3]) <= rem_len) {
                    res += to_string(d);
                    req = next_req;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        // 1. Factorize t into prime factors (2, 3, 5, 7)
        vector<int> req(4, 0);
        long long temp = t;
        int primes[4] = {2, 3, 5, 7};
        for (int i = 0; i < 4; ++i) {
            while (temp % primes[i] == 0) {
                req[i]++;
                temp /= primes[i];
            }
        }
        if (temp > 1) return "-1"; // Invalid prime factor

        int n = num.size();

        // 2. Check if num itself is zero-free and valid
        bool has_zero = false;
        vector<int> num_req = req;
        for (char c : num) {
            if (c == '0') {
                has_zero = true;
                break;
            }
            for (int k = 0; k < 4; ++k) {
                num_req[k] = max(0, num_req[k] - digit_factors[c - '0'][k]);
            }
        }

        if (!has_zero && min_digits(num_req[0], num_req[1], num_req[2], num_req[3]) == 0) {
            return num;
        }

        // 3. Find first zero position
        int zero_idx = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                zero_idx = i;
                break;
            }
        }

        // Precompute cumulative requirements along the valid prefix of num
        vector<vector<int>> pref_req(n + 1, req);
        for (int i = 0; i < zero_idx; ++i) {
            int d = num[i] - '0';
            for (int k = 0; k < 4; ++k) {
                pref_req[i + 1][k] = max(0, pref_req[i][k] - digit_factors[d][k]);
            }
        }

        // 4. Try matching the longest prefix and branching at position i
        int limit = min(n - 1, zero_idx);
        for (int i = limit; i >= 0; --i) {
            int start_digit = num[i] - '0' + 1;
            for (int d = start_digit; d <= 9; ++d) {
                vector<int> cur_req = pref_req[i];
                for (int k = 0; k < 4; ++k) {
                    cur_req[k] = max(0, cur_req[k] - digit_factors[d][k]);
                }
                int rem_len = n - 1 - i;
                if (min_digits(cur_req[0], cur_req[1], cur_req[2], cur_req[3]) <= rem_len) {
                    string ans = num.substr(0, i) + to_string(d);
                    ans += fill_greedy(rem_len, cur_req);
                    return ans;
                }
            }
        }

        // 5. If no length-n string works, increase string length
        int target_len = max(n + 1, min_digits(req[0], req[1], req[2], req[3]));
        return fill_greedy(target_len, req);
    }
};