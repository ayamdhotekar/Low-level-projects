#include <stdio.h>
#include "linear_regression.h"

double predict(LinearRegression *model, double x) {
    return model->weight * x + model->bias;
}

double compute_loss(LinearRegression *model, double *x, double *y, int n) {
    double loss = 0.0;
    for (int i = 0; i < n; i++) {
        double y_pred = predict(model, x[i]);
        double error = y_pred - y[i];
        loss += error * error;
    }
    return loss / n;
}

void train(LinearRegression *model, double *x, double *y, int n, double lr, int epochs) {
    for (int e = 0; e < epochs; e++) {
        double dw = 0.0;
        double db = 0.0;

        for (int i = 0; i < n; i++) {
            double y_pred = predict(model, x[i]);
            double error = y_pred - y[i];

            dw += error * x[i];
            db += error;
        }

        dw /= n;
        db /= n;

        model->weight -= lr * dw;
        model->bias -= lr * db;

        if (e % 100 == 0) {
            printf("Epoch %d, Loss: %f\n", e, compute_loss(model, x, y, n));
        }
    }
}
