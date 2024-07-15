#ifndef ODE_H
#define ODE_H

#include <functional>

using namespace std;

vector<double> odeEuler(double t, vector<double> yMinus1, function<vector<double>(double, vector<double>)> theFunction);
vector<double> odeRK2(double t, vector<double> yMinus1, function<vector<double>(double, vector<double>)> theFunction);
vector<double> odeRK4(double t, vector<double> yMinus1, function<vector<double>(double, vector<double>)> theFunction);

#endif // ODE_H
