#include <stdlib.h>
#include <stdio.h>

double a = 2.0;
double k = 1.4;

// m = 3
// 3 functions, 3 variables + 1 independant variable (time)
// 1 -> s
// 2 -> i
// 3 -> r
double s_prime(double *vars)
{
    return -vars[1] * a * vars[2];
}

double i_prime(double *vars)
{
    return a * vars[1] * vars[2] - k * vars[2];
}

double r_prime(double *vars)
{
    return k * vars[2];
}

void step(double *vars, double step_size)
{
    double half_h = step_size / 2.0;
    double sixth_h = step_size / 6.0;
    double params[4];

    double a_1 = s_prime(vars);
    double b_1 = i_prime(vars);
    double c_1 = r_prime(vars);

    params[0] = vars[0] + half_h;
    params[1] = vars[1] + half_h * a_1;
    params[2] = vars[2] + half_h * b_1;
    params[3] = vars[3] + half_h * c_1;
    double a_2 = s_prime(params);
    double b_2 = i_prime(params);
    double c_2 = r_prime(params);

    params[0] = vars[0] + half_h; // redundant
    params[1] = vars[1] + half_h * a_2;
    params[2] = vars[2] + half_h * b_2;
    params[3] = vars[3] + half_h * c_2;
    double a_3 = s_prime(params);
    double b_3 = i_prime(params);
    double c_3 = r_prime(params);

    params[0] = vars[0] + step_size;
    params[1] = vars[1] + step_size * a_3;
    params[2] = vars[2] + step_size * b_3;
    params[3] = vars[3] + step_size * c_3;
    double a_4 = s_prime(params);
    double b_4 = i_prime(params);
    double c_4 = r_prime(params);

    vars[0] = vars[0] + step_size; // redundant
    vars[1] = vars[1] + sixth_h * (a_1 + 2 * a_2 + 2 * a_3 + a_4);
    vars[2] = vars[2] + sixth_h * (b_1 + 2 * b_2 + 2 * b_3 + b_4);
    vars[3] = vars[3] + sixth_h * (c_1 + 2 * c_2 + 2 * c_3 + c_4);
}

void print_csv(int n, double *vars)
{
    printf("%d,%f,%f,%f,%f\n", n, vars[0], vars[1], vars[2], vars[3]);
}

void print_display(int n, double *vars)
{
    printf("%d\t%f\t%f\t%f\t%f\n", n, vars[0], vars[1], vars[2], vars[3]);
}

int main()
{
    double step_size = 0.01;
    int n = 0;

    // initial conditions
    double vars[4];
    vars[0] = 0;   // t (time)
    vars[1] = 0.9; // s (susceptible)
    vars[2] = 0.1; // i (infected)
    vars[3] = 0;   // r (recovered)

    do
    {
        print_csv(n, vars);
        step(vars, step_size);
        n++;
    } while (n < 500);
}