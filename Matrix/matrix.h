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
#include <stdlib.h>
#include <string.h>

#ifndef MATRIX
#define MATRIX
#endif

struct matrix
{
    float **mat;
    unsigned int rows, columns;
};

/* This function creates a matrix m x n filled with 0s */
struct matrix create_matrix(unsigned int m, unsigned int n)
{
    unsigned int i;
    struct matrix m1;
    m1.rows=m;
    m1.columns=n;
    m1.mat=malloc(m*sizeof(float *));
    for (i = 0; i < m1.rows; i++)
        m1.mat[i]=malloc(n*sizeof(float));
    return m1;
}

/* This function ask for a matrix from keyboard */
struct matrix get_matrix(void)
{
    unsigned int i,j;
    printf("Please, insert number of rows of the matrix\n");
    scanf("%u",&i);
    printf("Please, insert number of columns of the matrix\n");
    scanf("%u",&j);
    struct matrix m=create_matrix(i,j);
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.columns; j++)
        {
            printf("Please, insert the %u,%u component of the matrix\n",i+1,j+1);
            scanf("%f",&m.mat[i][j]);
        }
    return m;
}

/* This function is used to create a matrix from a string
 * The string has to be a series of numbers separated by spaces
 * If the string is not big enough, it returns what it have
 * done and the rest filled with 0s                             */
/* As I don't recommend the use of strings in C, I strongly
 * recommend not to use this function                           */
struct matrix matrix_from_string(char *c, unsigned int m, unsigned int n)
{
    struct matrix a=create_matrix(m,n);
    char *number=strtok(c," ");
    unsigned int i,j;

    for (i = 0; i < a.rows; i++)
        for (j = 0; j < a.columns; j++)
            if(number!=NULL)
            {
                a.mat[i][j]=atof(number);
                number=strtok(NULL," ");
            }
            else
            {
                printf("Problems creating matrix\n");
                printf("It couldn't be totally filled\n");
                printf("Filled untill %u,%u\n",i+1,j+1);
                return a;
            }
    if(number!=NULL)
    {
        printf("There are still numbers in the string\n");
        printf("that couldn't be written in the matrix\n");
    }
    return a;
}

/* */
struct matrix matrix_from_file(char *c, unsigned int m, unsigned int n)
{
    FILE *f;
    f=fopen(c,"r");
    if(f==NULL)
    {
        printf("Error opening file %s\n",c);
        return create_matrix(0,0);
    }

    struct matrix a=create_matrix(m,n);
    unsigned i,j;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if(fscanf(f,"%f",&a.mat[i][j])==EOF)
            {
                printf("Problems creating matrix\n");
                printf("It couldn't be totally filled\n");
                printf("Filled untill %u,%u\n",i+1,j+1);
                return a;
            }
    if(feof(f))
    {
        printf("There are still numbers in the file\n");
        printf("that couldn't be written in the matrix\n");
    }
    return a;
}

/* This function returns a copy of the given matrix */
struct matrix copy_matrix(struct matrix m)
{
    unsigned int i,j;
    struct matrix c=create_matrix(m.rows,m.columns);
    for (i = 0; i < c.rows; i++)
        for (j = 0; j < c.columns; j++)
            c.mat[i][j]=m.mat[i][j];
    return c;
}

/* This function creates an identity matrix of nth order */
struct matrix identity_matrix(unsigned int n)
{
    struct matrix c=create_matrix(n,n);
    unsigned int i;
    for (i = 0; i < n; i++)
        c.mat[i][i]=1;
    return c;
}

/* This function prints a matrix */
void print_matrix(struct matrix m)
{
    unsigned int i,j;
    for (i = 0; i < m.rows; i++)
    {
        for (j = 0; j < m.columns; j++)
            printf("%f\t",m.mat[i][j]);
        printf("\n");
    }
}

/* */
void print_matrix_to_file(char *c, struct matrix m)
{
    FILE *f;
    f=fopen(c,"w");
    if(f==NULL)
        printf("Error opening file\n");

    unsigned i,j;
    for (i = 0; i < m.rows; i++)
    {
        for (j = 0; j < m.columns; j++)
            fprintf(f,"%f\t",m.mat[i][j]);
        fprintf(f,"\n");
    }
}

