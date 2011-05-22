/* a */
#ifndef _MATRIX_EXTRA_H
#define _MATRIX_EXTRA_H

struct matrix row_matrix_from_vector(struct vector v);
struct matrix column_matrix_from_vector(struct vector v);
struct vector vector_from_matrix(struct matrix m);
struct matrix matrix_product(struct vector v1, struct vector v2);
struct vector multiply_matrix_from_left(struct matrix m, struct vector v);
struct vector multiply_matrix_from_right(struct matrix m, struct vector v);
double mutiply_matrix_from_both_sides(struct matrix m, struct vector v1, struct vector v2);
double bilinear_product(struct matrix m, struct vector v);

#endif
