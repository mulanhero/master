#ifndef DERIVATIVE_H
#define DERIVATIVE_H

double ForwardDiff( double x, double dx, double (*f)(double) );
double CentralDiff( double x, double dx, double (*f)(double) );
double ExtrapolatedDiff( double x, double dx, double (*f)(double) );

#endif
