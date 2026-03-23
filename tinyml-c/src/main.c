#include <stdio.h>
#include <stdlib.h>
#include "linear_regression.h"

#define MAX_DATA 100

int load_csv(const char *filename, double *x, double *y) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%lf,%lf", &x[i], &y[i]) != EOF) {
        i++;
    }

    fclose(file);
    return i;
}

int main() {
    double x[MAX_DATA], y[MAX_DATA];

    int n = load_csv("data/sample.csv", x, y);

    if (n == 0) {
        printf("No data loaded.\n");
        return 1;
    }

    LinearRegression model = {0.0, 0.0};

    printf("Training on %d samples...\n", n);

    train(&model, x, y, n, 0.01, 1000);

    printf("\nFinal Model:\n");
    printf("Weight: %f\n", model.weight);
    printf("Bias: %f\n", model.bias);

    double test = 6.0;
    printf("\nPrediction for %.2f: %f\n", test, predict(&model, test));

    return 0;
}
