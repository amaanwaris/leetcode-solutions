class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        int left = 0;
        int ones = 0;

        string ans = "";

        for (int right = 0; right < n; right++) {

            // Add current character
            if (s[right] == '1') {
                ones++;
            }

            // More than k ones -> shrink
            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            // Remove unnecessary leading zeros
            while (ones == k && s[left] == '0') {
                left++;
            }

            // We have exactly k ones
            if (ones == k) {

                string curr = s.substr(left, right - left + 1);

                // First valid answer
                if (ans == "") {
                    ans = curr;
                }
                // Shorter substring
                else if (curr.size() < ans.size()) {
                    ans = curr;
                }
                // Same length -> lexicographically smaller
                else if (curr.size() == ans.size() && curr < ans) {
                    ans = curr;
                }
            }
        }

        return ans;
    }
};