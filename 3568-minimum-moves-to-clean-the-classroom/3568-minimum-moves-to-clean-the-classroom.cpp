class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        // Har litter ko ek unique bit denge
        vector<vector<int>> id(m, vector<int>(n, -1));

        int sr = 0, sc = 0;
        int litterCount = 0;

        // Start position aur litter positions find karo
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount++;
                }
            }
        }

        // Agar koi litter hi nahi hai
        if (litterCount == 0)
            return 0;

        int totalMasks = 1 << litterCount;

        /*
            State:
            row
            col
            remaining energy
            mask = abhi kaun-kaun sa litter baaki hai
        */

        queue<array<int, 4>> q;

        // Initially saare litter baaki hain
        int fullMask = totalMasks - 1;

        q.push({sr, sc, energy, fullMask});

        // visited[row][col][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(totalMasks, false)
                )
            )
        );

        visited[sr][sc][energy][fullMask] = true;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                auto [r, c, currEnergy, mask] = q.front();
                q.pop();

                // Saara litter collect ho gaya
                if (mask == 0)
                    return moves;

                // Energy khatam hai to aage nahi ja sakte
                if (currEnergy == 0)
                    continue;

                for (int k = 0; k < 4; k++) {

                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    // Boundary check
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // Normal move -> energy - 1
                    int newEnergy = currEnergy - 1;

                    // Reset cell -> energy full
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    int newMask = mask;

                    // Agar litter mila
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];

                        // Is litter ko collected mark karo
                        newMask &= ~(1 << bit);
                    }

                    // Agar state pehle visit nahi hui
                    if (!visited[nr][nc][newEnergy][newMask]) {

                        visited[nr][nc][newEnergy][newMask] = true;

                        q.push({
                            nr,
                            nc,
                            newEnergy,
                            newMask
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};