#include <vector>
#include <string>
#include <algorithm>
#include <bit>

using namespace std;

struct Group {
    int start;
    int length;
};

// Sparse Table for Range Maximum Queries (RMQ)
class SparseTable {
public:
    SparseTable(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;
        int max_log = std::__lg(n) + 1;
        st.assign(max_log, vector<int>(n));
        copy(nums.begin(), nums.end(), st[0].begin());

        for (int i = 1; i < max_log; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int i = std::__lg(r - l + 1);
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }

private:
    int n;
    vector<vector<int>> st;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int ones = count(s.begin(), s.end(), '1');

        auto [zeroGroups, zeroGroupIndex] = getZeroGroups(s);
        int numZeroGroups = zeroGroups.size();

        // Adjacent zero group merged lengths calculate karna
        vector<int> zeroMergeLengths;
        for (int i = 0; i < numZeroGroups - 1; ++i) {
            zeroMergeLengths.push_back(zeroGroups[i].length + zeroGroups[i + 1].length);
        }

        SparseTable st(zeroMergeLengths);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            int lGroup = zeroGroupIndex[l];
            int rGroup = zeroGroupIndex[r];

            // Substring boundary elements process karna
            int left = (lGroup == -1) ? -1 : (zeroGroups[lGroup].length - (l - zeroGroups[lGroup].start));
            int right = (rGroup == -1) ? -1 : (r - zeroGroups[rGroup].start + 1);

            int startAdjacentGroupIndex = lGroup + 1;
            int endAdjacentGroupIndex = (s[r] == '1') ? (rGroup - 1) : (rGroup - 2);

            int activeSections = ones;

            if (s[l] == '0' && s[r] == '0' && lGroup + 1 == rGroup) {
                activeSections = max(activeSections, ones + left + right);
            } else if (startAdjacentGroupIndex <= endAdjacentGroupIndex) {
                activeSections = max(activeSections, ones + st.query(startAdjacentGroupIndex, endAdjacentGroupIndex));
            }

            if (s[l] == '0' && lGroup + 1 <= ((s[r] == '1') ? rGroup : rGroup - 1)) {
                activeSections = max(activeSections, ones + left + zeroGroups[lGroup + 1].length);
            }

            if (s[r] == '0' && lGroup < rGroup - 1) {
                activeSections = max(activeSections, ones + right + zeroGroups[rGroup - 1].length);
            }

            ans.push_back(activeSections);
        }

        return ans;
    }

private:
    pair<vector<Group>, vector<int>> getZeroGroups(const string& s) {
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(s.length(), -1);

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
            }
            zeroGroupIndex[i] = zeroGroups.empty() ? -1 : ((int)zeroGroups.size() - 1);
        }

        return {zeroGroups, zeroGroupIndex};
    }
};