/* This function checks if a matrix is symmetric
 * returns -1 if it can't be checked
 * returns  0 if it isn't symmetric
 * returns  1 if it is symmetric                */
int check_symmetric(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("This matrix isn't square\n");
        return -1;
    }

    unsigned int i,j;
    for (i = 1; i < m.rows; i++)
        for (j = i; j < m.columns; j++)
            if(m.mat[i][j]!=m.mat[j][i])
                return 0;
    return 1;
}

/* This function checks if a matrix is anti-symmetric
 * returns -1 if it can't be checked
 * returns  0 if it isn't anti-symmetric
 * returns  1 if it is anti-symmetric                  */
int check_antisymmetric(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("This matrix isn't square\n");
        return -1;
    }

    unsigned int i,j;
    for (i = 1; i < m.rows; i++)
        for (j = i; j < m.columns; j++)
            if(m.mat[i][j]!=-m.mat[j][i])
                return 0;
    return 1;
}

struct matrix traspose(struct matrix m);
struct matrix matrix_multiplication(struct matrix m1, struct matrix m2);
/* This function checks if a matrix is orthogonal
 * returns -1 if it can't be checked
 * returns 0 if it isn't orthogonal
 * returns 1 if it is orthogonal                */
int check_orthogonal(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("This matrix isn't square\n");
        return -1;
    }

    struct matrix c=traspose(m);
    c=matrix_multiplication(m,c);
    return compare_matrix(c,identity_matrix(c.rows));
}

/* This function compares two matrixes
 * returns -1 if they can't be compared
 * returns  0 if they are different
 * returns  1 if they are the same matrix */
int compare_matrix(struct matrix m1, struct matrix m2)
{
    if(m1.rows!=m2.rows||m1.columns!=m2.columns)
    {
        printf("These matrixes can't be compared\n");
        printf("They don't have the same size\n");
        return -1;
    }

    unsigned int i,j;
    for (i = 0; i < m1.rows; i++)
        for (j = 0; j < m1.columns; j++)
            if(m1.mat[i][j]!=m2.mat[i][j])
                return 0;
    return 1;
}

/* This function fills a matrix with a float */
void fill_matrix_with(struct matrix m, float n)
{
    unsigned int i,j;
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.columns; j++)
            m.mat[i][j]=n;
}

/* This function returns the matrix multiplied by n */ 
struct matrix multiply_matrix_by(struct matrix m, float n)
{
    unsigned int i,j;
    struct matrix c=create_matrix(m.rows,m.columns);
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.columns; j++)
            c.mat[i][j]=n*m.mat[i][j];
    return c;
}

/* This function returns the matrix m elevated to the nth
 * power by multiplying                                     */
struct matrix pow_matrix(struct matrix m, unsigned int n)
{
    if(m.rows!=m.columns)
    {
        printf("This matrix can't be powered\n");
        printf("It isn't square\n");
        return create_matrix(0,0);
    }

    unsigned int i;
    struct matrix c=copy_matrix(m);
    for (i = 0; i < n; i++)
        matrix_multiplication(c,m);
    return c;
}

/* This fuction returns a pointer to a copy
 * of the row-1 row
 * Note that it returns a copy of row-1
 * not a copy of row                        */
float * get_row(struct matrix m, unsigned int row)
{
    if(row+1>m.rows)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return NULL;
    }

    unsigned int i;
    float *a;
    a=malloc(m.columns*sizeof(float));
    for (i = 0; i < m.columns; i++)
        a[i]=m.mat[row][i];
    return a;
}

/* This fuction returns a pointer to a copy
 * of the column-1 column
 * Note that it returns a copy of column-1
 * not a copy of column                     */
float * get_column(struct matrix m, unsigned int column)
{
    if(column+1>m.columns)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that column\n");
        return NULL;
    }

    unsigned int i;
    float *a;
    a=malloc(m.rows*sizeof(float));
    for (i = 0; i < m.rows; i++)
        a[i]=m.mat[i][column];
    return a;
}

