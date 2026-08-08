class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // Positions of every character in word1
        vector<vector<int>> pos(26);

        for (int i = 0; i < n; i++) {
            pos[word1[i] - 'a'].push_back(i);
        }

        // runStart[i] = start of the same-character contiguous run
        // runEnd[i]   = end of the same-character contiguous run
        vector<int> runStart(n), runEnd(n);

        for (int i = 0; i < n; ) {
            int j = i;

            while (j + 1 < n && word1[j + 1] == word1[i])
                j++;

            for (int k = i; k <= j; k++) {
                runStart[k] = i;
                runEnd[k] = j;
            }

            i = j + 1;
        }

        /*
            exact[j]:
            largest index i such that word2[j...]
            can be matched EXACTLY after index i.
        */
        vector<int> exact(m + 1, -1);

        // Empty suffix can start after any index
        exact[m] = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            int limit = exact[j + 1];

            if (limit < 0)
                continue;

            auto &v = pos[word2[j] - 'a'];

            auto it = upper_bound(v.begin(), v.end(), limit);

            if (it != v.begin()) {
                --it;
                exact[j] = *it - 1;
            }
        }

        /*
            one[j]:
            largest index i such that word2[j...]
            can be matched with EXACTLY ONE mismatch after i.
        */
        vector<int> one(m + 1, -1);

        // Empty string cannot have exactly one mismatch.
        one[m] = -1;

        for (int j = m - 1; j >= 0; j--) {

            // Case 1:
            // Current character is the mismatch,
            // remaining suffix must match exactly.
            int limit = exact[j + 1];

            if (limit >= 0) {
                int p;

                if (word1[limit] != word2[j]) {
                    p = limit;
                } else {
                    // Find the previous character different from word2[j].
                    p = runStart[limit] - 1;
                }

                if (p >= 0)
                    one[j] = max(one[j], p - 1);
            }

            // Case 2:
            // Current character matches,
            // suffix contains exactly one mismatch.
            limit = one[j + 1];

            if (limit >= 0) {
                auto &v = pos[word2[j] - 'a'];

                auto it = upper_bound(v.begin(), v.end(), limit);

                if (it != v.begin()) {
                    --it;
                    one[j] = max(one[j], *it - 1);
                }
            }
        }

        vector<int> ans;

        int prev = -1;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {

            int start = prev + 1;

            // ------------------------------------
            // Option 1: Take matching character
            // ------------------------------------
            int matchIndex = n;

            auto &v = pos[word2[j] - 'a'];

            auto it = lower_bound(v.begin(), v.end(), start);

            if (it != v.end()) {
                int p = *it;

                // Remaining suffix may contain at most one mismatch.
                if (p <= max(exact[j + 1], one[j + 1])) {
                    matchIndex = p;
                }
            }

            // ------------------------------------
            // Option 2: Use mismatch here
            // ------------------------------------
            int mismatchIndex = n;

            if (!usedMismatch && start < n) {

                int p;

                if (word1[start] != word2[j]) {
                    p = start;
                } else {
                    // Skip the contiguous block of the same character.
                    p = runEnd[start] + 1;
                }

                // After using mismatch, suffix must match exactly.
                if (p <= exact[j + 1]) {
                    mismatchIndex = p;
                }
            }

            // Choose smallest possible index.
            int chosen = min(matchIndex, mismatchIndex);

            if (chosen == n)
                return {};

            ans.push_back(chosen);

            if (word1[chosen] != word2[j])
                usedMismatch = true;

            prev = chosen;
        }

        return ans;
    }
};