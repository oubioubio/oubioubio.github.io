#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        long long ans = 0, left = 0;
        unordered_map<char, int> cnt;
        /*统计当前窗口内每个元素的出现次数 */
        
        for (int right = 0; right < s.size(); right++) {
            // 1. 进入窗口
            char c = s[right];
            cnt[c]++;
            while(cnt[c] > 1){
                cnt[s[left]] --;
                left++;
            }
            ans = max(ans,right-left+1);
        }

        return ans;
    
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
    vector<tuple<string , long long>> testCases = {
        {"abcabcbb", 3},    // 测试用例1

        {"bbbbb", 1},   // 测试用例2（假设预期也是55，实际可能不同）
        
        // 新增测试用例只需在这里加一行，格式同上
    };

    for (int i = 0; i < testCases.size(); ++i) {
        // 从测试用例中提取参数

        string s = get<0>(testCases[i]);
        // vector<int> nums = get<0>(testCases[i]); // 第一个元素是nums

        // int k = get<1>(testCases[i]);            // 第二个元素是k

        long long expected = get<1>(testCases[i]); // 第三个元素是预期结果

        // 调用函数（如果函数名/参数变了，只改这一行）
        long long actual = sol.lengthOfLongestSubstring(s);

        // 输出结果
        printResult(i + 1, expected, actual); // i+1是测试用例编号（从1开始）

    }

    return 0;
}