#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int N1;
int N2;

void multiply_two_matrix() {

    int** matrix1 = malloc(sizeof(int*) * N1);
    int** matrix2 = malloc(sizeof(int*) * N2);

    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (i == j || i == size - j - 1) {
                board[i][j] = 1;
            }
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));

    // Rozmiar bloku K (a także N) powinien być parametrem przekazywanym programowi z wiersza polecenia. 
 
    int N1 = atoi(argv[1]);
    int N2 = atoi(argv[2]);

    multiply_two_matrix();

    int K_size = atoi(argv[3]);

    // clock_t start, end;
    // double total_time;

    // start = clock();   
    // end = clock();
    // total_time = ((double)(end-start))/CLOCKS_PER_SEC;
    // printf("Total time: %f\n", total_time);  
    return 0;
}