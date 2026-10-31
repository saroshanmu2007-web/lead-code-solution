class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> R(m, vector<int>(n, -1));
        vector<vector<int>> D(m, vector<int>(n, -1));

        // Precompute mirror destinations
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (grid[i][j] == 0)
                    continue;

                // Enter mirror while moving Right
                if (i + 1 < m) {
                    if (grid[i + 1][j] == 0)
                        R[i][j] = (i + 1) * n + j;
                    else
                        R[i][j] = D[i + 1][j];
                }

                // Enter mirror while moving Down
                if (j + 1 < n) {
                    if (grid[i][j + 1] == 0)
                        D[i][j] = i * n + j + 1;
                    else
                        D[i][j] = R[i][j + 1];
                }
            }
        }

        vector<vector<long long>> dp(m, vector<long long>(n, 0));

        dp[0][0] = 1;

        // Dynamic Programming
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0)
                    continue;

                // Move Right
                if (j + 1 < n) {

                    int x = i;
                    int y = j + 1;

                    if (grid[x][y] == 1) {
                        int pos = R[x][y];

                        if (pos != -1) {
                            x = pos / n;
                            y = pos % n;

                            dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                        }
                    }
                    else {
                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }

                // Move Down
                if (i + 1 < m) {

                    int x = i + 1;
                    int y = j;

                    if (grid[x][y] == 1) {
                        int pos = D[x][y];

                        if (pos != -1) {
                            x = pos / n;
                            y = pos % n;

                            dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                        }
                    }
                    else {
                        dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};