#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
BINARY SEARCH MASTER FILE — PATTERN RECOGNITION + ALL CORE PROBLEMS
================================================================================

This file is written to help you recognize WHEN binary search applies,
WHICH template to use, and HOW to code the common problems.

--------------------------------------------------------------------------------
KEYWORDS / CLUES THAT SIGNAL BINARY SEARCH
--------------------------------------------------------------------------------
- sorted array
- rotated sorted array
- lower bound / upper bound
- first occurrence / last occurrence
- first true / last true
- minimum feasible / maximum feasible
- answer in a range
- capacity, days, pages, speed, load, time
- monotonic predicate
- one side is always sorted
- decide which half can be discarded

Binary search is used because it cuts the search space in half every step,
giving O(log N) time whenever the problem has a monotonic structure.

--------------------------------------------------------------------------------
WHICH LOOP CONDITION SHOULD YOU USE?
--------------------------------------------------------------------------------
1) while(low <= high)
   - exact search
   - when you want to return an index or -1
   - classic search in sorted array
   - rotated search often uses this style too

2) while(low < high)
   - boundary / answer search
   - lower_bound / upper_bound style
   - first valid / minimum feasible answer
   - the final answer is left in low (or high)

Why low < high?
- because when low == high, only one candidate remains
- you stop and return that candidate
- this keeps the invariant clean for first-true / minimum-answer problems

Why low <= high?
- because you are checking each candidate explicitly
- once low crosses high, the search ends

--------------------------------------------------------------------------------
MID FORMULA
--------------------------------------------------------------------------------
Use:
    mid = low + (high - low) / 2

This prevents overflow.

================================================================================
SECTION 1: 1D ARRAY PROBLEMS
================================================================================
*/

// 1) Find x in sorted array (exact search)
int searchInSortedArray(const vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 2) Lower bound: first index where nums[i] >= target
int lowerBoundBS(const vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= target) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 3) Upper bound: first index where nums[i] > target
int upperBoundBS(const vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > target) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 4) First and last position of element
int firstOccurrence(const vector<int>& nums, int target) {
    int idx = lowerBoundBS(nums, target);
    if (idx < (int)nums.size() && nums[idx] == target) return idx;
    return -1;
}

int lastOccurrence(const vector<int>& nums, int target) {
    int idx = upperBoundBS(nums, target) - 1;
    if (idx >= 0 && idx < (int)nums.size() && nums[idx] == target) return idx;
    return -1;
}

// 5) Number of occurrences
int countOccurrences(const vector<int>& nums, int target) {
    int first = firstOccurrence(nums, target);
    if (first == -1) return 0;
    int last = lastOccurrence(nums, target);
    return last - first + 1;
}

// 6) Peak element (find any peak)
int findPeakElement(const vector<int>& nums) {
    int n = (int)nums.size();
    if (n == 1) return 0;
    int low = 0, high = n - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[mid + 1]) low = mid + 1;
        else high = mid;
    }
    return low;
}

// 7) Search in rotated sorted array (distinct elements)
int searchInRotatedSortedArray(const vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;

        if (nums[low] <= nums[mid]) { // left half sorted
            if (nums[low] <= target && target < nums[mid]) high = mid - 1;
            else low = mid + 1;
        } else { // right half sorted
            if (nums[mid] < target && target <= nums[high]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}

// 8) Search in rotated sorted array with duplicates
bool searchInRotatedSortedArrayWithDuplicates(const vector<int>& nums, int target) {
    int low = 0, high = (int)nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return true;

        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
            low++;
            high--;
        } else if (nums[low] <= nums[mid]) { // left sorted
            if (nums[low] <= target && target < nums[mid]) high = mid - 1;
            else low = mid + 1;
        } else { // right sorted
            if (nums[mid] < target && target <= nums[high]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return false;
}

// 9) Find minimum element in rotated sorted array (with duplicates handled)
int findMinInRotatedSortedArray(const vector<int>& nums) {
    int low = 0, high = (int)nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[high]) high = mid;
        else if (nums[mid] > nums[high]) low = mid + 1;
        else high--; // duplicates case
    }
    return nums[low];
}

// 10) Find single element in sorted array (every other element appears twice)
int singleNonDuplicate(const vector<int>& nums) {
    int low = 0, high = (int)nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (mid % 2 == 1) mid--; // ensure mid is the first index of a pair
        if (nums[mid] == nums[mid + 1]) low = mid + 2;
        else high = mid;
    }
    return nums[low];
}

