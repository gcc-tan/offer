有数量不限的硬币，币值为25分、10分、5分和1分，请编写代码计算n分有几种表示法。
给定一个int n，请返回n分有几种表示法。保证n小于等于100000，为了防止溢出，请将答案Mod 1000000007。

测试样例：
	6
返回：
	2


coins[] = {25, 10, 5, 1}
很明显是一个动态规划问题，首先定义dp[i][j]表示coins数组的前0~i-1面值的硬币组成的j分钱的种类数。很明显，要求问题就是dp[4][n]。


 dp[i][j] = sum(dp[i-1][j - k*coins[i-1]])
 k = 0, 1, 2, ... , j / coins[i-1]

 上面这个方程就很好理解，因为它的思想是穷举coins[i-1]的面值硬币的个数k。



上面的方法效率低，下面的状态转移方程效率更高
dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]]，这个状态转移方程可能没有那么好理解。仔细想想就能发现是对的，dp[i][j]的状态可能是当前的硬币一个都不选，或者是选上一个（dp[i-1][j]），或者以上（dp[i][j-coins[i-1]]）






class Coins {
public:
    int countWays(int n) {
        // write code here
        int m = 4, i, j;
        int coins[] = {25, 10, 5, 1};
        vector<int> dp(n + 1, 0);

        dp[0] = 1;//dp[i][0]的边界条件
        for (i = 1; i <= 4; ++i)
        {
            for (j = coins[i-1]; j <= n; ++j)
            {
                dp[j] = (dp[j] + dp[j-coins[i-1]]) % 1000000007;
            }
        }

        return dp[n];
    }
};

