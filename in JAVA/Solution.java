class Solution {

    public long maxSubarraySum(int[] arr, int n) {
        long maxsoFar = arr[0];
        long currentMax = arr[0];

        for(int i=1; i<n;i++) {
            currentMax = Math.max(arr[i], currentMax + arr[i]);

            maxsoFar = Math.max(maxsoFar, currentMax);
        }
        return maxsoFar;
    }
}