// 11) How many times array is rotated = index of minimum element
int howManyTimesArrayIsRotated(const vector<int>& nums) {
    int low = 0, high = (int)nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[high]) high = mid;
        else if (nums[mid] > nums[high]) low = mid + 1;
        else high--;
    }
    return low; // rotation count
}

/*
================================================================================
SECTION 2: 2D ARRAY PROBLEMS
================================================================================
*/

// 1) Row with maximum number of 1's
int rowWithMaximumOnes(const vector<vector<int>>& mat) {
    int n = mat.size();
    if (n == 0) return -1;
    int m = mat[0].size();
    int bestRow = -1;
    int maxOnes = 0;

    for (int i = 0; i < n; i++) {
        // if each row is sorted, lower_bound on 1 gives first 1
        int firstOne = lowerBoundBS(mat[i], 1);
        int ones = m - firstOne;
        if (ones > maxOnes) {
            maxOnes = ones;
            bestRow = i;
        }
    }
    return bestRow;
}

// 2) Search in sorted matrix (matrix treated as a flattened sorted array)
bool searchInSortedMatrix(const vector<vector<int>>& mat, int target) {
    int n = mat.size();
    if (n == 0) return false;
    int m = mat[0].size();
    int low = 0, high = n * m - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int r = mid / m;
        int c = mid % m;
        if (mat[r][c] == target) return true;
        if (mat[r][c] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

// 3) Search in row-wise sorted matrix
bool searchInRowWiseSortedMatrix(const vector<vector<int>>& mat, int target) {
    int n = mat.size();
    if (n == 0) return false;
    int m = mat[0].size();

    for (int i = 0; i < n; i++) {
        if (mat[i][0] <= target && target <= mat[i][m - 1]) {
            int low = 0, high = m - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (mat[i][mid] == target) return true;
                if (mat[i][mid] < target) low = mid + 1;
                else high = mid - 1;
            }
        }
    }
    return false;
}

// 4) Peak element in matrix
// A peak is an element greater than or equal to its neighbors (up/down/left/right)
// This implementation finds a peak by binary searching columns.
vector<int> findPeakElementInMatrix(const vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    int low = 0, high = m - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        int maxRow = 0;
        for (int i = 1; i < n; i++) {
            if (mat[i][mid] > mat[maxRow][mid]) maxRow = i;
        }

        int left = (mid - 1 >= 0) ? mat[maxRow][mid - 1] : -1;
        int right = (mid + 1 < m) ? mat[maxRow][mid + 1] : -1;

        if (mat[maxRow][mid] >= left && mat[maxRow][mid] >= right) {
            return {maxRow, mid};
        } else if (right > mat[maxRow][mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return {-1, -1};
}

// 5) Matrix median
// Assumes each row is sorted.
// The median is the (n*m + 1)/2-th smallest number.
int matrixMedian(const vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    int low = INT_MAX, high = INT_MIN;
    for (int i = 0; i < n; i++) {
        low = min(low, mat[i][0]);
        high = max(high, mat[i][m - 1]);
    }

    int need = (n * m + 1) / 2;
    while (low < high) {
        int mid = low + (high - low) / 2;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
        }
        if (cnt < need) low = mid + 1;
        else high = mid;
    }
    return low;
}

/*
================================================================================
SECTION 3: SEARCH SPACE PROBLEMS
================================================================================

This is the most important binary search category in interviews.
You are not searching an element.
You are searching the answer.

The key idea is to define a monotonic predicate check(x).

Example:
- if x works, then all larger x also work
- or if x fails, then all smaller x also fail

That allows binary search on the answer.
================================================================================
*/

// 1) Square root of number (floor sqrt)
int squareRootFloor(int n) {
    int low = 1, high = n, ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long sq = mid * mid;
        if (sq <= n) {
            ans = (int)mid;
            low = (int)mid + 1;
        } else {
            high = (int)mid - 1;
        }
    }
    return ans;
}

// 2) Nth root of integer (exact root if exists, else -1)
long long powerLimit(long long x, int n, long long limit) {
    long long val = 1;
    for (int i = 0; i < n; i++) {
        if (val > limit / x) return limit + 1; // overflow-safe pruning
        val *= x;
    }
    return val;
}

int nthRoot(int n, int m) {
    int low = 1, high = m;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long val = 1;
        bool overflow = false;
        for (int i = 0; i < n; i++) {
            if (val > m / mid) {
                overflow = true;
                break;
            }
            val *= mid;
        }
        if (!overflow && val == m) return mid;
        if (!overflow && val < m) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 3) Koko Eating Bananas
bool canEatAllBananas(const vector<int>& piles, int h, int speed) {
    long long hours = 0;
    for (int p : piles) {
        hours += (p + speed - 1) / speed;
    }
    return hours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1, high = *max_element(piles.begin(), piles.end());
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canEatAllBananas(piles, h, mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 4) Minimum days to make bouquets
bool canMakeBouquets(const vector<int>& bloomDay, int m, int k, int day) {
    int bouquets = 0, flowers = 0;
    for (int d : bloomDay) {
        if (d <= day) {
            flowers++;
            if (flowers == k) {
                bouquets++;
                flowers = 0;
            }
        } else {
            flowers = 0;
        }
    }
    return bouquets >= m;
}

int minDaysToMakeBouquets(vector<int>& bloomDay, int m, int k) {
    long long need = 1LL * m * k;
    if (need > (long long)bloomDay.size()) return -1;

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canMakeBouquets(bloomDay, m, k, mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 5) Find smallest divisor such that sum of ceil(nums[i] / divisor) <= threshold
bool canDivideWithThreshold(const vector<int>& nums, int threshold, int divisor) {
    long long sum = 0;
    for (int x : nums) {
        sum += (x + divisor - 1) / divisor;
    }
    return sum <= threshold;
}

int smallestDivisor(vector<int>& nums, int threshold) {
    int low = 1, high = *max_element(nums.begin(), nums.end());
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canDivideWithThreshold(nums, threshold, mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 6) Capacity to ship packages within D days
bool canShipWithinDays(const vector<int>& weights, int days, int capacity) {
    int usedDays = 1;
    long long load = 0;
    for (int w : weights) {
        if (load + w > capacity) {
            usedDays++;
            load = w;
        } else {
            load += w;
        }
    }
    return usedDays <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canShipWithinDays(weights, days, mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 7) Magnetic force between two balls (maximize minimum distance)
bool canPlaceBalls(const vector<int>& position, int m, int dist) {
    int count = 1;
    int last = position[0];
    for (int i = 1; i < (int)position.size(); i++) {
        if (position[i] - last >= dist) {
            count++;
            last = position[i];
            if (count >= m) return true;
        }
    }
    return false;
}

int maxDistance(vector<int>& position, int m) {
    sort(position.begin(), position.end());
    int low = 1, high = position.back() - position.front();
    int ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canPlaceBalls(position, m, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// 8) Book allocation (minimize maximum pages)
bool canAllocateBooks(const vector<int>& books, int students, int limit) {
    int required = 1;
    long long pages = 0;
    for (int b : books) {
        if (b > limit) return false;
        if (pages + b > limit) {
            required++;
            pages = b;
        } else {
            pages += b;
        }
    }
    return required <= students;
}

int bookAllocation(vector<int>& books, int students) {
    if (students > (int)books.size()) return -1;
    int low = *max_element(books.begin(), books.end());
    int high = accumulate(books.begin(), books.end(), 0);
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canAllocateBooks(books, students, mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 9) Split array largest sum
bool canSplitArray(const vector<int>& nums, int k, long long maxSum) {
    int parts = 1;
    long long sum = 0;
    for (int x : nums) {
        if (sum + x > maxSum) {
            parts++;
            sum = x;
        } else {
            sum += x;
        }
    }
    return parts <= k;
}

int splitArrayLargestSum(vector<int>& nums, int k) {
    long long low = *max_element(nums.begin(), nums.end());
    long long high = accumulate(nums.begin(), nums.end(), 0LL);
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (canSplitArray(nums, k, mid)) high = mid;
        else low = mid + 1;
    }
    return (int)low;
}

// 10) Kth missing number
int findKthMissingNumber(const vector<int>& arr, int k) {
    // missing count till index i = arr[i] - (i+1)
    int n = arr.size();
    if (k > arr[n - 1] - n) return arr[n - 1] + (k - (arr[n - 1] - n));

    int low = 0, high = n - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);
        if (missing < k) low = mid + 1;
        else high = mid;
    }
    return low + k;
}

// 11) Gas station (minimize maximum distance between adjacent gas stations)
// Given existing stations and k extra stations, minimize max gap after adding stations.
bool canAchieveGasStationGap(const vector<int>& stations, int k, double dist) {
    int needed = 0;
    for (int i = 1; i < (int)stations.size(); i++) {
        double gap = stations[i] - stations[i - 1];
        needed += (int)ceil(gap / dist) - 1;
        if (needed > k) return false;
    }
    return needed <= k;
}

double gasStationMinimizeMaxDistance(vector<int>& stations, int k) {
    sort(stations.begin(), stations.end());
    double low = 0.0, high = stations.back() - stations.front();
    for (int iter = 0; iter < 100; iter++) { // precision based search
        double mid = (low + high) / 2.0;
        if (canAchieveGasStationGap(stations, k, mid)) high = mid;
        else low = mid;
    }
    return high;
}

// 12) Median of two sorted arrays
// Standard binary partition approach.
double medianOfTwoSortedArrays(vector<int>& a, vector<int>& b) {
    if (a.size() > b.size()) return medianOfTwoSortedArrays(b, a);

    int n1 = a.size(), n2 = b.size();
    int low = 0, high = n1;

    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int l1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
        int r1 = (cut1 == n1) ? INT_MAX : a[cut1];
        int r2 = (cut2 == n2) ? INT_MAX : b[cut2];

        if (l1 <= r2 && l2 <= r1) {
            if ((n1 + n2) % 2 == 0) return (max(l1, l2) + min(r1, r2)) / 2.0;
            return max(l1, l2);
        } else if (l1 > r2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }
    return 0.0;
}

// 13) Kth element of two sorted arrays
int kthElementOfTwoSortedArrays(vector<int>& a, vector<int>& b, int k) {
    if (a.size() > b.size()) return kthElementOfTwoSortedArrays(b, a, k);

    int n1 = a.size(), n2 = b.size();
    int low = max(0, k - n2), high = min(k, n1);

    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = k - cut1;

        int l1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
        int r1 = (cut1 == n1) ? INT_MAX : a[cut1];
        int r2 = (cut2 == n2) ? INT_MAX : b[cut2];

        if (l1 <= r2 && l2 <= r1) return max(l1, l2);
        else if (l1 > r2) high = cut1 - 1;
        else low = cut1 + 1;
    }
    return -1;
}

/*
================================================================================
PATTERN RECOGNITION SUMMARY
================================================================================

A) Exact search in sorted / rotated array
   -> while(low <= high)
   -> return index or -1

B) First / last / lower_bound / upper_bound / minimum feasible answer
   -> while(low < high)
   -> use boundary updates:
      - first valid: high = mid
      - first invalid after valid: low = mid + 1

C) Search on answer space
   -> define can(mid)
   -> binary search on mid
   -> if can(mid) is true, shrink left; otherwise move right

D) Matrix problems
   -> either flatten the matrix
   -> or binary search rows / columns
   -> or use monotonic counting in rows

E) Common traps
   -> duplicates in rotated array need special handling
   -> use long long where sums / products can overflow
   -> store answer only when doing maximum feasible / minimum feasible search

================================================================================
SAMPLE MAIN FOR QUICK TESTING
================================================================================
*/
int main() {
    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    cout << "Exact search 3: " << searchInSortedArray(arr, 3) << '
';
    cout << "Lower bound 2: " << lowerBoundBS(arr, 2) << '
';
    cout << "Upper bound 2: " << upperBoundBS(arr, 2) << '
';
    cout << "First occurrence 2: " << firstOccurrence(arr, 2) << '
';
    cout << "Last occurrence 2: " << lastOccurrence(arr, 2) << '
';
    cout << "Count 2: " << countOccurrences(arr, 2) << '
';
    cout << "Peak index: " << findPeakElement(vector<int>{1, 3, 20, 4, 1, 0}) << '
';
    cout << "Min in rotated: " << findMinInRotatedSortedArray(vector<int>{4, 5, 6, 7, 0, 1, 2}) << '
';
    cout << "Rotation count: " << howManyTimesArrayIsRotated(vector<int>{4, 5, 6, 7, 0, 1, 2}) << '
';

    vector<vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    cout << "Search in sorted matrix (6): " << searchInSortedMatrix(mat, 6) << '
';
    cout << "Matrix median: " << matrixMedian(mat) << '
';

    vector<int> piles = {3, 6, 7, 11};
    cout << "Koko speed: " << minEatingSpeed(piles, 8) << '
';

    return 0;
}
