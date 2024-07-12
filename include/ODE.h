#ifndef ODE_H
#define ODE_H

#include <functional>

double differentiateExtrap(double x, std::function<double(double, double)> theFunction);
double odeEuler(double t, double yMinus1, std::function<double(double, double)> theFunction);
double odeRK2(double t, std::function<double(double, double)> theFunction);

#endif // ODE_H
