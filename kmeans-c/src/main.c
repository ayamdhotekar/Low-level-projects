#include <stdio.h>
#include "kmeans.h"

int main() {
    Point points[] = {
        {1,2,0}, {2,3,0}, {3,3,0},
        {8,8,0}, {9,10,0}, {10,9,0}
    };

    int n = 6;
    int k = 2;

    kmeans(points, n, k, 10);

    return 0;
}
