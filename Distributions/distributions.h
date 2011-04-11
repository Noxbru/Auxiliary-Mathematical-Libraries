/* This is a library to use vectors in C
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
#include <stdlib.h>
#include <math.h>

/* A little factorial function needed for the
 * basic poisson probability function           */
int fac(int i)
{
    double factorial=1;
    while (0<i)
        factorial*=i--;
    return factorial;
}

/* Basic poisson probability function
 * Returns the probability of having the i
 * event in a poisson distribution with
 * mean = var                               */
double poisson(int i, double var)
{
    double prob;
    prob=pow(var,i);
    prob*=exp(-var);
    prob/=fac(i);
    return prob;
}

/* A more advanced poisson probability function
 * Returns an array of doubles with the poisson
 * probabilities of the values up to the given  */
/* The reason this returns an array of doubles
 * is that when I implemented this function, I
 * needed to do exp(-117,96) and as a float is 0    */
double * poisson_up_to(int i, double var)
{
    double *prob;
    unsigned int j;
    prob=malloc(i++*sizeof(double));
    prob[0]=exp(-var);
    for (j = 1; j < i; j++)
        prob[j]=prob[j-1]*var/j;
    return prob;
}

/* Returns the probability of having an event
 * between a and b in a poisson distribution
 * with mean = var                              */
double poisson_from_to(int a, int b, double var)
{
    double prob1,prob2,probtot=0;
    unsigned int i;
    b++; a--;
    prob1=exp(-var);
    for (i = 1; i < b; i++)
    {
        if(a<i)
            probtot+=prob1;
        prob2=prob1*var/i;
        prob1=prob2;
    }
    return probtot;
}

/* Basic gauss probability function
 * Returns the probability of having the x
 * result in a gauss distribution with
 * mean and variance = sigma2                */
double gauss(double x, double mean, double sigma2)
{
    double aux=(x-mean)*(x-mean);
    aux/=(2*sigma2);
    aux=exp(-aux);
    aux/=sqrt(2*MATH_PI*sigma2);
    return aux
}

/* Returns the probability of being the x event
 * between a and b in a gauss distribution
 * with mean and variance = sigma2              */
double gauss_from_to(double a, double b, double mean, double sigma2)
{
    double aux;
    aux=gauss(a,mean,sigma2);
    aux+=4*gauss((a+b)/2,mean,sigma2);
    aux+=gauss(b,mean,sigma2);
    aux*=(b-a)/6;
    return aux;
}
