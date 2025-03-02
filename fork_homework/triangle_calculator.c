#include <stdio.h>
#include <stdlib.h>

int main() {
    double base = 5.0, height = 10.0;
    double area = 0.5 * base * height;
    printf("Child Process: Area = %.2f\n", area);
    return 0;
}