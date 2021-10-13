#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void addArray(int *a, int *b, int*c, int length)
{
    int tid = blockIdx.x;
    if(tid < length)
        c[tid] = a[tid] + b[tid];


}
void debug(int * array, int length)
{
    int i;
    for( i = 0; i < length; i++)
    {
        printf("%2d: %6d  ", i, array[i]);
    }
    printf("\n");
    return;
}

void printArray(int * array, int length)
{
    int i;
    for( i = 0; i < length; i++)
    {
        printf("%d: %6d\n", i, array[i]);
    }
    return;
}

void generateArray(int **array, int length)
{
    int i;
    *array = (int*)malloc(sizeof(int) * length);
    memset ((void *) *array, 0, sizeof(int) * length);   
    printf("I got here\n");
    for(i = 0; i < length; i++)
    {
        (*array)[i] = rand() % 1000;
    }
    printf("I filled it up\n");
   // debug(*array, length);
    return;
}


int main(int argc, char * argv[])
{
    int *sum; // host sum
    int *dev_sum; // device sum
    int length;
    int *array;
    int i;
    int *array2;
    int *dev_array;
    int *dev_array2;


    srand(time(0));

    if(argc != 2)
    {
        std::cout << "usage:   ./addArray.elf <length of random array>\n";
        exit(0);
    }
    length = atoi(argv[1]);
    if(length > 65535)
    {
        std::cout << "please pick an array length less than 65535\n";
        exit(0);
    }

    if(length == 0)
    {
        std::cout<< "please specify a length > 0\n";
        exit(0);
    }
    cudaMalloc( (void**)&dev_sum, sizeof(int) * length );
    cudaMalloc( (void**)&dev_array, sizeof(int) * length );
    cudaMalloc( (void**)&dev_array2, sizeof(int) * length );
    sum = (int*)malloc(sizeof(int) * length);
    memset((void*)sum, 0, sizeof(int) * length);
    
    generateArray(&array, length);
    generateArray(&array2, length);
    //debug(array, length);
    //debug(array2, length);
    cudaMemcpy (dev_array, array, length * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy (dev_array2, array2, length * sizeof(int), cudaMemcpyHostToDevice);

    addArray<<<length,1>>>( dev_array, dev_array2, dev_sum, length);

    cudaMemcpy(sum, dev_sum, length * sizeof(int), cudaMemcpyDeviceToHost);

    for(i = 0; i < length; i++)
        printf("%5d: %3d + %3d = %4d\n", i, array[i], array2[i], sum[i]);

    cudaFree(dev_sum);
    cudaFree(dev_array);
    cudaFree(dev_array2);
    



    
    return 0;
}
    


    


