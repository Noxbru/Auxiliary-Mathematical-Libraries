/* This is a library to make some statistic in C
 * written by Bruno Jiménez
 * under the Catware licence && GPL licence
 * More info of the Catware licence can be
 * found here: http://lists.debian.org/debian-devel/1999/01/msg01921.html
 * but it says that if you find this code useful
 * you should pay for it petting some cats
 * Any request or bug or anything of the code
 * please, contact brunojimen(at)gmail(dot)com
 */

/* This function returns the mean of an
 * array of n data  <a>                 */
/* Caution, as it may overflow or loss
 * precision with high values           */
double mean(double *a, unsigned int n)
{
    double mean=0;
    unsigned int i;
    for(i = 0; i < n; i++)
        mean+=a[i];
    return mean/n;
}

/* This function returns the mean of the
 * squares of an array of n data <a²>   */
double mean2(double *a, unsigned int n)
{
    double mean2=0;
    unsigned int i;
    for(i = 0; i < n; i++)
        mean2+=a[i]*a[i];
    return mean2/n;
}

/* This function returns the variance of an
 * array of n data  <a²>-<a>²               */
/* This is a very naive function and can lead
 * to numerous loss of precision, for more
 * information on algorithms please look:
 * http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance */
double variance(double *a, unsigned int n)
{
    double mean=0;
    double mean2=0;
    unsigned int i;
    for(i = 0; i < n; i++)
    {
        mean+=a[i];
        mean2+=a[i]*a[i];
    }
    mean/=n;
    mean2/=n;
    return mean2-mean*mean;
}

/* This function is a safer version of the
 * variance function based on the Algorithm II
 * of wikipedia (sum of (a_i-<a>)²)             */
double variance_safe(double *a, unsigned int n)
{
    double mean_temp=mean(a,n);
    double variance=0;
    unsigned int i;
    for(i = 0; i < n; i++)
        variance+=(a[i]-mean_temp)*(a[i]-mean_temp);
    return variance/n;
}

/* This function returns the covariance of
 * two arrays of n data  <ab>-<a><b>        */
double covariance(double *a, double *b, unsigned int n)
{
    double mean_a=0;
    double mean_b=0;
    double mean_ab=0;
    unsigned int i;
    for(i = 0; i < n; i++)
    {
        mean_a+=a[i];
        mean_b+=b[i];
        mean_ab+=a[i]*b[i];
    }
    mean_a/=n;
    mean_b/=n;
    mean_ab/=n;
    return mean_ab-mean_a*mean_b;
}

/* This function is a safer version of the
 * covariance function based on the
 * of wikipedia (sum of (a_i-<a>)*(b_i-<b>) */
double covariance_safe(double *a, double *b, unsigned int n)
{
    double mean_a=mean(a,n);
    double mean_b=mean(b,n);
    double covariance=0;
    unsigned int i;
    for(i = 0; i < n; i++)
        covariance+=(a[i]-mean_a)*(b[i]-mean_b);
    return covariance/n;
}

/* This function fits two sets of
 * data to a straight line a*x+b
 * using that
 * a = <xy>-<x><y>/<x²>-<x>²
 * b = <y>-a<x>                     */
/* Warning, this may is an unsafe
 * function as it uses the unsafe
 * version of the variance and
 * covariance                       */
void fit_linear(double *x, double *y, unsigned int n, double *a, double *b)
{
    *a=covariance(x,y,n)/variance(x,n);
    *b=mean(y,n)-*a*mean(x,n);
}
/* ALTERNATIVE CODE (maybe a bit faster)
{
    double mean_x=0, mean_y=0;
    double mean_xx=0, mean_xy=0;
    unsigned int i;

    for(i = 0; i < n; i++)
    {
        mean_x+=x[i];
        mean_y+=y[i];
        mean_xx+=x[i]*x[i];
        mean_xy+=x[i]*y[i];
    }

    *a=(mean_xy-mean_x*mean_y/n)/(mean_xx-mean_x*mean_x/n);
    *b=(mean_y-*a*mean_x)/n;
}
*/

/* This function is the safer version of
 * the fit_linear function              */
void fit_linear_safe(double *x, double *y, unsigned int n, double *a, double *b)
/*{
    *a=covariance_safe(x,y,n)/variance_safe(x,n);
    *b=mean(y,n)-*a*mean(x,n);
}*/
/* ALTERNATIVE CODE (maybe a bit faster) */
{
    double mean_x=0, mean_y=0;
    double var_x=0, covar_xy=0;
    unsigned int i;

    for(i = 0; i < n; i++)
    {
        mean_x+=x[i];
        mean_y+=y[i];
    }
    mean_x/=n;
    mean_y/=n;

    for(i = 0; i < n; i++)
    {
        var_x+=(x[i]-mean_x)*(x[i]-mean_x);
        covar_xy+=(x[i]-mean_x)*(y[i]-mean_y);
    }
    // Technically var_x and covar_xy aren't the variance
    // or the covariance of x and xy as they should be
    // divided by n, but as it will be cancelled we avoid
    // that operation

    *a=covar_xy/var_x;
    *b=mean_y-*a*mean_x;
}
