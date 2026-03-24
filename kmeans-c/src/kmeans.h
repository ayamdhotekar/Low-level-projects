#ifndef KMEANS_H
#define KMEANS_H

typedef struct {
    double x;
    double y;
    int cluster;
} Point;

void kmeans(Point *points, int n, int k, int epochs);

#endif
