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
