#include "include/ODE.h"

#include <cmath>
double h = pow(2,-40);

double differentiateExtrap(double x, double y, std::function<double(double, double)> theFunction){
    return (8*(theFunction(x+h/4, y)-theFunction(x-h/4, y)) - (theFunction(x+h/2, y)-theFunction(x-h/2, y)))/3/h;
}


double odeEuler(double t, double yMinus1,  std::function<double(double, double)> theFunction){
    return theFunction(t-h, yMinus1)+h * differentiateExtrap(t-h, theFunction);
}

double odeRK2(double t, double yMinus1,  std::function<double(double, double)> theFunction){
    return theFunction(t-h, yMinus1)+h*theFunction(t-(h/2), odeEuler(t-(h/2), yMinus1, theFunction));
}
