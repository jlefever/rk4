#include <stdio.h>

double p_prime(double p) {
    return 10.0 * p * (1.0 - p);
}

double next_p(double p, double step_size) {
    double k_1 = p_prime(p);
    double k_2 = p_prime(p + (step_size / 2.0) * k_1);
    double k_3 = p_prime(p + (step_size / 2.0) * k_2);
    double k_4 = p_prime(p + (step_size * k_3));

    return p + (step_size / 6.0) * (k_1 + 2 * k_2 + 2 * k_3 + k_4);
}

int main() {
    double step_size = 0.35;
    double p_0 = 0.1;

    printf("%f\n", p_0);
    double p = next_p(p_0, step_size);

    for (int i = 0; i < 59; i++) {
        printf("%f\n", p);
        p = next_p(p, step_size);
    }
}