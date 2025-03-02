#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

double calculateRectangleArea(double length, double width) {
    return length * width;
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        execl("./triangle_calculator", "triangle_calculator", NULL);
        perror("execl failed"); 
        exit(1);
    } 
    else {
        double length = 8.0, width = 4.0;
        double area = calculateRectangleArea(length, width);
        printf("Parent Process: Area = %.2f\n", area);
    }

    return 0;
}
