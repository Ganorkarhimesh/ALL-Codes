int maximumUnits(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize) {
    for (int i = 0; i < boxTypesSize - 1; i++) {
        for (int j = i + 1; j < boxTypesSize; j++) {
            if (boxTypes[j][1] > boxTypes[i][1]) {
                int temp_boxes = boxTypes[i][0];
                int temp_units = boxTypes[i][1];
                boxTypes[i][0] = boxTypes[j][0];
                boxTypes[i][1] = boxTypes[j][1];
                boxTypes[j][0] = temp_boxes;
                boxTypes[j][1] = temp_units;
            }
        }
    }
    
    int totalUnits = 0;
    int remainingCapacity = truckSize;
    
    for (int i = 0; i < boxTypesSize && remainingCapacity > 0; i++) {
        int boxesToTake = (boxTypes[i][0] < remainingCapacity) ? boxTypes[i][0] : remainingCapacity;
        totalUnits += boxesToTake * boxTypes[i][1];
        remainingCapacity -= boxesToTake;
    }
    
    return totalUnits;
}
