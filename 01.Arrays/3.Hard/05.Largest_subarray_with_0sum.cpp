/*
QUESTION:
Given an array with both positive and negative integers, 
we need to compute the length of the largest subarray with a sum of 0.

Example:
Input:
N = 8
A[] = {15, -2, 2, -8, 1, 7, 10, 23}
Output: 5
Explanation: The largest subarray with a sum of 0 will be -2, 2, -8, 1, 7.

APPROACH:
To find the length of the largest subarray with a sum of 0, we can use a technique called prefix sum.
1. Create a prefix sum array of the same size as the input array.
2. Initialize a map to store the prefix sum and its corresponding index. 
   Initialize it with an entry for prefix sum 0 and index -1.
3. Iterate through the input array and calculate the prefix sum by adding each element.
4. For each prefix sum encountered, check if it exists in the map.
   If it does, update the answer by taking the maximum of the current answer and the difference between the current index and the 
   index stored in the map for that prefix sum.
5. If the prefix sum is not found in the map, add it to the map with its corresponding index.
6. Finally, return the answer as the length of the largest subarray with a sum of 0.

CODE:
*/

int maxLen(vector<int>& arr) {
        unordered_map<int, int> sumMap;  // Map to store first occurrence of cumulative sum
        int maxLength = 0;
        int sum = 0;

        // Traverse the array
        for (int i = 0; i < arr.size(); ++i) {
            sum += arr[i];  // Compute the running sum

            // If sum is zero, the subarray from index 0 to i has sum 0
            if (sum == 0) {
                maxLength = i + 1;
            }
            // If the sum has been seen before, update maxLength
            else if (sumMap.find(sum) != sumMap.end()) {
                maxLength = max(maxLength, i - sumMap[sum]);
            } else {
                // Store the first occurrence of the cumulative sum
                sumMap[sum] = i;
            }
        }

        return maxLength;  // Return the maximum length of subarray with sum zero
    }

/*
TIME COMPLEXITY: O(n), where n is the size of the input array A.
SPACE COMPLEXITY: O(n), as we are using a map to store the prefix sums and their corresponding indices.
*/
