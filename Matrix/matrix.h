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
#ifndef _MATRIX_H
#define _MATRIX_H

struct matrix;

/* Functions to create matrixes */
struct matrix create_matrix(unsigned int m, unsigned int n);
struct matrix get_matrix();
struct matrix matrix_from_string(char *c, unsigned int m, unsigned int n);
struct matrix matrix_from_file(char *c, unsigned int m, unsigned int n);
struct matrix copy_matrix(struct matrix m);
struct matrix identity_matrix(unsigned int n);

/* Functions to print matrixes */
void print_matrix(struct matrix m);
void print_matrix_to_file(char *c, struct matrix m, char over=1);

/* Functions to destroy matrices */
void free_matrix(struct matrix *m);

/* Functions to check types of matrixes */
int is_symmetric(struct matrix m);
int is_antisymmetric(struct matrix m);
int is_orthogonal(struct matrix m);
int compare_matrix(struct matrix m1, struct matrix m2);

/* Functions to do operations on one single matrix */
void fill_matrix_with(struct matrix m, double n);
struct matrix multiply_matrix_by(struct matrix m, double n);
struct matrix pow_matrix(struct matrix m, unsigned int n);

double * get_row(struct matrix m, unsigned int row);
double * get_column(struct matrix m, unsigned int column);
struct matrix delete_row(struct matrix m, unsigned int n);
struct matrix delete_column(struct matrix m, unsigned int n);
void change_rows(struct matrix m, unsigned int row1, unsigned int row2);
void change_columns(struct matrix m, unsigned int column1, unsigned int column2);
struct matrix replace_row(struct matrix m, unsigned int n, double * a);
struct matrix replace_column(struct matrix m, unsigned int n, double * a);
struct matrix n_replace_row(struct matrix m, unsigned int n, double * a, unsigned int num);
struct matrix n_replace_column(struct matrix m, unsigned int n, double * a, unsigned int num);

struct matrix minor_matrix(struct matrix m, unsigned int i, unsigned int j);

struct matrix traspose(struct matrix m);
struct matrix oposite(struct matrix m);
struct matrix inverse_matrix(struct matrix m);

double multiply_diagonal(struct matrix m);
double sum_diagonal(struct matrix m);
double determinant(struct matrix m);
double sarrus(struct matrix m);
double determinant_laplace(struct matrix m);

/* Functions to do operations with two matrixes */
struct matrix matrix_sum(struct matrix m1, struct matrix m2);
struct matrix matrix_subtraction(struct matrix m1, struct matrix m2);
struct matrix matrix_multiplication(struct matrix m1, struct matrix m2);

struct matrix gauss_elimination(struct matrix m, struct matrix n);

#endif
