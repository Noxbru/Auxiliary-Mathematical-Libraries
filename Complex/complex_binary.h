#ifndef _COMPLEX_BINARY_H
#define _COMPLEX_BINARY_H

struct complex_binary;

/* Functions to create complex numbers in binary form */
struct complex_binary create_complex_binary(double a, double b);
struct complex_binary get_complex(void);
struct complex_binary copy_complex_binary(struct complex_binary z);

/* Functions to print complex numbers in binary form */
void print_complex(struct complex_binary z);

/* Functions to get info from complex numbers in binary form */
double real_part_binary(struct complex_binary z);
double imaginary_part_binary(struct complex_binary z);
double module_binary(struct complex_binary z);
double argument_binary(struct complex_binary z);

struct complex_binary conjugate_binary(struct complex_binary z);
struct complex_binary reciprocal_binary(struct complex_binary z);
struct complex_polar binary_to_polar(struct complex_binary z);

/* Functions to do operations with two complex numbers
 * in binary form */
struct complex_binary multiply_complex_binary_by(struct complex_binary z, double n);
struct complex_binary sum_complex_binary(struct complex_binary z1, struct complex_binary z2);
struct complex_binary subtraction_complex_binary(struct complex_binary z1, struct complex_binary z2);
struct complex_binary multiplication_complex_binary(struct complex_binary z1, struct complex_binary z2);
struct complex_binary division_complex_binary(struct complex_binary z1, struct complex_binary z2);

#endif
