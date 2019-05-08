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

void step(double *vars, double (*functions[])(double *), int m, double step_size)
{
    int i;
    double half_h = step_size / 2.0;
    double sixth_h = step_size / 6.0;
    double params[m + 1], a[m], b[m], c[m], d[m];

    // A
    for (i = 0; i < m; i++)
    {
        a[i] = functions[i](vars);
    }

    // B
    params[0] = vars[0] + half_h;
    for (i = 0; i < m; i++)
    {
        params[i + 1] = vars[i + 1] + half_h * a[i];
    }
    for (i = 0; i < m; i++)
    {
        b[i] = functions[i](params);
    }

    // C
    params[0] = vars[0] + half_h; // redundant
    for (i = 0; i < m; i++)
    {
        params[i + 1] = vars[i + 1] + half_h * b[i];
    }
    for (i = 0; i < m; i++)
    {
        c[i] = functions[i](params);
    }

    // D
    params[0] = vars[0] + step_size;
    for (i = 0; i < m; i++)
    {
        params[i + 1] = vars[i + 1] + step_size * c[i];
    }
    for (i = 0; i < m; i++)
    {
        d[i] = functions[i](params);
    }

    // Final
    vars[0] = vars[0] + step_size; // redundant
    for (i = 0; i < m; i++)
    {
        vars[i + 1] = vars[i + 1] + sixth_h * (a[i] + 2 * b[i] + 2 * c[i] + d[i]);
    }
}

void print_csv(int n, double *vars, int m)
{
    printf("%d,%f", n, vars[0]);
    for (int i = 0; i < m; i++)
    {
        printf(",%f", vars[i + 1]);
    }
    printf("\n");
}

void print_display(int n, double *vars, int m)
{
    printf("%d\t%f", n, vars[0]);
    for (int i = 0; i < m; i++)
    {
        printf("\t%f", vars[i + 1]);
    }
    printf("\n");
}

int main()
{
    double step_size = 0.01;
    int n = 0;

    int m = 3;

    // initial conditions
    double vars[m + 1];
    vars[0] = 0;   // t (time)
    vars[1] = 0.9; // s (susceptible)
    vars[2] = 0.1; // i (infected)
    vars[3] = 0;   // r (recovered)

    double (*functions[m])(double *);
    functions[0] = &s_prime;
    functions[1] = &i_prime;
    functions[2] = &r_prime;

    do
    {
        print_display(n, vars, m);
        step(vars, functions, m, step_size);
        n++;
    } while (n < 500);
}