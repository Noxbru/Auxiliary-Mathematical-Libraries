#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define COMPLEX_POLAR

#ifndef COMPLEX_BINARY
#include "complex_binary.h"
#endif

struct complex_polar
{
    double module, argument;
};

/* Creates a complex number in polar form with
 * module=a and argument=b
 * Note that argument goes from -PI to +PI      */
struct complex_polar create_complex_polar(double a, double b)
{
    if(a==0)
        printf("WARNING: CREATING A 0 length complex number\n");
    if(b<-M_PI||b>M_PI) //CHECK! STUDY A CHECK ARGUMENT FUNCTION!
        b=fmod(b,M_PI);

    struct complex_polar z;
    z.module=a;
    z.argument=b;
    return z;
}

/* Gets a complex number in polar form from
 * keyboard
 * This function relays on the create function
 * to give the correct argument                 */
struct complex_polar get_complex(void)
{
    double a,b;
    printf("Enter module\n");
    scanf("%f",&a);
    printf("Enter argument\n");
    scanf("%f",&b);
    return create_complex_polar(a,b);
}

/* Copy a complex number in polar form */
struct complex_polar copy_complex_polar(struct complex_polar z)
{
    struct complex_polar c;
    c.module=z.module;
    c.argument=z.argument;
    return c;
}

/* Prints a complex number in polar form with
 * the format: "module: # argument: #"          */
void print_complex(struct complex_polar z)
{
    printf("module: %f  argument: %f\n",z.module,z.argument);
}

/* Transforms a complex number in polar form
 * to binary form                           */
struct complex_binary polar_to_binary(struct complex_polar z)
{
    struct complex_binary z1;
    z1.real=real_part_polar(z);
    z1.imaginary=imaginary_part_polar(z);
    return z1;
}

/* Sums two complex numbers in polar form
 * This functions transforms the numbers
 * to binary form, sums them and then
 * transform the answer back to polar       */
struct complex_polar sum_complex_polar(struct complex_polar z1, struct complex_polar z2)
{
    struct complex_binary z3,z4;
    z3=polar_to_binary(z1);
    z4=polar_to_binary(z2);
    z3=sum_complex_binary(z3,z4);
    return binary_to_polar(z3);
}

/* Subtract two complex numbers in polar form
 * This functions transforms the numbers
 * to binary form, subtract them and then
 * transform the answer back to polar          */
struct complex_polar subtraction_complex_polar(struct complex_polar z1, struct complex_polar z2)
{
    struct complex_binary z3,z4;
    z3=polar_to_binary(z1);
    z4=polar_to_binary(z2);
    z3=subtraction_complex_binary(z3,z4);
    return binary_to_polar(z3);
}

/* Multiplicate two numbers in polar form */
struct complex_polar multiplication_complex_polar(struct complex_polar z1, struct complex_polar z2)
{
    struct complex_polar c;
    c.module=z1.module*z2.module;
    c.argument=z1.argument+z2.argument;
    if(c.argument<-M_PI||c.argument>M_PI)
        c.argument=fmod(c.argument,M_PI);
    return c;
}

/* Divide two numbers in polar form */
struct complex_polar division_complex_polar(struct complex_polar z1, struct complex_polar z2)
{
    struct complex_polar c;
    c.module=z1.module/z2.module;
    c.argument=z1.argument-z2.argument;
    if(c.argument<-M_PI||c.argument>M_PI)
        c.argument=fmod(c.argument,M_PI);
    return c;
}

/* Returns the real part of a complex number
 * in polar form                            */
double real_part_polar(struct complex_polar z)
{
    return z.module*cos(z.argument);
}

/* Returns the imaginary part of a complex number
 * in polar form                                 */
double imaginary_part_polar(struct complex_polar z)
{
    return z.module*sin(z.argument);
}

/* Returns the module of a complex number
 * in polar form                            */
double module_polar(struct complex_polar z)
{
    return z.module;
}

/* Returns the argument of a complex number
 * in polar form                            */
double argument_polar(struct complex_polar z)
{
    return z.argument;
}

/* Returns the complex conjugate of a complex
 * number in polar form                         */
struct complex_polar conjugate_polar(struct complex_polar z)
{
    struct complex_polar c;
    c.module=z.module
    c.argument=-z.argument;
    return c;
}

/* Returns the reciprocal of a complex number
 * in polar form                                */
struct complex_polar reciprocal_polar(struct complex_polar z)
{
    struct complex_polar c;
    c.module=1/z.module;
    c.argument=z.argument;
    return c;
}

/* Multiply a complex number in polar form by
 * a scalar                                      */
struct complex_binary multiply_complex_polar_by(struct complex_polar z, double n)
{
    struct complex_polar c;
    c.module=z.module*n
    c.argument=z.argument;
    return c;
}