/* This function returns a matrix which is the
 * original matrix without the n-1 row
 * Note that the row deleted is n-1 not n
 * returns a 0x0 matrix if there isn't that
 * row in the matrix                            */
struct matrix delete_row(struct matrix m, unsigned int n)
{
    if(n+1>m.rows)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return create_matrix(0,0);
    }

    unsigned int i,j,k;
    struct matrix c=create_matrix(m.rows-1,m.columns);
    for (i = 0, j = 0; i < m.rows; i++)
        if(i!=n)
        {
            for (k = 0; k < m.columns; k++)
                c.mat[j][k]=m.mat[i][k];
            j++;
        }
    return c;
}

/* This function returns a matrix which is the
 * original matrix without the n-1 column
 * Note that the column deleted is n-1 not n
 * returns a 0x0 matrix if there isn't that
 * column in the matrix                            */
struct matrix delete_column(struct matrix m, unsigned int n)
{
    if(n+1>m.columns)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return create_matrix(0,0);
    }

    unsigned int i,j,k;
    struct matrix c=create_matrix(m.rows,m.columns-1);
    for (i = 0; i < m.rows; i++)
        for (k = 0, j = 0; k < m.columns; k++)
            if(k!=n)
            {
                c.mat[i][j]=m.mat[i][k];
                j++;
            }
    return c;
}

/* This function changes two rows */
void change_rows(struct matrix m, unsigned int row1, unsigned int row2)
{
    if(row1>m.rows||row2>m.rows)
    {
        printf("The matrix isn't big enough\n");
        printf("To have that number of rows\n");
        return;
    }

    float *aux;
    aux=m.mat[row1];
    m.mat[row1]=m.mat[row2];
    m.mat[row2]=aux;
}

/* This function changes two columns */
void change_columns(struct matrix m, unsigned int column1, unsigned int column2)
{
    if(column1>m.columns||column2>m.columns)
    {
        printf("The matrix isn't big enough\n");
        printf("To have that number of columns\n");
        return;
    }

    unsigned int i;
    float aux;
    for (i = 0; i < m.rows; i++)
    {
        aux=m.mat[i][column1];
        m.mat[i][column1]=m.mat[i][column2];
        m.mat[i][column2]=aux;
    }
}

/* This function returns a matrix with the n-1th row replaced 
 * with the contents of a
 * Note that it doesn't check if a has enough elements or if
 * it is longer than the row size in m, in this case,
 * only the elements of a that fit in the row are used
 * returns a 0x0 matrix if there isn't that row in the matrix */
struct matrix replace_row(struct matrix m, unsigned int n, float * a)
{
    if(n+1>m.rows)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return create_matrix(0,0);
    }

    unsigned int i;
    struct matrix c=copy_matrix(m);
    for (i = 0; i < m.columns; i++)
        c.mat[n][i]=a[i];
    return c;
}

/* This function returns a matrix with the n-1th column replaced 
 * with the contents of a
 * Note that it doesn't check if a has enough elements or if
 * it is longer than the column size in m, in this case,
 * only the elements of a that fit in the column are used
 * returns a 0x0 matrix if there isn't that column in the matrix */
struct matrix replace_column(struct matrix m, unsigned int n, float * a)
{
    if(n+1>m.columns)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that column\n");
        return create_matrix(0,0);
    }

    unsigned int i;
    struct matrix c=copy_matrix(m);
    for (i = 0; i < m.rows; i++)
        c.mat[i][n]=a[i];
    return c;
}

/* This function returns a matrix with the n-1th row replaced 
 * with the contents of a
 * Note that it doesn't check if a has less than num elements
 * if num is less than the row size, the remaining elements
 * are filled with 0s
 * if num is bigger than the row size in m, in this case,
 * only the elements of a that fit in the row are used
 * returns a 0x0 matrix if there isn't that row in the matrix */
struct matrix n_replace_row(struct matrix m, unsigned int n, float * a, unsigned int num)
{
    if(n+1>m.rows)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return create_matrix(0,0);
    }

    unsigned int i;
    struct matrix c=copy_matrix(m);
    for (i = 0; i < num; i++)
        c.mat[n][i]=a[i];
    for ( ; i < m.columns; i++)
        c.mat[n][i]=0;
    return c;
}

