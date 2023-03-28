#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define N 1000

int32_t a[N][N]={{0}};
int32_t b[N][N]={{0}};
int32_t c[N][N]={{0}};




int main(){
   

    //hadmard product with first implementation

    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j< N; ++j){
            c[i][j] = a[i][j] * b[i][j];
        }
    }

   
    return EXIT_SUCCESS;
    


}