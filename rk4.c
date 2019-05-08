#include <stdlib.h>
#include <stdio.h>

double a = 2.0;
double k = 1.4;

// m = 3
// 3 functions, 3 variables
double s_prime(double s, double i, double r)
{
    return -s * a * i;
}

double i_prime(double s, double i, double r)
{
    return a * s * i - k * i;
}

double r_prime(double s, double i, double r)
{
    return k * i;
}

double *step(double s, double i, double r, double step_size)
{
    double half_h = step_size / 2.0;
    double sixth_h = step_size / 6.0;

    double s_n = s, i_n = i, r_n = r;

    double a_1 = s_prime(s_n, i_n, r_n);
    double b_1 = i_prime(s_n, i_n, r_n);
    double c_1 = r_prime(s_n, i_n, r_n);

    s_n = s + half_h * a_1;
    i_n = i + half_h * b_1;
    r_n = r + half_h * c_1;
    double a_2 = s_prime(s_n, i_n, r_n);
    double b_2 = i_prime(s_n, i_n, r_n);
    double c_2 = r_prime(s_n, i_n, r_n);

    s_n = s + half_h * a_2;
    i_n = i + half_h * b_2;
    r_n = r + half_h * c_2;
    double a_3 = s_prime(s_n, i_n, r_n);
    double b_3 = i_prime(s_n, i_n, r_n);
    double c_3 = r_prime(s_n, i_n, r_n);

    s_n = s + step_size * a_2;
    i_n = i + step_size * b_2;
    r_n = r + step_size * c_2;
    double a_4 = s_prime(s_n, i_n, r_n);
    double b_4 = i_prime(s_n, i_n, r_n);
    double c_4 = r_prime(s_n, i_n, r_n);

    double *vec = (double *)malloc(sizeof(double) * 3);
    vec[0] = s + sixth_h * (a_1 + 2 * a_2 + 2 * a_3 + a_4);
    vec[1] = i + sixth_h * (b_1 + 2 * b_2 + 2 * b_3 + b_4);
    vec[2] = r + sixth_h * (c_1 + 2 * c_2 + 2 * c_3 + c_4);
    return vec;
}

int main()
{
    double step_size = 0.01;

    double s_0 = 0.9;
    double i_0 = 0.1;
    double r_0 = 0;

    printf("susceptible\tinfected\trecovered\n");
    printf("%f\t%f\t%f\n", s_0, i_0, r_0);
    double *vec = step(s_0, i_0, r_0, step_size);
    double *next_vec;

    for (int i = 0; i < 499; i++)
    {
        printf("%f\t%f\t%f\n", vec[0], vec[1], vec[2]);
        next_vec = step(vec[0], vec[1], vec[2], step_size);
        free(vec);
        vec = next_vec;
    }
}