#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "complex_polar.h"

struct complex_binary
{
    double real, imaginary;
};

/* Creates a complex number in binary form with
 * real part=a and imaginary part=b             */
struct complex_binary create_complex_binary(double a, double b)
{
    struct complex_binary z;
    z.real=a;
    z.imaginary=b;
    return z;
}

/* Gets a complex number in binary form from
 * keyboard                                 */
struct complex_binary get_complex(void)
{
    struct complex_binary z;
    printf("Enter real part\n");
    scanf("%f",&z.real);
    printf("Enter imaginary part\n");
    scanf("%f",&z.imaginary);
    return z;
}

/* Copy a complex number in binary form */
struct complex_binary copy_complex_binary(struct complex_binary z)
{
    struct complex_binary c;
    c.real=z.real;
    c.imaginary=z.imaginary;
    return c;
}

/* Prints a complex number in binary form with
 * the format " # + i#"
 * If some of the parts is 0 or the imaginary
 * part is <0 the format is adapted             */
void print_complex(struct complex_binary z)
{
    if(z.real!=0&&z.imaginary>0)
        printf("%f + i%f\n",z.real,z.imaginary);
    else if(z.real!=0&&z.imaginary==0)
        printf("%f\n",z.real);
    else if(z.real!=0&&z.imaginary<0)
        printf("%f - i%f\n",z.real,fabs(z.imaginary));
    else if(z.real==0&&z.imaginary>0)
        printf("i%f\n",z.imaginary);
    else if(z.real==0&&z.imaginary<0)
        printf("-i%f\n",fabs(z.imaginary));
    else if(z.real==0&&z.imaginary==0)
        printf("0\n");
}

/* Returns the real part of a complex number
 * in binary form                           */
double real_part_binary(struct complex_binary z)
{
    return z.real;
}

/* Returns the imaginary part of a complex number
 * in binary form                           */
double imaginary_part_binary(struct complex_binary z)
{
    return z.imaginary;
}

/* Returns the module of a complex number
 * in binary form                           */
double module_binary(struct complex_binary z)
{
    double real=fabs(z.real);
    double imaginary=fabs(z.imaginary);
    if(real==0&&imaginary==0)
        return 0;
    if(real<=imaginary)
    {
        double r=imaginary/real;
        return r*sqrt(1+r*r);
    }
    else
    {
        double r=real/imaginary;
        return r*sqrt(1+r*r);
    }
}

/* Returns the argument of a complex number
 * in binary form
 * Note that it goes from -PI to +PI        */
double argument_binary(struct complex_binary z)
{
    double c=atan2(z.imaginary,z.real);
    return c;
}

/* Returns the complex conjugate of a complex
 * number in binary form                        */
struct complex_binary conjugate_binary(struct complex_binary z)
{
    struct complex_binary c;
    c.real=z.real;
    c.imaginary=-z.imaginary;
    return c;
}

/* Returns the reciprocal of a complex number
 * in binary form                               */
struct complex_binary reciprocal_binary(struct complex_binary z)
{
    struct complex_binary c;
    double denominator=z2.real*z2.real+z2.imaginary*z2.imaginary;
    c.real=z.real/denominator;
    c.imaginary=-z.imaginary/denominator;
    return c;
}

/* Transforms a complex number in binary form
 * to polar form
 * Note that te argument goes from -PI to +PI   */
struct complex_polar binary_to_polar(struct complex_binary z)
{
    struct complex_polar z1;
    z1.module=module_binary(z);
    z1.argument=argument_binary(z);
    return z1;
}

/* Multiply a complex number in binary form by
 * a scalar                                      */
struct complex_binary multiply_complex_binary_by(struct complex_binary z, double n)
{
    struct complex_binary c;
    c.real=z.real*n;
    c.imaginary=z.imaginary*n;
    return c;
}

/* Sums two complex numbers in binary form */
struct complex_binary sum_complex_binary(struct complex_binary z1, struct complex_binary z2)
{
    struct complex_binary c;
    c.real=z1.real+z2.real;
    c.imaginary=z1.imaginary+z2.imaginary;
    return c;
}

/* Subtract two complex numbers in binary form */
struct complex_binary subtraction_complex_binary(struct complex_binary z1, struct complex_binary z2)
{
    struct complex_binary c;
    c.real=z1.real-z2.real;
    c.imaginary=z1.imaginary-z2.imaginary;
    return c;
}

/* Multiply two complex numbers in binary form */
struct complex_binary multiplication_complex_binary(struct complex_binary z1, struct complex_binary z2)
{
    struct complex_binary c;
    c.real=z1.real*z2.real-z1.imaginary*z2.imaginary;
    c.imaginary=z1.real*z2.imaginary+z1.imaginary*z2.real;
    return c;
}

/* Divide two complex numbers in binary form */
struct complex_binary division_complex_binary(struct complex_binary z1, struct complex_binary z2)
{
    struct complex_binary c;
    double denominator=z2.real*z2.real+z2.imaginary*z2.imaginary;
    c.real=(z1.real*z2.real+z1.imaginary*z2.imaginary)/denominator;
    c.imaginary=(z1.imaginary*z2.real-z1.real*z2.imaginary)/denominator;
    return c;
}
