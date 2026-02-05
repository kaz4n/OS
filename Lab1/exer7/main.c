#include <stdio.h>

int main() {
    int n;
    float sum = 0.0;

    printf("Enter an integer n (1 < n < 10): ");
    scanf("%d", &n);

    if (n <= 1 || n >= 10) {
        printf("Error: n must be between 2 and 9.\n");
        return 1;
    }

    float numbers[n]; 
    printf("Enter %d numbers:\n", n);

    for (int i = 0; i < n; i++) {
        printf("Value %d: ", i + 1);
        scanf("%f", &numbers[i]);
        sum += numbers[i]; // Add each input to the total sum
    }

    float average = sum / n;
    printf("\nThe average is: %.2f\n", average);

    return 0;
}
