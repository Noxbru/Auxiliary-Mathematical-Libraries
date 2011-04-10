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
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifndef VECTOR
#define VECTOR
#endif

struct vector
{
    double *vec;
    unsigned int dimension;
};

/* This function creates a n-dimensional vector
 * filled with 0s                               */
struct vector create_vector(unsigned int n)
{
    struct vector v;
    v.dimension=n;
    v.vec=malloc(n*sizeof(double));
    return v;
}

/* This function ask for a vector from keyboard */
struct vector get_vector(void)
{
    unsigned int i;
    printf("Please, insert dimension of the vector\n");
    scanf("%u",&i);
    struct vector v=create_vector(i);
    for (i = 0; i < v.dimension; i++)
    {
        printf("Please, insert the %u component of the vector\n",i+1);
        scanf("%f",&v.vec[i]);
    }
}

/* This function is used to create a vector from a string
 * The string has to be a series of numbers separated by
 * spaces                                                   */
/* As I don't recommend the use of strings in C, I strongly
 * recommend not to use this function                       */
struct vector vector_from_string(char *c, unsigned int n)
{
    struct vector v=create_vector(n);
    char *number=strtok(c," ");
    unsigned int i;

    for (i = 0; i < v.dimension; i++)
    {
        if(number!=NULL)
        {
            v.vec[i]=atof(number);
            number=strtok(NULL," ");
        }
        else
        {
            printf("Problems creating vector\n");
            printf("It couldn't be totally filled\n");
            printf("Filled until %u\n",i+1);
            return v;
        }
    }
    if(number!=NULL)
    {
        printf("There are still numbers in the string\n");
        printf("that couldn't be written in the vector\n");
    }
}

/* This function is used to create a vector from an array */
struct vector vector_from_array(double *a, unsigned int n)
{
    struct vector v=create_vector(n);
    unsigned int i;
    for (i = 0; i < n; i++)
        v.vec[i]=a[i];
    return v;
}

/* This function is used to create a vector from a file
 * The file has to be a series of numbers separated by spaces
 * if there aren't enough numbers, it returns what it has done
 * and the rest is filled with 0s
 * Returns a 0-dimensional vector if there is any problem
 * opening the file                                             */
struct vector vector_from_file(char *c, unsigned int n)
{
    FILE *f;
    f=fopen(c,"r");
    if(f==NULL)
    {
        printf("Error opening file %s\n",c);
        return create_vector(0);
    }

    struct vector v=create_vector(n);
    unsigned int i;

    for (i = 0; i < n; i++)
        if(fscanf(f,"%f",&v.vec[i])==EOF)
        {
            printf("Problems creating vector\n");
            printf("It couldn't be totally filled\n");
            printf("Filled untill %u\n",i+1);
            return v;
        }
    if(!feof(f))
    {
        printf("There are still numbers in the file\n");
        printf("that couldn't be written in the vector\n");
    }
    return v;
}

/* This function returns a copy of the given vector */
struct vector copy_vector(struct vector v)
{
    unsigned int i;
    struct vector w=create_vector(v.dimension);
    for (i = 0; i < w.dimension; i++)
        w.vec[i]=v.vec[i];
    return w;
}

/* This function prints a vector */
void print_vector(struct vector v)
{
    unsigned int i;
    printf("(%f",v.vec[0]);
    for (i = 1; i < v.dimension; i++)
        printf("\t%f",v.vec[i]);
    printf(")\n");
}

/* This function prints a vector in a file
 * named as the string that c points to
 * If the file doesn't exist it is created
 * The third parameter is whether you want to
 * override the contents of the file or not     */
void print_vector_to_file(char *c, struct vector v, char over)
{
    FILE *f;
    if(over==0)
        f=fopen(c,"a");
    else
        f=fopen(c,"w");
    if(f==NULL)
        printf("Error opening file\n");
    
    unsigned int i;
    printf("(%f",v.vec[0]);
    for (i = 1; i < v.dimension; i++)
        printf("\t%f",v.vec[i]);
    printf(")\n");
}

/* This function fills a vector with a double */
void fill_vector_with(struct vector v, double n)
{
    unsigned int i;
    for (i = 0; i < v.dimension; i++)
        v.vec[i]=n;
}

/* This function returns the vector multiplied by n */
struct vector multiply_vector_by(struct vector v, double n)
{
    unsigned int i;
    struct vector w=create_vector(v.dimension);
    for (i = 0; i < v.dimension; i++)
        w.vec[i]=v.vec[i]*n;
    return w;
}

/* This function returns the module of the vector   */
/* Warning, can overflow the auxiliar double         */
double module(struct vector v)
{
    unsigned int i;
    double aux=0;
    for (i = 0; i < v.dimension; i++)
        aux+=v.vec[i]*v.vec[i];
    return sqrt(aux);
}

/* Alternative code for the module function
 * is slower but safer with big components  */
/*
double module(struct vector v)
{
    double aux=max_component(v);
    double aux2=aux*aux;
    double mod=0;
    unsigned int i;
    for (i = 0; i < v.dimension; i++)
        mod+=v.vec[i]*v.vec[i]/aux2;
    return aux*sqrt(mod);
}
*/

/* This function returns the unitary vector from
 * an input vector                               */
struct vector unitary_vector(struct vector v)
{
    double aux=module(v);
    if(aux==1)
        return copy_vector(v);
    struct vector w=create_vector(v.dimension);
    unsigned int i;
    for (i = 0; i < v.dimension; i++)
        w.vec[i]=v.vec[i]/aux;
    return w;
}

/* This function returns the maximum component
 * of the vector                                */
