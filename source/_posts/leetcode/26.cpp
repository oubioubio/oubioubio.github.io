#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i=1,j=0;
        while(i<nums.size()){
            if(nums[j]!=nums[i]){
                nums[++j]=nums[i];
            }
            i++;
        }
        return ++j;
    }
    //It does not matter what you leave beyond the returned k (hence they are underscores).
};

// test
int main() {
    Solution sol;
    vector<int> nums = {0,0,1,1,2,2,2,3 };
    sol.removeDuplicates(nums);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}