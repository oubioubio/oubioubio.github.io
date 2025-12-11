#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i=0,j=0,sum=0,min=INT_MAX;
        for(i=0;i<nums.size();i++){
            sum+=nums[i];
            while(sum>=target){
                if(min>i-j+1) min=i-j+1;
                sum-=nums[j++];
            }//2,3,1,2,4,3
        }
        return min == INT_MAX ? 0 : min;
    }
};

// test
int main() {
    Solution sol;
    vector<int> nums = {2,3,1,2,4,3};
    sol.minSubArrayLen(7,nums);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}