double max_component(struct vector v)
{
    unsigned int i;
    double aux;
    for (i = 0; i < v.dimension; i++)
        if(v.vec[i]>aux)
            aux=v.vec[i];
    return aux;
}

/* This function returns the minimum component
 * of the vector                                */
double min_component(struct vector v)
{
    unsigned int i;
    double aux;
    for (i = 0; i < v.dimension; i++)
        if(v.vec[i]<aux)
            aux=v.vec[i];
    return aux;
}

/* This function compares two vectors
 * returns -1 if they can't be compared
 * returns 0 if they are different
 * returns 1 if they are the same vector    */
int compare_vector(struct vector v1, struct vector v2)
{
    if(v1.dimension!=v2.dimension)
    {
        printf("These vectors can't be compared\n");
        printf("They don't have the same size\n");
        return -1;
    }

    unsigned int i;
    for (i = 0; i < v1.dimension; i++)
        if(v1.vec[i]!=v2.vec[i])
            return 0;
    return 1;
}

/* This function checks if two vectors are orthogonal
 * returns -1 if they can't be checked
 * returns 0 if they aren't orthogonal
 * returns 1 if they are orthogonal                     */
int check_orthogonal(struct vector v1, struct vector v2)
{
    if(v1.dimension!=v2.dimension)
    {
        printf("These vectors can't be compared\n");
        printf("They don't have the same size\n");
        return -1;
    }

    return !scalar_product(v1, v2);
}

/* This function checks if two vectors are parallel
 * returns -1 if they can't be checked
 * returns 0 if they aren't parallel
 * returns 1 if they are parallel                   */
int check_parallel(struct vector v1, struct vector v2)
{
    if(v1.dimension!=v2.dimension)
    {
        printf("These vectors can't be compared\n");
        printf("They don't have the same size\n");
        return -1;
    }

    unsigned int i;
    double aux=v1[0]/v2[0];
    for (i = 1; i < v1.dimension; i++)
        if(v1[i]/v2[i]!=aux)
            return 0;
    return 1;
}

/* This function returns the sum of two vectors
 * returns a 0-dimensional vector if they can't
 * be summed                                    */
struct vector vector_sum(struct vector v1, struct vector v2)
{
    if(v1.lenght!=v2.dimension)
    {
        printf("These vectors doesn't have the same size\n");
        printf("Imposible to sum them\n");
        return create_vector(0);
    }

    unsigned int i;
    struct vector w=create_vector(v1.dimension);
    for (i = 0; i < v1.dimension; i++)
        w.vec[i]=v1.vec[i]+v2.vec[i];
    return w;
}

/* This function returns the subtraction of two
 * vectors
 * returns a 0-dimensional vector if they can't
 * be subtracted                                 */
struct vector vector_subtraction(struct vector v1, struct vector v2)
{
    if(v1.lenght!=v2.dimension)
    {
        printf("These vectors doesn't have the same size\n");
        printf("Imposible to sum them\n");
        return create_vector(0);
    }

    unsigned int i;
    struct vector w=create_vector(v1.dimension);
    for (i = 0; i < v1.dimension; i++)
        w.vec[i]=v1.vec[i]-v2.vec[i];
    return w;
}

/* This function returns the scalar product of two
 * vectors
 * returns -1 if scalar product can't be calculated */
double scalar_product(struct vector v1, struct vector v2)
{
    if(v1.lenght!=v2.dimension)
    {
        printf("These vectors doesn't have the same size\n");
        printf("Imposible calculate the scalar product\n");
        return -1;
    }

    unsigned int i;
    double a=0;
    for (i = 0; i < v1.dimension; i++)
        a+=v1.vec[i]*v2.vec[i];
    return a;
}

/* This function returns the vectorial product of
 * two vectors if they are 3-dimensional
 * returns a 0-dimensional vector if vectorial
 * product can't be calculated                      */
struct vector vectorial_product(struct vector v1, struct vector v2)
{
    if(v1.dimension!=3||v2.dimension!=3)
    {
        printf("These vectors arent 3-dimensional\n");
        printf("Imposible to calculate the vectorial product\n");
        return create_vector(0);
    }

    struct vector w=create_vector(3);
    w.vec[0]=v1.vec[1]*v2.vec[2]-v1.vec[2]*v2.vec[1];
    w.vec[1]=v1.vec[2]*v2.vec[0]-v1.vec[0]*v2.vec[2];
    w.vec[2]=v1.vec[0]*v2.vec[1]-v1.vec[1]*v2.vec[0];
    return w;
}

/**/
struct vector projection_along(struct vector v1, struct vector v2)
{
    if(v1.dimension!=v2.dimension)
    {
        printf("These vectors doesn't have the same size\n");
        printf("Imposible calculate the projection");
    }

    struct vector w=unitary_vector(v1);
    double aux=scalar_product(v1,v2)/module(v1);
    w=multiply_vector_by(v1,aux);
    return w;
}

/* This function transforms a set of vectors into
 * an orthonormal set: an orthonormal base          */
struct vector * gram_schmidt(struct vector *v, unsigned int n)
{
    struct vector *w;
    w=malloc(n*sizeof(struct vector));
    w[0]=unitary_vector(v[0]);

    unsigned int i,j;
    struct vector aux;
    for (i = 1; i < n; i++)
    {
        w[i]=copy_vector(v[i]);
        for (j = 0; j < i; j++)
        {
            aux=projection_along(w[j],v[i])
            w[i]=vector_subtraction(w[i],aux);
        }
        w[i]=unitary_vector(w[i]);
    }
    return w;
}
