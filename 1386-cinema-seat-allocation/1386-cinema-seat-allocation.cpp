class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        
        unordered_map<int, unordered_set<int>> reserved;

        // Store reserved seats row-wise
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Seat 1 and 10 are not useful for family placement
            if (col >= 2 && col <= 9) {
                reserved[row].insert(col);
            }
        }

        // Initially every row can have 2 families
        // if there are no relevant reservations.
        long long ans = 2LL * n;

        for (auto &[row, seats] : reserved) {

            bool left = true;    // 2,3,4,5
            bool middle = true;  // 4,5,6,7
            bool right = true;   // 6,7,8,9

            // Check LEFT block
            for (int s = 2; s <= 5; s++) {
                if (seats.count(s)) {
                    left = false;
                    break;
                }
            }

            // Check MIDDLE block
            for (int s = 4; s <= 7; s++) {
                if (seats.count(s)) {
                    middle = false;
                    break;
                }
            }

            // Check RIGHT block
            for (int s = 6; s <= 9; s++) {
                if (seats.count(s)) {
                    right = false;
                    break;
                }
            }

            // This row was initially counted as 2.
            // Recalculate its actual contribution.
            ans -= 2;

            if (left && right) {
                ans += 2;
            }
            else if (left || middle || right) {
                ans += 1;
            }
        }

        return ans;
    }
};