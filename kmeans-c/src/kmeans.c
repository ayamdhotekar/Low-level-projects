#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kmeans.h"

double distance(Point a, Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void kmeans(Point *points, int n, int k, int epochs) {
    Point centroids[k];

    for (int i = 0; i < k; i++) {
        centroids[i] = points[i];
    }

    for (int e = 0; e < epochs; e++) {

        for (int i = 0; i < n; i++) {
            double min_dist = 1e9;
            int best = 0;

            for (int j = 0; j < k; j++) {
                double d = distance(points[i], centroids[j]);
                if (d < min_dist) {
                    min_dist = d;
                    best = j;
                }
            }

            points[i].cluster = best;
        }

        for (int j = 0; j < k; j++) {
            double sum_x = 0, sum_y = 0;
            int count = 0;

            for (int i = 0; i < n; i++) {
                if (points[i].cluster == j) {
                    sum_x += points[i].x;
                    sum_y += points[i].y;
                    count++;
                }
            }

            if (count > 0) {
                centroids[j].x = sum_x / count;
                centroids[j].y = sum_y / count;
            }
        }

        printf("Epoch %d completed\n", e);
    }

    printf("\nFinal clusters:\n");
    for (int i = 0; i < n; i++) {
        printf("(%.2f, %.2f) -> Cluster %d\n", points[i].x, points[i].y, points[i].cluster);
    }
}
