class Solution {
public:

    string makePalindrome(const string& half, char mid, int n) {
        string ans = half;

        if (n % 2 == 1)
            ans += mid;

        string rev = half;
        reverse(rev.begin(), rev.end());

        ans += rev;

        return ans;
    }

    string lexPalindromicPermutation(string s, string target) {

        int n = s.size();
        int halfLen = n / 2;

        // Count characters
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        // Find middle character
        char mid = 0;
        int odd = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                odd++;
                mid = char('a' + i);
            }
        }

        // A palindrome is impossible
        if (odd > 1)
            return "";

        // Counts for first half
        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++)
            halfCnt[i] = cnt[i] / 2;

        /*
            First try:
            Can target's first half itself be used?

            If yes, construct its palindrome.
            It is automatically the smallest possible candidate
            if that palindrome is greater than target.
        */

        string targetHalf = target.substr(0, halfLen);

        vector<int> rem = halfCnt;
        bool possible = true;

        for (char c : targetHalf) {
            if (rem[c - 'a'] == 0) {
                possible = false;
                break;
            }
            rem[c - 'a']--;
        }

        if (possible) {

            string candidate =
                makePalindrome(targetHalf, mid, n);

            if (candidate > target)
                return candidate;
        }

        /*
            Target's first half cannot directly give the answer.

            Find the smallest permutation of halfCnt
            which is lexicographically greater than targetHalf.

            We try changing one position:
                targetHalf[0 ... i-1]  = same
                position i              = smallest char > targetHalf[i]
                remaining               = sorted ascending
        */

        rem = halfCnt;

        string answer = "";

        for (int i = 0; i < halfLen; i++) {

            // Try making current position greater
            for (int c = targetHalf[i] - 'a' + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                vector<int> temp = rem;

                // Use the greater character
                temp[c]--;

                string half = targetHalf.substr(0, i);
                half += char('a' + c);

                // Fill remaining characters in smallest order
                for (int j = 0; j < 26; j++) {
                    half += string(temp[j], char('a' + j));
                }

                // Because this is the last possible position
                // that gives the smallest answer, overwrite answer.
                answer = half;
                break;
            }

            // Continue matching target prefix
            int x = targetHalf[i] - 'a';

            if (rem[x] == 0)
                break;

            rem[x]--;
        }

        if (answer.empty())
            return "";

        return makePalindrome(answer, mid, n);
    }
};