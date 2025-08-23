#include <stdio.h>

typedef struct {
    int start;
    int finish;
    char name[3];
    int profit;
} Activity;

void activitySelection(Activity activities[], int n) {
    int i, j;
    int totalProfit = 0;
    printf("Selected Activities:\n");

    for (int i = 0; i < n; i++)
    {
        if (i == 0 || activities[i].start >= activities[j].finish)
        {
            printf("%s", activities[i].name);
            totalProfit += activities[i].profit;
            j = i;
        }
        
    }
    printf("\n Total Profit: %d\n", totalProfit);
}
int main() {
    Activity activities[] = {
        {1, 4, "A1", 10},   
        {3, 5, "A2", 15},
        {0, 6, "A3", 14},
        {5, 7, "A4", 12},
        {3, 9, "A5", 20},
        {5, 9, "A6", 30},
        {6, 10, "A7", 32},
        {8, 11, "A8", 28},
        {8, 12, "A9", 30},
        {2, 14, "A10", 40},
        {12, 16, "A11", 45}
    };
    int n = sizeof(activities) / sizeof(activities[0]);
    activitySelection(activities, n);

    return 0;
}