// Arrays_Contest_Interview_CheatSheet.cpp
// C++ Revision Cheat Sheet for Striver Arrays + LeetCode
// Focus: Contest + Interview

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
1. KADANE'S ALGORITHM
KEYWORDS:
"maximum subarray sum", "contiguous"

THINK:
Negative prefix hurting answer? Reset it.

TC: O(N), SC: O(1)
PITFALL:
Initialize ans = nums[0] for all negative array.
=========================================================
*/
int kadane(vector<int>& nums){
    int sum = 0, maxi = nums[0];

    for(int x : nums){
        sum += x;
        maxi = max(maxi, sum);

        if(sum < 0) sum = 0;
    }
    return maxi;
}

/*
=========================================================
2. PREFIX SUM + HASHMAP
KEYWORDS:
"subarray sum = k"
"count subarrays"
"longest subarray"

THINK:
prefixSum - k
=========================================================
*/

// Count subarrays with sum K
// prefix = current sum till now
// prefix - old_prefix = k
// old_prefix = prefix - k
int subarraySum(vector<int>& nums, int k){
    unordered_map<int,int> mp;

    int prefix = 0, count = 0;

    for(int x : nums){
        prefix += x;
        if (prefix == k)
            count++;

        if(mp.find(prefix-k) != mp.end())
            count += mp[prefix-k];

        mp[prefix]++;
    }
    return count;
}

// Longest subarray sum = k
int longestSubarray(vector<int>& nums, int k){
    unordered_map<int,int> mp;
    int sum = 0, maxi = 0;

    for(int i=0;i<nums.size();i++){
        sum += nums[i];

        if(sum == k) maxi = i+1;

        if(mp.find(sum-k)!=mp.end())
            maxi = max(maxi, i-mp[sum-k]);

        if(mp.find(sum)==mp.end())
            mp[sum] = i;
    }
    return maxi;
}

/*
=========================================================
3. DUTCH NATIONAL FLAG
KEYWORDS:
sort 0,1,2
low mid high
=========================================================
*/
void sortColors(vector<int>& nums){
    int low=0, mid=0, high=nums.size()-1;

    while(mid<=high){
        if(nums[mid]==0)
            swap(nums[low++], nums[mid++]);
        else if(nums[mid]==1)
            mid++;
        else
            swap(nums[mid], nums[high--]);
    }
}

/*
=========================================================
4. BOYER MOORE VOTING
KEYWORDS:
majority element > n/2
majority element > n/3
=========================================================
also refer question number hard Q2 : "Majority Element II" for n/3 case
*/
int majorityElement(vector<int>& nums) {
    int vote = 0, ele = 0;
    for(int x : nums){
        if(vote == 0){
            ele = x;
            vote = 1;
        }
        else if(x == ele)
            vote++;
        else
            vote--;
    }
    int cnt = 0;
    for(int x : nums){
        if(x == ele)
            cnt++;
    }
    return (cnt > nums.size()/2) ? ele : -1;
}
/*
=========================================================
5. NEXT PERMUTATION
KEYWORDS:
next lexicographical permutation
=========================================================
STEPS:
1. Find breakpoint
2. Find greater element from back
3. Swap
4. Reverse suffix
*/
void nextPermutation(vector<int>& nums){
    int idx=-1, n=nums.size();

    for(int i=n-2;i>=0;i--){
        if(nums[i] < nums[i+1]){
            idx=i;
            break;
        }
    }

    if(idx==-1){
        reverse(nums.begin(), nums.end());
        return;
    }

    for(int i=n-1;i>idx;i--){
        if(nums[i] > nums[idx]){
            swap(nums[i], nums[idx]);
            break;
        }
    }

    reverse(nums.begin()+idx+1, nums.end());
}

/*
=========================================================
6. LONGEST CONSECUTIVE SEQUENCE
KEYWORDS:
consecutive elements
O(N) expected
=========================================================
*/
int longestConsecutive(vector<int>& nums){
    unordered_set<int> st(nums.begin(), nums.end());
    int longest=0;

    for(int x : st){
        if(st.find(x-1)==st.end()){
            int cnt=1, cur=x;

            while(st.find(cur+1)!=st.end()){
                cur++;
                cnt++;
            }

            longest=max(longest,cnt);
        }
    }
    return longest;
}

/*
=========================================================
7. 3 SUM
KEYWORDS:
triplets = target
no duplicates

SORT + TWO POINTER
TC: O(N^2)
also check 4sum, hard Q4
=========================================================
*/
vector<vector<int>> threeSum(vector<int>& nums){
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    for(int i=0;i<nums.size();i++){
        if(i>0 && nums[i]==nums[i-1]) continue;

        int j=i+1, k=nums.size()-1;

        while(j<k){
            long long sum=nums[i]+nums[j]+nums[k];

            if(sum<0) j++;
            else if(sum>0) k--;
            else{
                ans.push_back({nums[i], nums[j], nums[k]});
                j++; k--;

                while(j<k && nums[j]==nums[j-1]) j++;
                while(j<k && nums[k]==nums[k+1]) k--;
            }
        }
    }
    return ans;
}

/*
=========================================================
8. MERGE INTERVALS
KEYWORDS:
overlapping intervals
=========================================================
*/
vector<vector<int>> merge(vector<vector<int>>& intervals){
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    for(auto &it : intervals){
        if(ans.empty() || it[0] > ans.back()[1])
            ans.push_back(it);
        else
            ans.back()[1] = max(ans.back()[1], it[1]);
    }
    return ans;
}

/*
=========================================================
9. XOR PATTERN
KEYWORDS:
xor = k
missing number
single number

IMPORTANT:
x ^ x = 0
x ^ 0 = x
=========================================================
*/

/*
Contest Heuristics:
1. "Subarray sum k" -> Prefix Sum + HashMap
2. "Longest/Count subarray" -> Prefix + Map
3. "Pair/triplet sorted" -> Two pointer
4. "Consecutive sequence" -> HashSet
5. "Maximum contiguous" -> Kadane
6. "0/1/2" -> DNF
7. "Majority > n/2" -> Boyer Moore
8. "Intervals overlap" -> Sort + Merge
9. "No extra space" -> Swap/Reverse
*/
int main(){
    cout << "Arrays Cheat Sheet Loaded\n";
}
