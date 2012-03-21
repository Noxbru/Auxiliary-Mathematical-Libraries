#include <stdio.h>
#include <math.h>
#include "integration.h"

int main(int argc, const char *argv[])
{
    unsigned int i;
    unsigned int number=11;
    double values[number];

    for(i = 0; i < number; i++)
        values[i]=1/(1+(double)i*i/(100));

    printf("Calculation of Pi with 11 points\n");
    printf(" integrating from 0 to 1 4/(1+x²)\n");
    printf("\n");
    printf("Trapezoidal: %.10g\n",4*integration_trapezoidal(values,0,1,number));
    printf("Simpson:     %.10g\n",4*integration_simpson(values,0,1,number));
    printf("Boole:       %.10g\n",4*integration_boole(values,0,1,number));
    printf("M_PI:        %.10g\n",M_PI);

    return 0;
}
