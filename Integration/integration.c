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

    integral+=x[0];
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

/* This function computes the integral
 * of a series of n points of data, x,
 * from a to b asuming that the values
 * of x are separated the same step,
 * h, using Boole rule.
 * This rule says that
 * integral from a to b of f(x)
 * is sum of
 * h*(7f(x-2h)+32f(x-h)+12f(x)+32f(x+h)+7f(x+2h))2/45
 * so every point between a and b is
 * summed thirty-two, twelve or fourteen
 * times depending on its index, and
 * f(a) and f(b) only seven.
 * The error of this method goes as
 * (b-a)8/945*h⁷f⁽⁶⁾
 * this is only achieved if n is the
 * sum of five and a multiply of four,
 * otherwise we have to finish the
 * integral using simpson or the
 * trapezoidal rule                     */
double integration_boole(double *x, double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    unsigned int i;

    integral+=7*x[0];
    for(i = 1; i < n-4; i+=4)
    {
        integral+=32*x[i];
        integral+=12*x[i+1];
        integral+=32*x[i+2];
        integral+=14*x[i+3];
    }

    // Integrating the final points
    // using Boole's Rule
    if(i==n-4)
    {
        integral+=32*x[i];
        integral+=12*x[i+1];
        integral+=32*x[i+2];
        integral+=7*x[n-1];
        integral*=2*step/45;
    }
    // Integrating the final points
    // using Simpson's and Trapezoidal
    // Rule
    else if(i==n-3)
    {
        integral-=7*x[i-1]; 
        integral*=2*step/45;
        integral+=(x[i-1]+4*x[i]+x[i+1])*step/3;
        integral+=(x[i+1]+x[i+2])*step/2.;
    }
    // Integrating the final points
    // using Simpson's Rule
    else if(i==n-2)
    {
        integral-=7*x[i-1]; 
        integral*=2*step/45;
        integral+=(x[i-1]+4*x[i]+x[i+1])*step/3;
    }
    // Integrating the final points
    // using the Trapezoidal's Rule
    else if(i==n-1)
    {
        integral-=7*x[i-1]; 
        integral*=2*step/45;
        integral+=(x[i-1]+x[i])*step/2.;
    }

    return integral;
}

/* This function computes the integral
 * of a function (*function(x)), which
 * returns a double, from a to b using
 * n main points and calculating the
 * function at points separated the
 * same step, h, using the trapezoidal
 * rule.
 * This rule says that
 * integral from a to b of f(x)
 * is sum of h*(f(x)+f(x+h))/2
 * so every point between a and b is
 * summed two times, and f(a) and f(b)
 * only one.
 * The error of this method goes as
 * (b-a)/12*h²f''                       */
double integration_function_trapezoidal(double (*function)(double x), double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    double pos;

    // This for goes until b-step/2 to avoid
    // summing the final point because of a
    // loss of precision suming step so many
    // times
    for(pos = a+step; pos < b-step/2.; pos+=step)
        integral+=function(pos);

    integral+=function(a)/2.;
    integral+=function(b)/2.;
    integral*=step;
    return integral;
}

/* This function computes the integral
 * of a function (*function(x)), which
 * returns a double, from a to b using
 * n main points and calculating the
 * function at points separated the
 * same step, h, using simpson rule.
 * This rule says that
 * integral from a to b of f(x)
 * is sum of h*(f(x-h)+4f(x)+f(x+h))/3
 * so every main point between a and b
 * is summed two times, the points
 * between them four times, and f(a)
 * and f(b) only one.
 * The error of this method goes as
 * (b-a)/180*h⁴f⁽⁴⁾
 * Note that this method really uses
 * 2n-1 points and evaluations of
 * the function                         */
double integration_function_simpson(double (*function)(double x), double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    double pos;

    integral+=function(a);
    integral+=4*function(a+step/2);
    // This for goes until b-step/2 to avoid
    // summing the final point because of a
    // loss of precision suming step so many
    // times
    for(pos = a+step; pos < b-step/2.; pos+=step)
    {
        integral+=2*function(pos);
        integral+=4*function(pos+step/2);
    }

    integral+=function(b);
    integral*=step/6;
    return integral;
}

/* This function computes the integral
 * of a function (*function(x)), which
 * returns a double, from a to b using
 * n main points and calculating the
 * function at points separated the
 * same step, h, using simpson rule.
 * This rule says that
 * integral from a to b of f(x)
 * h*(7f(x-2h)+32f(x-h)+12f(x)+32f(x+h)+7f(x+2h))2/45
 * so every main point between a and b
 * is summed fourteen times, and the
 * points between them thirty-two or
 * twelve times, and f(a) and f(b)
 * only seven.
 * The error of this method goes as
 * (b-a)8/945*h⁷f⁽⁶⁾
 * Note that this method really uses
 * 4n-3 points and evaluations of
 * the function                         */
double integration_function_boole(double (*function)(double x), double a, double b, unsigned int n)
{
    double integral=0;
    // Remember that n is the number of points,
    // not the number of intervals between them
    double step=(b-a)/(n-1);
    double pos;

    integral+=7*function(a);
    integral+=32*function(a+step/4);
    integral+=12*function(a+step/2);
    integral+=32*function(a+step*3/4.);
    // This for goes until b-step/2 to avoid
    // summing the final point because of a
    // loss of precision suming step so many
    // times
    for(pos = a+step; pos < b-step/2.; pos+=step)
    {
        integral+=14*function(pos);
        integral+=32*function(pos+step/4);
        integral+=12*function(pos+step/2);
        integral+=32*function(pos+step*3/4.);
    }

    integral+=7*function(b);
    integral*=step/90;
    return integral;
}
