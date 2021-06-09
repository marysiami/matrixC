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

double drand (double low, double high )
{
    return ((double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}

void prepare_matrixs(){

    printf("Jestem w prepare_matrixs \n");

    matrix1 = malloc(sizeof(int*) * N);
    matrix2 = malloc(sizeof(int*) * N);
    result_matrix_naive = malloc(sizeof(int*) * N);
    result_matrix_blocks = malloc(sizeof(int*) * N);

    srand(time(NULL));   
    double r1,r2; 
    
    //wypełnienie tablic liczbami losowymi a  tablicy wynikowej zerami
    int i, j, k;
   // printf("N: %d",N);
    for (i = 0; i < N; i++) {
        matrix1[i] = malloc(sizeof(int*) * N);
        matrix2[i] = malloc(sizeof(int*) * N);
        result_matrix_naive[i] = malloc(sizeof(int*) * N);
        result_matrix_blocks[i] = malloc(sizeof(int*) * N);

        for (j = 0; j < N; j++) {

            r1 = drand(0, 100);
            r2 = drand(0, 100);
            matrix1[i][j] = r1;
            matrix2[i][j] = r2;
            
            printf("matrix1 [%d][%d]: %f \n ", i,j,matrix1[i][j]);
            printf("matrix2 [%d][%d]: %f \n ", i,j,matrix2[i][j]);

            result_matrix_naive[i][j] = 0;
            result_matrix_blocks[i][j] = 0;

            printf("result_matrix_naive [%d][%d]: %f \n ", i,j,result_matrix_naive[i][j]);
            printf("result_matrix_blocks[%d][%d]: %f \n ", i,j,result_matrix_blocks[i][j]);

        }
    }  

}


double** multiply_two_matrix_naive() {
  int i, j, k;
      printf("Jestem w multiply_two_matrix_naive \n");
    //mnożenie macierzy
    for(i = 0; i <N; ++i){
        for(j = 0; j < N; ++j){
           for(k = 0; k < N; ++k)
            {
                result_matrix_naive[i][j] += matrix1[i][k] * matrix2[k][j];
                 printf("result: %f",result_matrix_naive[i][j]);
            } 
        }
    }
        
    return result_matrix_naive;          
}


double** multiply_two_matrix_block(){
 printf("Jestem w multiply_two_matrix_block \n");
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

//http://aragorn.pb.bialystok.pl/~wkwedlo/PC9.pdf str 16
//http://www.cmmsigma.eu/labs/parallel_comp/openmp_tutorial/step_02.pl.html
//http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
//http://www.inf.ufsc.br/~bosco.sobral/ensino/ine5645/OpenMP_Dynamic_Scheduling.pdf

void schedule_directive(){

    int chunk_size= 4;
    int THREADS = 4;

     //#pragma omp for schedule(static, chunk_size)
     #pragma omp parallel for schedule(dynamic) num_threads(THREADS)
     {
        #pragma omp for
        for (int i = 0; i < 10; i++) {
            int id = 1;
            printf("Iteracja %d wykonana przez watek nr. %d.\n", i, id);
        }
     }
    

}

int main(int argc, char** argv) {
    srand(time(NULL));

    clock_t start_naive, end_naive, start_block, end_block;
    double total_time_naive, total_time_block;

    // Rozmiar bloku K (a także N) powinien być parametrem przekazywanym programowi z wiersza polecenia.  
     N = 10;//atoi(argv[1]);  
     K = 2;//atoi(argv[2]);
 
    prepare_matrixs();

    start_naive = clock(); 
    printf("start_naive: %f\n", start_naive);  
    double** result_naive = multiply_two_matrix_naive();
    end_naive= clock();
    printf("end_naive: %f\n", end_naive);  


    // start_block = clock();
    // printf("start_block: %f\n", start_block); 
    // double** result_blocks = multiply_two_matrix_block();
    // end_block = clock();
    // printf("end_block: %f\n", end_block);

    // int flops = 2 * N^3;

    // total_time_naive = ((double)(end_naive-start_naive))/CLOCKS_PER_SEC;
    // total_time_block = ((double)(end_block-start_block))/CLOCKS_PER_SEC;

    // printf("Flops: %f\n", flops);  
    // printf("Total time NAIVE: %f\n", total_time_naive);  
    // printf("GFLOP/s NAIVE: %f\n", flops/total_time_naive);  
    // printf("Total time BLOCK: %f\n", total_time_block); 
    // printf("GFLOP/s BLOCK: %f\n", flops/total_time_block); 

    return 0;
}