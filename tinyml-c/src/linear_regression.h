#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

typedef struct {
    double weight;
    double bias;
} LinearRegression;

void train(LinearRegression *model, double *x, double *y, int n, double lr, int epochs);
double predict(LinearRegression *model, double x);
double compute_loss(LinearRegression *model, double *x, double *y, int n);

#endif
