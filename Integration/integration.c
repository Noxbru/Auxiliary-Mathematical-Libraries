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

#include <stdio.h>
#include <math.h>
#include "integration.h"

/* This function computes the integral
 * of a series of n points of data, x,
 * from a to b asuming that the values
 * of x are separated the same step,
 * h, using the trapezoidal rule.
 * This rule says that
 * integral from a to b of f(x)
 * is sum of h*(f(x)+f(x+h))/2
 * so every point between a and b is
 * summed two times, and f(a) and f(b)
 * only one.
 * The error of this method goes as
 * (b-a)/12*h²f''                       */
double integration_trapezoidal(double *x, double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    unsigned int i;

    for(i = 1; i < n-1; i++)
        integral+=x[i];

    integral+=x[0]/2.;
    integral+=x[n-1]/2.;
    integral*=step;
    return integral;
}

/* This function computes the integral
 * of a series of n points of data, x,
 * from a to b asuming that the values
 * of x are separated the same step,
 * h, using Simpson rule.
 * This rule says that
 * integral from a to b of f(x)
 * is sum of h*(f(x-h)+4f(x)+f(x+h))/3
 * so every point between a and b is
 * summed two times if its index is
 * even, and four if its index is odd,
 * and f(a) and f(b) only one.
 * The error of this method goes as
 * (b-a)/180*h⁴f⁽⁴⁾
 * this is only achieved if n is an odd
 * number, if it is even the error is
 * much higher because a final step
 * integrating with trapeziums          */
double integration_simpson(double *x, double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    unsigned int i;

    for(i = 1; i < n-2; i+=2)
    {
        integral+=4*x[i];
        integral+=2*x[i+1];
    }
    // If there's an odd number of points, as in
    // 3, there's a point that isn't added and
    // we have to check for it
    if(i==n-2)
    {
        integral+=4*x[i];
        integral+=x[n-1];
        integral*=step/3;
    }
    // If there's an even number of points, as in
    // 4, we can only integrate till n-2 and we
    // have to add the rest as if it were a
    // trapezium, so we have to substract the n-2
    // point, and multiply by h/3 to integrate
    // till there as Simpson, and add n-2 and n-1
    // as a trapezium.
    else if(i==n-1)
    {
        integral-=x[n-2];
        integral*=step/3;
        integral+=(x[n-2]+x[n-1])*step/2.;
    }

    return integral;
}
