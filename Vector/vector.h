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

#ifndef _VECTOR_H
#define _VECTOR_H value

struct vector;

/* Functions to create vectors */
struct vector create_vector(unsigned int n);
struct vector get_vector(void);
struct vector vector_from_string(char *c, unsigned int n);
struct vector vector_from_array(double *a, unsigned int n);
struct vector copy_vector(struct vector v);

/* Functions to print vectors */
void print_vector(struct vector v);
void print_vector_to_file(char *c, struct vector v, char over);

/* Functions to do operations on one single vector */
void fill_vector_with(struct vector v, double n);
struct vector multiply_vector_by(struct vector v, double n);
double module(struct vector v);
struct vector unitary_vector(struct vector v);
double max_component(struct vector v);
double min_component(struct vector v);

/* Functions to check types of vectors */
int compare_vector(struct vector v1, struct vector v2);
int check_orthogonal(struct vector v1, struct vector v2);
int check_parallel(struct vector v1, struct vector v2);

/* Functions to do operations with two vectors */
struct vector vector_sum(struct vector v1, struct vector v2);
struct vector vector_subtraction(struct vector v1, struct vector v2);
double scalar_product(struct vector v1, struct vector v2);
struct vector vectorial_product(struct vector v1, struct vector v2);

#endif
