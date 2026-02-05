#include <stdio.h>

double toKm(double meter);
double toCel(double ferh);

int main(int argc, char **argv) {
    
    double input = 4500; 
    double temp = 35; 
    printf("%f Length in Kilometer is: %f \n", input,  toKm(input));
        printf("%f tempreture in celciliuse is: %f \n", temp,  toCel(temp));

    return 0;
}

double toCel(double ferh){
    return (ferh - 32)*5/9;    
}
double toKm(double meter){
    return meter/1000;
}