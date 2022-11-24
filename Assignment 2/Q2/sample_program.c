#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#define SYS_kernel_2d_memcpy 451
int main()
{
    int n_rows = 3;
    int n_column = 4;
    float Matrix_1[n_rows][n_column];
    printf("Matrix is: \n");
    for(int i = 0; i < n_rows; i++){
      for(int j = 0; j < n_column; j++)
      {
        Matrix_1[i][j] = (float)rand()/(float)(RAND_MAX/100);;
        printf("%f    ", i, j, Matrix_1[i][j]);
      }
      printf("\n");
    }
    float Matrix_2[n_rows][n_column];
    int ret= syscall(SYS_kernel_2d_memcpy,Matrix_1,Matrix_2,n_rows,n_column);
    printf("---------------SYS_kernel_2d_memcpy returned %d----------------\n",ret);
    if (ret == 0){
        printf("The Destination Matrix post copying is:\n");
        for(int i = 0; i < n_rows; i++){
            for(int j = 0; j < n_column; j++)
        {
            printf("%f    ", i, j, Matrix_2[i][j]);
        }
        printf("\n");
        } 
    }
    else{
      printf("Since SYS_kernel_2d_memcpy returned %d. Error were encountered during copying of 2-D floating point matrix to another.\n",ret);
    }
  return 0;
}