/* This function returns a matrix with the n-1th column replaced 
 * with the contents of a
 * Note that it doesn't check if a has less than num elements
 * if num is less than the column size, the remaining elements
 * are filled with 0s
 * if num is bigger than the column size in m, in this case,
 * only the elements of a that fit in the column are used
 * returns a 0x0 matrix if there isn't that column in the matrix */
struct matrix n_replace_column(struct matrix m, unsigned int n, float * a, unsigned int num)
{
    if(n+1>m.columns)
    {
        printf("This matrix isn't big enough\n");
        printf("To have that row\n");
        return create_matrix(0,0);
    }

    unsigned int i;
    struct matrix c=copy_matrix(m);
    for (i = 0; i < num; i++)
        c.mat[i][n]=a[i];
    for ( ; i < m.columns; i++)
        c.mat[i][n]=0;
    return c;
}

/* This function returns a matrix which is the
 * original matrix without the i-1 row and j-1
 * column
 * Note that the row & column deleted are i-1
 * and j-1, not i nor j
 * returns a 0x0 matrix if there isn't that row
 * or column in the matrix                      */
struct matrix minor_matrix(struct matrix m, unsigned int row, unsigned int column)
{
    if(row+1>m.rows||column+1>m.columns)
    {
        printf("Matrix isn't big enough\n");
        printf("to have that element\n");
        return create_matrix(0,0);
    }
    struct matrix c=create_matrix(m.rows-1,m.columns-1);
    unsigned int i,j,k,l;
    for (i = 0, k = 0; i < m.rows; i++)
        if(i!=row)
        {
            for (j = 0, l = 0; j < m.columns; j++)
                if(j!=column)
                {
                    c.mat[k][l]=m.mat[i][j];
                    l++;
                }
            k++;
    }
    return c;
}

/* This function returns the traspose of a matrix */
struct matrix traspose(struct matrix m)
{
    unsigned int i,j;
    struct matrix c=create_matrix(m.columns,m.rows);
    for (i = 0; i < m.rows-1; i++)
        for (j = i+1; j < m.columns; j++)
        {
            c.mat[j][i]=m.mat[i][j];
            c.mat[i][j]=m.mat[j][i];
        }
    return c;
}

/* This function returns the oposite of a matrix */
struct matrix oposite(struct matrix m)
{
    unsigned int i,j;
    struct matrix c=create_matrix(m.columns,m.rows);
    for (i = 0; i < m.rows; i++)
        for (j = 0; j < m.columns; j++)
            c.mat[i][j]=-m.mat[i][j];
    return c;
}

struct matrix gauss_elimination(struct matrix m1, struct matrix m2);
/* This function returns the inverse of a matrix using
 * the gauss elimination algorithm with an identity matrix
 * returns a 0x0 matrix if the given matrix isn't square    */
struct matrix inverse_matrix(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Impossible to find inverse matrix\n");
        printf("Imput matrix not square\n");
        return create_matrix(0,0);
    }

    return gauss_elimination(m,identity_matrix(m.rows));
}

/* This function returns the product of the diagonal of the matrix
 * returns -1 if the matrix isn't square                             */
float multiply_diagonal(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Impossible to multiply the diagonal\n");
        printf("Non square matrix\n");
        return -1;
    }

    unsigned int i;
    float aux=1;
    for (i = 0; i < m.rows; i++)
        aux*=m.mat[i][i];
    return aux;
}

/* This function returns the sum of the diagonal of the matrix
 * returns -1 if the matrix isn't square                        */
float sum_diagonal(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Impossible to sum the diagonal\n");
        printf("Non square matrix\n");
        return -1;
    }

    unsigned int i;
    float aux=0;
    for (i = 0; i < m.rows; i++)
        aux+=m.mat[i][i];
    return aux;
}

/* This function returns the determinant of a matrix using
 * a gauss elimination-like algorithm
 * returns -1 if the given matrix isn't square              */
