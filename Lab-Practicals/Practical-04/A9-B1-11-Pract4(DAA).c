#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int findMaxSubarray(int resources[], int left, int right , int constraint) {
    if(left > right) return 0;
    if(left == right) return resources[left] < constraint ? resources[left] : 0;

    int mid = (left + right) / 2;

    int leftMax = findMaxSubarray(resources, left, mid, constraint);
    int rightMax = findMaxSubarray(resources, mid + 1, right, constraint);

    int sum = 0, maxLeftSum = 0;
    for (int i = mid; i > left; i--)
    {
        sum += resources[i];
        if(sum < constraint) maxLeftSum = max(maxLeftSum, sum);
    }
    sum = 0;
    int maxRightSum = 0;
    for (int i = mid + 1; i < right; i++)
    {
        sum += resources[i];
        if(sum < constraint) maxRightSum = max(maxRightSum, sum);
    }
    int crossMax = maxLeftSum + maxRightSum;
    if(crossMax > constraint) crossMax = 0;

    return max(max(leftMax, rightMax), crossMax);
}

int main() {
    int resources[] = {2, 1, 3, 4};
    int constraint = 5;
    int n = sizeof(resources) / sizeof(resources[0]);

    int result = findMaxSubarray(resources, 0, n-1, constraint);
    printf("%d\n", result);
    return 0;
}