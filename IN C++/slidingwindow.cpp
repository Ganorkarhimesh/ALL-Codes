#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int maxSum(vector<int>& arr, int k) {
    int n = arr.size();
    int max_sum = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        int current_sum = 0;
        for (int j = 0; j < k; j++)
        current_sum += arr[i + j];
        
        max_sum = max(current_sum, max_sum);
    }
    return max_sum;
}

int main() {
    vector<int> arr = {5, 2, -1, 0, 3};
    int k = 3;

    cout << maxSum(arr, k) << endl;
    return 0;
}