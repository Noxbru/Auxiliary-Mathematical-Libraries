#ifndef _COMPLEX_POLAR
#define _COMPLEX_POLAR

struct complex_polar;

/* Functions to create complex numbers in binary form */
struct complex_polar create_complex_polar(double a, double b);
struct complex_polar get_complex(void);
struct complex_polar copy_complex_polar(struct complex_polar z);

/* Functions to print complex numbers in binary form */
void print_complex(struct complex_polar z);

/* Functions to get info from complex numbers in binary form */
double real_part_polar(struct complex_polar z);
double imaginary_part_polar(struct complex_polar z);
double module_polar(struct complex_polar z);
double argument_polar(struct complex_polar z);

struct complex_polar conjugate_polar(struct complex_polar z);
struct complex_polar reciprocal_polar(struct complex_polar z);
struct complex_binary polar_to_binary(struct complex_polar z);

/* Functions to do operations with two complex numbers
 * in binary form */
struct complex_polar sum_complex_polar(struct complex_polar z1, struct complex_polar z2);
struct complex_polar subtraction_complex_polar(struct complex_polar z1, struct complex_polar z2);
struct complex_polar multiplication_complex_polar(struct complex_polar z1, struct complex_polar z2);
struct complex_polar division_complex_polar(struct complex_polar z1, struct complex_polar z2);

#endif
