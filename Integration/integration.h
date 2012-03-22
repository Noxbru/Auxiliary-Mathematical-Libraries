/* This is a library to use matrixes in C
 * written by Bruno Jiménez
 * under the Catware licence && GPL licence
 * More info of the Catware licence can be
 * found here: http://lists.debian.org/debian-devel/1999/01/msg01921.html
 * but it says that if you find this code useful
 * you should pay for it petting some cats
 * Any request or bug or anything of the code
 * please, contact brunojimen(at)gmail(dot)com
 */
#ifndef _INTEGRATION_H
#define _INTEGRATION_H

#include <stdio.h>
#include <math.h>
#include "integration.h"

double integration_trapezoidal(double *x, double a, double b, unsigned int n);
double integration_simpson(double *x, double a, double b, unsigned int n);
double integration_boole(double *x, double a, double b, unsigned int n);

double integration_function_trapezoidal(double (*function)(double x), double a, double b, unsigned int n);
double integration_function_simpson(double (*function)(double x), double a, double b, unsigned int n);
double integration_function_boole(double (*function)(double x), double a, double b, unsigned int n);

#endif
