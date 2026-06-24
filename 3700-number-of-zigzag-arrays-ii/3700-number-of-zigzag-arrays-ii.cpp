class Solution {
    static constexpr long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix &A, const Matrix &B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!A[i][k]) continue;

                long long aik = A[i][k];

                for (int j = 0; j < n; j++) {
                    if (!B[k][j]) continue;

                    C[i][j] =
                        (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix res(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++)
            res[i][i] = 1;

        while (exp) {
            if (exp & 1)
                res = multiply(res, base);

            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

public:
    int zigZagArrays(long long n, int l, int r) {

        int m = r - l + 1;

        if (n == 1) return m;

        int S = 2 * m;

        Matrix T(S, vector<long long>(S, 0));

        auto UP = [&](int v) { return v; };
        auto DOWN = [&](int v) { return m + v; };

        for (int u = 0; u < m; u++) {
            for (int v = u + 1; v < m; v++) {

                T[UP(v)][DOWN(u)] = 1;
                T[DOWN(u)][UP(v)] = 1;
            }
        }

        vector<long long> dp2(S, 0);

        for (int v = 0; v < m; v++) {
            dp2[UP(v)] = v;
            dp2[DOWN(v)] = m - 1 - v;
        }

        if (n == 2) {
            long long ans = 0;
            for (auto x : dp2)
                ans = (ans + x) % MOD;
            return ans;
        }

        Matrix P = power(T, n - 2);

        vector<long long> dp(S, 0);

        for (int i = 0; i < S; i++) {
            long long val = 0;

            for (int j = 0; j < S; j++) {
                val = (val + P[i][j] * dp2[j]) % MOD;
            }

            dp[i] = val;
        }

        long long ans = 0;
        for (auto x : dp)
            ans = (ans + x) % MOD;

        return (int)ans;
    }
};