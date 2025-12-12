#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i=1,j=0;
        bool fir=true;
        while(i<nums.size()){
            if(nums[j]==nums[i]){
                if(fir){
                    nums[++j]=nums[i];    
                    fir=false;
                }
            }
            else{
                nums[++j]=nums[i];
                fir=true;
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
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 5, 5, };
    sol.removeDuplicates(nums);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}