#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i=0,j=0;
        while(i<nums.size()){
            if(nums[i]!=val){
                nums[j++]=nums[i];
            }
            i++;
        }
        return j;
    }
    //It does not matter what you leave beyond the returned k (hence they are underscores).
};

// test
int main() {
    Solution sol;
    vector<int> nums = {2, 0, 1, 5, 3, };
    sol.removeElement(nums,2);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}