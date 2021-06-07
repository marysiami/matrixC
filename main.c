#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int N;

double** multiply_two_matrix() {

    double** matrix1 = malloc(sizeof(int*) * N);
    double** matrix2 = malloc(sizeof(int*) * N);
    double** result_matrix = malloc(sizeof(int*) * N);

    srand(time(NULL));   
    double r1,r2; 
    
    //wypełnienie tablic liczbami losowymi a  tablicy wynikowej zerami
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {

                r1 = (double)rand();
                r2 = (double)rand();

                matrix1[i][j] = r1;
                matrix1[i][j] = r2;

                result_matrix[i][j] = 0;
        }
    }  

    //mnożenie macierzy
    for(i = 0; i <N; ++i){
        for(j = 0; j < N; ++j){
           for(k = 0; k < N; ++k)
            {
                result_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            } 
        }
    }
        
    return result_matrix;          
}

int main(int argc, char** argv) {
    srand(time(NULL));

    // Rozmiar bloku K (a także N) powinien być parametrem przekazywanym programowi z wiersza polecenia.  
    int N = atoi(argv[1]);  
    int K = atoi(argv[2]);

    double** result_matrix = multiply_two_matrix();

  

    // clock_t start, end;
    // double total_time;

    // start = clock();   
    // end = clock();
    // total_time = ((double)(end-start))/CLOCKS_PER_SEC;
    // printf("Total time: %f\n", total_time);  
    return 0;
}