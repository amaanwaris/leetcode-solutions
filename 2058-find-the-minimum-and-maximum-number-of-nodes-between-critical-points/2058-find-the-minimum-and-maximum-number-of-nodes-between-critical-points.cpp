class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;

        while (curr->next != nullptr) {
            int nextVal = curr->next->val;

            // Check if current node is a critical point
            if ((curr->val > prev->val && curr->val > nextVal) ||
                (curr->val < prev->val && curr->val < nextVal)) {

                if (first == -1) {
                    // First critical point
                    first = index;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, index - last);
                }

                last = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        // Less than 2 critical points
        if (first == last)
            return ans;

        int maxDist = last - first;

        return {minDist, maxDist};
    }
};