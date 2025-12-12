#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        long long ans = INT_MAX, s = 0, sum = 0;

        if (k == cardPoints.size()) {
            long long sum = 0;
            for (int num : cardPoints) sum += num;
            return sum;
        }

        
        for (int i = 0; i < cardPoints.size(); i++) {
            // 1. 进入窗口
            s += cardPoints[i];
            sum += cardPoints[i];

            
            int left = k + i + 1 - cardPoints.size();

            if (left < 0) { // 窗口大小不足 k
                continue;
            }

            ans = min(ans, s);

            int out = cardPoints[left];
            s -= out;
        }
        ans = sum - ans;
        return ans;
    }
};

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int m = n - k;
        //reduce()计算范围内的总和
        int s = reduce(cardPoints.begin(), cardPoints.begin() + m);
        int min_s = s;
        for (int i = m; i < n; i++) {
            s += cardPoints[i] - cardPoints[i - m];
            min_s = min(min_s, s);
        }
        return reduce(cardPoints.begin(), cardPoints.end()) - min_s;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/solutions/2551432/liang-chong-fang-fa-ni-xiang-si-wei-zhen-e3gb/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

//我的solution是参考灵神的思路构建的,灵神这个要比我的简单不少,考点就是滑动窗口
//时间复杂度：O(n)，其中 n 为 cardPoints 的长度。
//空间复杂度：O(1)。

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int s = reduce(cardPoints.begin(), cardPoints.begin() + k);
        int ans = s;
        for (int i = 1; i <= k; i++) {
            s += cardPoints[cardPoints.size() - i] - cardPoints[k - i];
            ans = max(ans, s);
        }
        return ans;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/solutions/2551432/liang-chong-fang-fa-ni-xiang-si-wei-zhen-e3gb/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

//正向思维

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
        long long actual = sol.maxScore(nums, k);

        // 输出结果
        printResult(i + 1, expected, actual); // i+1是测试用例编号（从1开始）

    }

    return 0;
}