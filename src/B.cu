#include <stdio.h>

__global__ void kernel(int *a, int *b)
{
    int tx = threadIdx.x;

    switch( tx )
    {
    case 0:
     *a = *a + 10;
     break;
    case 1:
     *b = *b + 3;
     break;
    default:
     *a = *a + 10;
     break;
    }

}

extern "C" void kernel_wrapper(int *a, int *b)
{
    int *d_1, *d_2;

    dim3 threads( 2, 1 );
    dim3 blocks( 1, 1 );    

    cudaMalloc( (void **)&d_1, sizeof(int) );
    cudaMalloc( (void **)&d_2, sizeof(int) );

    cudaMemcpy( d_1, a, sizeof(int), cudaMemcpyHostToDevice );
    cudaMemcpy( d_2, b, sizeof(int), cudaMemcpyHostToDevice );

    kernel<<< blocks, threads >>>( d_1, d_2 );

    cudaMemcpy( a, d_1, sizeof(int), cudaMemcpyDeviceToHost );
    cudaMemcpy( b, d_2, sizeof(int), cudaMemcpyDeviceToHost );

    cudaFree(d_1);
    cudaFree(d_2);
}