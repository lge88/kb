class Solution {
 public:
  int closedPairDistance(const vector<int>& nums, int left, int right) {
    vector<int> numsCopy(nums.begin() + left, nums.begin() + right + 1);
    sort(numsCopy.begin(), numsCopy.end());
    int minDist = -1;
    for (size_t i = 1; i < numsCopy.size(); ++i) {
      int dist = abs(numsCopy[i] - numsCopy[i - 1]);
      minDist = minDist < 0 ? dist : min(dist, minDist);
    }
    return minDist;
  }

  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    int n = nums.size();
    for (int i = 0; i + k <= n; ++i) {
      if (closedPairDistance(nums, i, i + k - 1) <= t) return true;
    }
    return false;
  }
};
