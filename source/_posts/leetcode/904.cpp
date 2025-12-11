#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int i=0,j=0,max=0;
        for(i=0; i<fruits.size(); i++){
            
            if(max<j-i) max=j-i;
        }
    }
};

// test
int main() {
    Solution sol;
    vector<int> nums = {1,2,1};
    sol.totalFruit(nums);
    vector<int> res = nums;
    for (int num : res) cout << num << " ";
    return 0;
}