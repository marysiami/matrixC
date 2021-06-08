#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int N;
int K;
double** matrix1;
double** matrix2;
double** result_matrix_naive;
double** result_matrix_blocks;

void prepare_matrixs(){
    matrix1 = malloc(sizeof(int*) * N);
    matrix2 = malloc(sizeof(int*) * N);
    result_matrix_naive = malloc(sizeof(int*) * N);
    result_matrix_blocks = malloc(sizeof(int*) * N);

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

                result_matrix_naive[i][j] = 0;
                result_matrix_blocks[i][j] = 0;
        }
    }  
}

double** multiply_two_matrix_naive() {
  int i, j, k;
    //mnożenie macierzy
    for(i = 0; i <N; ++i){
        for(j = 0; j < N; ++j){
           for(k = 0; k < N; ++k)
            {
                result_matrix_naive[i][j] += matrix1[i][k] * matrix2[k][j];
            } 
        }
    }
        
    return result_matrix_naive;          
}


double** multiply_two_matrix_block(){

    int temp;
//https://stackoverflow.com/questions/16115770/block-matrix-multiplication
    for(int jj = 0; jj < N; jj += K){
            for(int kk = 0; kk < N; kk += K){
                    for(int i = 0; i < N; i++){
                            for(int j = jj; j< ((jj + K) > N ? N:(jj + K)); j++){
                                    temp = 0;
                                    for(int k = kk; k < ((kk + K) > N ? N:(kk + K)); k++){
                                            temp += matrix1[i][k] * matrix2[k][j]; // a moze  temp += b[i][k]*a[j][k]; ???
                                    }
                                    result_matrix_blocks[i][j] += temp;
                            }
                    }
            }
    }

    return result_matrix_blocks;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    clock_t start_naive, end_naive, start_block, end_block;
    double total_time_naive, total_time_block;

    // Rozmiar bloku K (a także N) powinien być parametrem przekazywanym programowi z wiersza polecenia.  
    int N = atoi(argv[1]);  
    int K = atoi(argv[2]);

    prepare_matrixs();

    start_naive = clock(); 
    double** result_naive = multiply_two_matrix_naive();
    end_naive= clock();

    start_block = clock();
    double** result_blocks = multiply_two_matrix_block();
    end_block = clock();

    int flops = 2 * N^3;

    total_time_naive = ((double)(end_naive-start_naive))/CLOCKS_PER_SEC;
    total_time_block = ((double)(end_block-start_block))/CLOCKS_PER_SEC;

    printf("Flops: %f\n", flops);  
    printf("Total time NAIVE: %f\n", total_time_naive);  
    printf("GFLOP/s NAIVE: %f\n", flops/total_time_naive);  
    printf("Total time BLOCK: %f\n", total_time_block); 
    printf("GFLOP/s BLOCK: %f\n", flops/total_time_block); 

    return 0;
}