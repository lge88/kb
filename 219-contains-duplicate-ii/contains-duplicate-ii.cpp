class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    // num => largest index in nums where its value is num
    unordered_map<int, int> seen;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int num = nums[i];
      if (seen.find(num) == seen.end()) {
        seen[num] = i;
      } else {
        if (i - seen[num] <= k) return true;
        seen[num] = i;
      }
    }
    return false;
  }
};
