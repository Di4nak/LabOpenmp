#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel num_threads(10)
    {
        int thread_num = omp_get_thread_num();
        if (thread_num % 2 == 0) {
            printf("Hello from even thread %d\n", thread_num);
        } else {
            printf("Hello from odd thread %d\n", thread_num);
        }
    }
    return 0;
}
