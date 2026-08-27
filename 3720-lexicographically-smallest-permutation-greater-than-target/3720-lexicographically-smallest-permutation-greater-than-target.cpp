class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Try changing target from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Count characters used in target[0 ... i-1]
            vector<int> remaining = freq;

            bool possible = true;

            for (int j = 0; j < i; j++) {
                int c = target[j] - 'a';

                if (remaining[c] == 0) {
                    possible = false;
                    break;
                }

                remaining[c]--;
            }

            if (!possible) {
                continue;
            }

            // Find the smallest character greater than target[i]
            int cur = target[i] - 'a';
            int bigger = -1;

            for (int c = cur + 1; c < 26; c++) {
                if (remaining[c] > 0) {
                    bigger = c;
                    break;
                }
            }

            if (bigger != -1) {

                string ans = target.substr(0, i);

                // Make the first difference here
                ans += char('a' + bigger);

                remaining[bigger]--;

                // Fill the rest with smallest characters
                for (int c = 0; c < 26; c++) {
                    while (remaining[c] > 0) {
                        ans += char('a' + c);
                        remaining[c]--;
                    }
                }

                return ans;
            }
        }

        return "";
    }
};