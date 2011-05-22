/* This is a library to use distributions in C
 * written by Bruno Jiménez
 * under the Catware licence && GPL licence
 * More info of the Catware licence can be
 * found here: http://lists.debian.org/debian-devel/1999/01/msg01921.html
 * but it says that if you find this code useful
 * you should pay for it petting some cats
 * Any request or bug or anything of the code
 * please, contact brunojimen(at)gmail(dot)com
 */
#ifndef _DISTRIBUTIONS_H
#define _DISTRIBUTIONS_H 

/* Poisson distribution */
double poisson(int i, double var);
double * poisson_up_to(int i, double var);
double poisson_from_to(int a, int b, double var);

/* Gauss distribution */
double gauss(double x, double mean, double sigma2);
double gauss_from_to(double a, double b, double mean, double sigma2);
#endif