float determinant(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Impossible to calculate determinant\n");
        printf("Matrix not square\n");
        return -1;
    }

    unsigned int i,j,k;
    float aux;
    float factor=1;
    
    /* We work with a copy of the matrix because we have to
     * change it a lot                                      */
    struct matrix c=copy_matrix(m);

    for (i = 0; i < c.rows-1; i++)
    {
        /* We have to be sure that the pivot we are using isn't 0
         * if so, we search for a row with a pivot different from
         * 0 and use it. We change the content in the changes array
         * so we can unchange them later
         * The factor is because if you change two rows of a matrix
         * its determinant gets multiplied by -1                    */
        if(c.mat[i][i]==0)
            for (j = i+1; j < c.rows && c.mat[i][i]==0; j++)
                if(c.mat[j][i]!=0)
                {
                    change_rows(c,i,j);
                    factor*=-1;
                }

        /* Now, we can do gauss elimination on the following rows
         * of the matrix.
         * Note that we start at i+1 because we only need a triangular
         * matrix with the diagonal untouched                           */
        for (j = i+1; j < c.rows; j++)
        {
            aux=c.mat[j][i]/c.mat[i][i];
            for (k = i+1; k < c.columns; k++)
                c.mat[j][k]-=aux*c.mat[i][k];
        }
    }
    return factor*multiply_diagonal(c);
}

/* This function implements Sarrus rule to calculate determinants
 * of 2x2 and 3x3 matrixes
 * returns -1 if the matrix isn't square, 2x2 or 3x3                */
float sarrus(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Can't calculate determinant\n");
        printf("Input matrix isn't square\n");
        return -1;
    }
    if(m.rows!=2&&m.rows!=3)
    {
        printf("Can't calculate determinant with Sarrus rule\n");
        printf("Input matrix is not 2x2 or 3x3\n");
        return -1;
    }

    if(m.rows==2)
        return m.mat[0][0]*m.mat[1][1]-m.mat[0][1]*m.mat[1][0];
    if(m.rows==3)
    {
        float fac1, fac2, fac3;
        fac1=m.mat[0][0]*(m.mat[1][1]*m.mat[2][2]-m.mat[1][2]*m.mat[2][1]);
        fac2=m.mat[0][1]*(m.mat[1][2]*m.mat[2][0]-m.mat[1][0]*m.mat[2][2]);
        fac3=m.mat[0][2]*(m.mat[1][0]*m.mat[2][1]-m.mat[1][1]*m.mat[2][0]);
        return fac1+fac2+fac3;
    }
}

/* This function calculates the determinant of a matrix using
 * the Laplace expansion
 * returns -1 if the matrix isn't square                        */
float determinant_laplace(struct matrix m)
{
    if(m.rows!=m.columns)
    {
        printf("Can't calculate determinant\n");
        printf("Input matrix isn't square\n");
        return -1;
    }
    if(m.rows==2||m.rows==3)
        return sarrus(m);

    unsigned int i;
    float det=0;
    for (i = 0; i < m.columns; i++)
    {
        if(m.mat[0][i]!=0)
            if(i%2==0)
                det+=m.mat[0][i]*determinant_laplace(minor_matrix(m,0,i));
            else
                det-=m.mat[0][i]*determinant_laplace(minor_matrix(m,0,i));
    }
    return det;
}

/* This function returns the sum of two matrixes
 * returns a 0x0 matrix if they can't be summed */
struct matrix matrix_sum(struct matrix m1, struct matrix m2)
{
    if(m1.rows!=m2.rows||m1.columns!=m2.columns)
    {
        printf("These matrixes doesn't have the same size\n");
        printf("Imposible to sum them.\n");
        return create_matrix(0,0);
    }

    unsigned int i,j;
    struct matrix c=create_matrix(m1.rows,m1.columns);
    for (i = 0; i < m1.rows; i++)
        for (j = 0; j < m1.columns; j++)
            c.mat[i][j]=m1.mat[i][j]+m2.mat[i][j];
    return c;
}

/* This function returns the subtraction of two matrixes
 * returns a 0x0 matrix if they can't be subtracted      */
