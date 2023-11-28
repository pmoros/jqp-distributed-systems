#include <stdio.h>

#define MAX 999999

__device__
double minVal(double a, double b) {
    return (a < b) ? a : b;
}

__device__
double fun(int i, int mask, int n, double* dist, double* memo, int* efficientRoute, int* efficientRouteIndex)
{
    if (mask == ((1 << i) | 15)) {        
        efficientRoute[*efficientRouteIndex] = i;
        *efficientRouteIndex = (*efficientRouteIndex + 1) % n;                                                         
        return dist[1 * n + i];    
    }
        
    // memoization
    if (memo[i * (1 << n) + mask] != 0) {
        efficientRoute[*efficientRouteIndex] = i;
        *efficientRouteIndex = (*efficientRouteIndex + 1) % n;                                                         
        return memo[i * (1 << n) + mask];
    }
 
    double res = MAX; // result of this sub-problem
 
    for (int j = 0; j < n; j++)
        if ((mask & (1 << j)) && j != i && j != 1)        
            res = minVal(res, fun(j, mask & (~(1 << i)), n, dist, memo, efficientRoute, efficientRouteIndex)
                                    + dist[i * n + j]);            
            
    return memo[i * (1 << n) + mask] = res;
}

__global__ void kernel(int numStops, int mask, double *dist, double *memo, int *efficientRoute, int *efficientRouteIndex, double *ans)
{    

    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;



    for (int i = index; i < numStops; i += stride){
        *ans = minVal(*ans, fun(i, (1 << (numStops + 1)) - 1, numStops, dist, memo, efficientRoute, efficientRouteIndex) + dist[i * numStops + 0]);
    }        
}

extern "C" void kernel_wrapper(int numStops, int mask, double **dist, double **memo, int *efficientRoute)
{
    int *efficientRouteCuda, *efficientRouteIndex;
    double *distCuda, *memoCuda, *ans;

    cudaMalloc((void **)&ans, sizeof(double));    
    cudaMalloc((void **)&efficientRouteIndex, sizeof(int));
    cudaMalloc((void **)&distCuda, numStops * numStops * sizeof(double));
    cudaMalloc((void **)&memoCuda, numStops * (1 << numStops) * sizeof(double));
    cudaMalloc((void **)&efficientRouteCuda, numStops * sizeof(int));

    int blockSize = 256;
    int numBlocks = 880;

    
    cudaMemcpy(distCuda, dist, numStops * numStops * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(memoCuda, memo, numStops * (1 << numStops) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(efficientRouteCuda, efficientRoute, numStops * sizeof(int), cudaMemcpyHostToDevice);    

    kernel<<<numBlocks, blockSize>>>(numStops, mask, distCuda, memoCuda, efficientRoute, efficientRouteIndex, ans);

    cudaMemcpy(efficientRouteCuda, efficientRoute, numStops * sizeof(int), cudaMemcpyDeviceToHost);    

    cudaFree(distCuda);
    cudaFree(memoCuda);
    cudaFree(efficientRouteIndex);
    cudaFree(efficientRouteCuda);
}