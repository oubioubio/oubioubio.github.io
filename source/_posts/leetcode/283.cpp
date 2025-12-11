#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i=0,j=0;
        while(i<nums.size()){
            if(nums[i]){
                nums[j++]=nums[i];// slow and fast pointer
            }
            i++;
        }
        while(j<i) nums[j++]=0;
    }
};

// test
int main() {
    Solution sol;
    vector<int> nums = {2, 0, 1, 5, 3, };
    sol.moveZeroes(nums);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}