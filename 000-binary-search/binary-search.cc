#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch(const vector<int>& sortedArr, int x) {
  int low = 0, high = sortedArr.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    int hit = sortedArr[mid];
    if (hit == x) {
      return mid;
    } else if (hit > x) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

// Return the index of the first element that is not less than value,
// or -1 if no such element is found.
int lowerBound(const vector<int>& sortedArr, int x) {
  int low = 0, high = sortedArr.size() - 1, sofar = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    int hit = sortedArr[mid];
    if (hit >= x) {
      sofar = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return sofar;
}

// Return the index of the first element that is larger than value, or
// -1 if no such element is found.
int upperBound(const vector<int>& sortedArr, int x) {
  int low = 0, high = sortedArr.size() - 1, sofar = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    int hit = sortedArr[mid];
    if (hit > x) {
      sofar = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return sofar;
}

void test(const vector<int>& sortedArr, int x) {
  cout << "input: [";
  for (auto x: sortedArr) cout << " " << x;
  cout << " ]\n";
  cout << "x: " << x << "\n";
  cout << "binarySearch(input, x): " << binarySearch(sortedArr, x) << "\n";
  cout << "lowerBound(input, x): " << lowerBound(sortedArr, x) << "\n";
  cout << "upperBound(input, x): " << upperBound(sortedArr, x) << "\n\n";
}

int main(int argc, char* argv[]) {
  test({  }, 1);
  test({ 1 }, 1);
  test({ 1 }, 0);
  test({ 1 }, 2);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, -10);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, -1);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 3);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 4);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 6);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 10);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 23);
  test({ -1, 3, 4, 4, 4, 6, 6, 10, 23 }, 29);
  return 0;
}