struct matrix matrix_subtraction(struct matrix m1, struct matrix m2)
{
    if(m1.rows!=m2.rows||m1.columns!=m2.columns)
    {
        printf("These matrixes doesn't have the same size\n");
        printf("Imposible to subtract them.\n");
        return create_matrix(0,0);
    }

    unsigned int i,j;
    struct matrix c=create_matrix(m1.rows,m1.columns);
    for (i = 0; i < m1.rows; i++)
        for (j = 0; j < m1.columns; j++)
            c.mat[i][j]=m1.mat[i][j]-m2.mat[i][j];
    return c;
}

/* This function returns the multiplication of two matrixes
 * returns a 0x0 matrix if they can't be multiplied         */
struct matrix matrix_multiplication(struct matrix m1, struct matrix m2)
{
    if(m1.columns!=m2.rows)
    {
        printf("These matrixes can't be multiplied\n");
        printf("They don't have the right size\n");
        return create_matrix(0,0);
    }

    unsigned int i,j,k;
    struct matrix c=create_matrix(m1.rows,m2.columns);
    for (i = 0; i < m1.rows; i++)
        for (j = 0; j < m2.columns; j++)
            for (k = 0; k < m1.columns; k++)
                c.mat[i][j]+=m1.mat[i][k]*m2.mat[k][j];
    return c;
}

/* This function implements the gauss elimination algorithm
 * in a given matrix and a second matrix with the independient
 * coeficients.
 * Note that you pass a matrix as the second argument, so you
 * can solve several linear equations with the same form at
 * the same time.
 * returns a 0x0 matrix if the matrixes have different number
 * of rows.                                                     */
struct matrix gauss_elimination(struct matrix m,struct matrix n)
{
    if(m.rows!=n.rows)
    {
        printf("Impossible to do Gauss Elimination\n");
        printf("The matrixes are not the right size\n");
        return create_matrix(0,0);
    }

    unsigned int i,j,k;
    float aux;

    /* We work with copies of the matrixes because we have to
     * change them a lot                                        */
    struct matrix c=copy_matrix(m);
    struct matrix b=copy_matrix(n);

    /* If we have to change the position of some rows, we have
     * to have a way to know where they were                    */
    float *changes;
    changes=malloc(c.rows*sizeof(int));
    for (i = 0; i < c.rows; i++)
        changes[i]=i;

    for (i = 0; i < c.columns; i++)
    {
        /* We have to be sure that the pivot we are using isn't 0
         * if so, we search for a row with a pivot different from
         * 0 and use it. We change the content in the changes array
         * so we can unchange them later */
        if(c.mat[i][i]==0)
            for (k = i+1; k < c.rows && c.mat[i][i]==0; k++)
                if(c.mat[k][i]!=0)
                {
                    change_rows(c,i,k);
                    change_rows(b,i,k);
                    changes[i]=k;
                    changes[k]=i;
                }

        /* Now that we are sure that the pivot isn't 0, we can
         * eliminate the numbers of the i column.
         * If j is different from i, that means that j is a row
         * in which we have to eliminate the i,j number.
         * If j is the same as i, we have to divide the row by
         * the i,i number so we have a 1 in the i,i position */
        for (j = 0; j < c.rows; j++)
        {
            if(j!=i)
            {
                aux=c.mat[j][i]/c.mat[i][i];
                for (k = i; k < c.columns; k++)
                    c.mat[j][k]-=aux*c.mat[i][k];
                for (k = 0; k < b.columns; k++)
                    b.mat[j][k]-=aux*b.mat[i][k];
            }
            else
            {
                aux=c.mat[i][i];
                for (k = i; k < c.columns; k++)
                    c.mat[j][k]/=aux;
                for (k = 0; k < b.columns; k++)
                    b.mat[j][k]/=aux;
            }
        }
    }

    /* We have to unmake all the changes we have made */
    for (i = 0; i < c.rows; i++)
        if(changes[i]!=i)
            for (j = 0; j < c.rows; j++)
                if(changes[j]==i)
                {
                    change_rows(b,i,j);
                    break;
                }
    return b;
}
