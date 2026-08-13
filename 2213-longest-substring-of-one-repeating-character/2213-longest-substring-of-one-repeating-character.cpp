class Solution {
public:
    struct Node {
        int pref[26], suff[26], best[26];

        Node() {
            for (int i = 0; i < 26; i++) {
                pref[i] = suff[i] = best[i] = 0;
            }
        }
    };

    vector<Node> tree;
    string s;

    void build(int idx, int l, int r) {
        if (l == r) {
            int c = s[l] - 'a';

            tree[idx].pref[c] = 1;
            tree[idx].suff[c] = 1;
            tree[idx].best[c] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);

        pull(idx, l, r);
    }

    void pull(int idx, int l, int r) {
        int mid = (l + r) / 2;

        Node &left = tree[idx * 2];
        Node &right = tree[idx * 2 + 1];
        Node &cur = tree[idx];

        int leftLen = mid - l + 1;
        int rightLen = r - mid;

        for (int c = 0; c < 26; c++) {

            cur.pref[c] = left.pref[c];
            cur.suff[c] = right.suff[c];

            cur.best[c] = max(left.best[c], right.best[c]);

            // substring crossing the middle
            cur.best[c] = max(
                cur.best[c],
                left.suff[c] + right.pref[c]
            );

            // Entire left part consists of same character
            if (left.pref[c] == leftLen) {
                cur.pref[c] = leftLen + right.pref[c];
            }

            // Entire right part consists of same character
            if (right.suff[c] == rightLen) {
                cur.suff[c] = rightLen + left.suff[c];
            }
        }
    }

    void update(int idx, int l, int r, int pos, char ch) {
        if (l == r) {
            tree[idx] = Node();

            int c = ch - 'a';

            tree[idx].pref[c] = 1;
            tree[idx].suff[c] = 1;
            tree[idx].best[c] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, ch);
        else
            update(idx * 2 + 1, mid + 1, r, pos, ch);

        pull(idx, l, r);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        this->s = s;

        int n = s.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {

            int pos = queryIndices[i];
            char ch = queryCharacters[i];

            s[pos] = ch;

            update(1, 0, n - 1, pos, ch);

            int mx = 0;

            for (int c = 0; c < 26; c++) {
                mx = max(mx, tree[1].best[c]);
            }

            ans.push_back(mx);
        }

        return ans;
    }
};