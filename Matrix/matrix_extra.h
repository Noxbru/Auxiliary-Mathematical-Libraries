/* a */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MATRIX
#include "matrix.h"
#endif

#ifndef VECTOR
#include "../Vector/vector.h"
#endif

#define MATRIX_EXTRA

/* Creates a row matrix from a vector */
struct matrix row_matrix_from_vector(struct vector v)
{
    struct matrix m=create_matrix(1,v.dimension)
    unsigned int i;
    for (i = 0; i < m.columns; i++)
        m.mat[0][i]=v.vec[i];
    return m;
}

/* Creates a column matrix from a vector */
struct matrix column_matrix_from_vector(struct vector v)
{
    struct matrix m=create_matrix(v.dimension,1);
    unsigned int i;
    for (i = 0; i < m.rows; i++)
        m.mat[i][0]=v.vec[i];
    return m;
}

/* Creates a vector from a matrix
 * This function checks for whether the matrix is
 * a column or a row and creates the corresponding
 * vector
 * Returns a 0-dimensional vector if the matrix
 * isn't a row or a column                          */
struct vector vector_from_matrix(struct matrix m)
{
    if(m.rows!=1)
        if(m.columns!=1)
        {
            printf("This matrix doesn't have only a row or a column\n");
            return crete_vector(0);
        }
        else
        {
            struct vector v=create_vector(m.rows);
            unsigned int i;
            for (i = 0; i < m.rows; i++)
                v.vec[i]=m.mat[i][0];
            return v;
        }
    struct vector v=create_vector(m.columns);
    unsigned int i;
    for (i = 0; i < m.columns; i++)
        v.vec[i]=m.mat[0][i];
    return v;
}

/* Multiplicates two vectors so the result is a matrix
 * vector1-dimensional x vector2-dimensional            */
struct matrix matrix_product(struct vector v1, struct vector v2)
{
    struct matrix m1=column_matrix_from_vector(v1);
    struct matrix m2=row_matrix_from_vector(v2);
    struct matrix m=matrix_multiplication(m1,m2);
    return m;
}

/* Multiplicates a matrix by a row vector from the left
 * The result is returned as a vector
 * Returns a 0-dimensional vector if the number of rows
 * of the matrix and the dimension of the original vector
 * are different                                            */
struct vector multiply_matrix_from_left(struct matrix m, struct vector v)
{
    if(m.rows!=v.dimension)
    {
        printf("The number of rows of the matrix\n");
        printf("Is different from the dimension of the Vectors\n");
        printf("Impossible to multiply them\n");
        return create_vector(0);
    }

    struct vector v1=create_vector(m.columns);
    unsigned int i,j;
    for (i = 0; i < m.columns; i++)
        for (j = 0; j < m.rows; j++)
            v1.vec[i]+=v1.vec[j]*m.mat[i][j];
    return v1;
}

/* Multiplicates a matrix by a column vector from the right
 * The result is returned as a vector
 * Returns a 0-dimensional vector if the number of columns
 * of the matrix and the dimension of the original vector
 * are different                                            */
struct vector multiply_matrix_from_right(struct matrix m, struct vector v)
{
    if(m.rows!=v.dimension)
    {
        printf("The number of columns of the matrix\n");
        printf("Is different from the dimension of the Vectors\n");
        printf("Impossible to multiply them\n");
        return create_vector(0);
    }

    struct vector v1=create_vector(m.rows);
    unsigned int i,j;
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.columns; j++)
            v1.vec[i]+=v1.vec[j]*m.mat[i][j];
    return v1;
}

/* Multiplicates a matrix from the left by a vector
 * v1, and from the right by a vector v2
 * Relies on the multiply a matrix from a side
 * and scalar product to return warnings            */
float mutiply_matrix_from_both_sides(struct matrix m, struct vector v1, struct vector v2)
{
    struct vector v=multiply_matrix_from_right(m,v2);
    return scalar_product(v1,v);
}

/* Multiplicates a matrix from the left and the
 * right by a vector v
 * Relies on the multiply a matrix from a side
 * and scalar product to return warnings            */
float bilinear_product(struct matrix m, struct vector v)
{
    struct vector v1=multiply_matrix_from_right(m,v);
    return scalar_product(v,v1);
}
