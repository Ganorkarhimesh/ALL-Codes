#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight ;
    int profit;
    double ratio;
} Box;

int compare(const void *a, const void *b) {
    Box *box1 = (Box *)a;
    Box *box2 = (Box *)b;
    return (box2->ratio > box1->ratio) - (box2->ratio < box1->ratio);
}

double fractionalKnapsack(Box boxes[], int n, int truckSize) {
    qsort(boxes, n, sizeof(Box), compare) ;
    double totalProfit = 0;
    for (int i = 0; i < n; i++)
    {
        if(truckSize == 0) break;
        if (boxes[i].weight <= truckSize)
        {
            totalProfit += boxes[i].profit;
            truckSize -= boxes[i].weight;
        } else {
            totalProfit += boxes[i].profit * ((double)truckSize / boxes[i].weight);
            truckSize = 0;
        }
        
    }
    return totalProfit;
}

int main() {
    int weights[50] = {7, 0, 30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0, 36, 3, 8, 15, 42, 9, 0, 42, 47, 52, 32, 26, 48, 55, 6, 29, 84, 2, 4, 18, 56, 7, 29, 93, 44, 71, 3, 86, 66, 31, 65, 0, 79, 20, 65, 52, 13};
    int profits[50] = {360, 83, 59, 130, 431, 67, 230, 52, 93, 125, 670, 892, 600, 38, 48, 147, 78, 256, 63, 17, 120, 164, 432, 35, 92, 110, 22, 42, 50, 323, 514, 28, 87, 73, 78, 15, 26, 78, 210, 36, 85, 189, 274, 43, 33, 10, 19, 389, 276, 312};
    int truckSize = 0;
    Box boxes[50]; 

    for (int i = 0; i < 50; i++)
    {
        boxes[i].weight = weights[i];
        boxes[i].profit = profits[i];
        boxes[i].ratio = (double)profits[i] / weights[i];
    }
    
    double maxProfit = fractionalKnapsack(boxes, 50, truckSize);
    printf("Maximum Profit : %.2f\n", maxProfit);
    return 0;
}
