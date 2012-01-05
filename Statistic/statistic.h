/* This is a library to make some statistic in C
 * written by Bruno Jiménez
 * under the Catware licence && GPL licence
 * More info of the Catware licence can be
 * found here: http://lists.debian.org/debian-devel/1999/01/msg01921.html
 * but it says that if you find this code useful
 * you should pay for it petting some cats
 * Any request or bug or anything of the code
 * please, contact brunojimen(at)gmail(dot)com
 */

#ifndef STATISTIC_H
#define STATISTIC_H

double mean(double *a, unsigned int n)
double mean2(double *a, unsigned int n)
double variance(double *a, unsigned int n)
double covariance(double *a, double *b, unsigned int n)

#endif
