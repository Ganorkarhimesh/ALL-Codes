#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateData(float arr[], int n, float min, float max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + ((float)rand() / RAND_MAX) * (max - min);
    }
}

void linearSearch(float arr[], int n, float *min, float *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void pairwiseSearch(float arr[], int n, float *min, float *max) {
    *min = arr[0];
    *max = arr[0];
    for (int i = 0; i < n; i++) {
        int isMin = 1, isMax = 1;
        for (int j = 0; j < n; j++) {
            if (arr[i] > arr[j]) isMin = 0;
            if (arr[i] < arr[j]) isMax = 0;
        }
        if (isMin) *min = arr[i];
        if (isMax) *max = arr[i];
    }
}

int linearFind(float arr[], int n, float val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] >= val) return i;
    }
    return -1;
}

int binaryFind(float arr[], int n, float val) {
    int left = 0, right = n - 1, res = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= val) {
            res = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return res;
}

void sort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

double measureTime(void (*func)(float[], int, float*, float*), float arr[], int n) {
    float min, max;
    clock_t start = clock();
    func(arr, n, &min, &max);
    return ((double)(clock() - start)) / CLOCKS_PER_SEC;
}

double measureFindTime(int (*func)(float[], int, float), float arr[], int n, float val) {
    clock_t start = clock();
    func(arr, n, val);
    return ((double)(clock() - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(0));
    int sizes[] = {100, 10000, 1000000};
    
    printf("Task-A (Linear Search)\n");
    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        float temp[n], pressure[n];
        generateData(temp, n, -20, 50);
        generateData(pressure, n, 950, 1050);
        printf("n=%d: temp=%.6f pressure=%.6f\n", n, 
            measureTime(linearSearch, temp, n),
            measureTime(linearSearch, pressure, n));
    }

    printf("\nTask-B (Pairwise Search)\n");
    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        float temp[n], pressure[n];
        generateData(temp, n, -20, 50);
        generateData(pressure, n, 950, 1050);
        printf("n=%d: temp=%.6f pressure=%.6f\n", n, 
            measureTime(pairwiseSearch, temp, n),
            measureTime(pairwiseSearch, pressure, n));
    }

    printf("\nTask-C (Threshold Search)\n");
    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        float temp[n];
        generateData(temp, n, 20, 50);
        sort(temp, n);
        printf("n=%d: linear=%.6f binary=%.6f\n", n,
            measureFindTime(linearFind, temp, n, 30),
            measureFindTime(binaryFind, temp, n, 30));
    }

    return 0;
}