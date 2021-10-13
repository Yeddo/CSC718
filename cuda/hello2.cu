/* hello.cu */

#include <unistd.h>
#include <stdio.h>

#define N 16
#define CORES 16 

/* this is the GPU kernel function */
__global__ void hello(char* s) {
  /* blockIdx is a struct containing our block id
     if this this is a one-dimensional kernel, then x is the block id
     y and z are also available for 2 or 3 dimensional kernels */

  /* capitalize the string by subtracting 32 from each lowercase letter */
  if ((s[blockIdx.x] >= 'a') && (s[blockIdx.x] <= 'z')) {
    s[blockIdx.x] -= 32;
  }
}

/* the main function begins running on the CPU */
int main( ) {
  /* this is the string data - it is 'hello world', in lower-case */
  char cpu_string[N] = "hello world!";

  /* allocate space on the GPU for the string */
  char* gpu_string;
  cudaMalloc((void**) &gpu_string, N * sizeof(char));

  /* send the character array to the GPU */
  cudaMemcpy(gpu_string, cpu_string, N * sizeof(char), cudaMemcpyHostToDevice);
  
  /* invoke the GPU to run the kernel in parallel
     we specify CORES cores which each run once */
  hello<<<CORES, 1>>>(gpu_string);

  /* copy the string back from the GPU to the CPU */
  cudaMemcpy(cpu_string, gpu_string, N * sizeof(char), cudaMemcpyDeviceToHost);
  
  /* free the memory we allocated on the GPU */
  cudaFree(gpu_string);
  
  /* print the string we got back from the GPU */
  printf("%s\n", cpu_string);

  return 0;
}
