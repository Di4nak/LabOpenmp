#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100 

int main() {
    int array[SIZE]; //Se declara el array
    int max_val = 0, //Se incializa la variable de valor max
    min_val = 10000;  // Se incializa la variable de valor min
    int sum = 0; // Acumula la suma de los elmentos
    double avg_val = 0.0; //Guarda el promedio

    // Inicializamos el array con números aleatorios entre 0 y 9999
    //omp parallel for para que cada hilo se encargue de inicializar un elemento del array
    #pragma omp parallel for 
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;  // Números aleatorios entre 0 y 9999
    }

    // Muestra el contenido del array
    printf("[ ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");

    // Encontrar el valor máximo
    // reduction(max:max_val) asegura que los hilos puedan comparar los valores de forma paralela
    // y guarda el valor máximo en max_val
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < SIZE; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    // Encontrar el valor mínimo
    // reduction(min:min_val) asegura que los hilos puedan comparar los valores de forma paralela
    // y guarda el valor máximo en min_val
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < SIZE; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
    }

    // Calcular la suma y luego el promedio
    // reduction(+:sum) asegura que los hilos sumen los valores en paralelo
    // El resultado se almacene en sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }
    avg_val = (double)sum / SIZE;

    printf("Max value: %d\n", max_val);
    printf("Min value: %d\n", min_val);
    printf("Average value: %.2f\n", avg_val);

    return 0;
}
