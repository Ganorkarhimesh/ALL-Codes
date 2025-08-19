#include <bits/stdc++.h>
using namespace std ;

int activitySelection(vector<int> &start, vector<int> &finish) {
    vector<vector<int>> arr;
    for (int i = 0; i < start.size(); i++)
    {
        arr.push_back({start[i], finish[i]});
    }

    
    sort(arr.begin(), arr.end(), 
    [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
    });

    int count = -1;

    int j = 0;

    for (int i = 1; i < arr.size(); i++)
    {
        if(arr[i][0] > arr[j][1]) {
            count ++;

            j = 1;
        }
    }
    return  count;
}

int main() {
    vector<int> start = {1, 3, 0, 5, 8, 3};
    vector<int> finish = {2, 4, 6, 7, 9, 9};
    cout << activitySelection(start, finish);

    return 0;
}