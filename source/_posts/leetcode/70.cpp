#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
    vector<int> memo;
    int dfs(int n){
        if(n<=1)    return 1;
        if(memo[n]) return memo[n];
        return memo[n]=dfs(n-1) + dfs(n-2);
    }
public:
    int climbStairs(int n) {
        memo.resize(n+1);
        return dfs(n);
    }
};

void printResult(int caseNum, long long expected, long long actual) {
    cout << "测试用例 " << caseNum << ": " 
         << (actual == expected ? "通过" : "失败") 
         << "（预期：" << expected << "，实际：" << actual << "）" << endl;
}


int main() {
    Solution sol;

    // 每个元素是一个测试用例：{nums, k, 预期结果}
    vector<tuple<vector<int>, int, long long>> testCases = {
        {{1,2,3,4,5,6,1}, 3, 12},    // 测试用例1

        {{9,7,7,9,7,7,9}, 7, 55},   // 测试用例2（假设预期也是55，实际可能不同）
        
        // 新增测试用例只需在这里加一行，格式同上
    };

    for (int i = 0; i < testCases.size(); ++i) {
        // 从测试用例中提取参数

        vector<int> nums = get<0>(testCases[i]); // 第一个元素是nums

        int k = get<1>(testCases[i]);            // 第二个元素是k

        long long expected = get<2>(testCases[i]); // 第三个元素是预期结果

        // 调用函数（如果函数名/参数变了，只改这一行）
        long long actual = sol.maximumSubarraySum(nums, k);

        // 输出结果
        printResult(i + 1, expected, actual); // i+1是测试用例编号（从1开始）

    }

    return 0;
}