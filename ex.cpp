#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, n,  size = 100, accum = 0, stat;
    int *arr;
    int total = 0;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        arr = new int[size] ;
        for (int i = 0; i <size; i++)
        {
            arr[i] = i+1;
        }
        for (int i = 1; i <= n - 1; i++)
        {
            stat = i * size / n;
            MPI_Send(&arr[stat],size/n, MPI_INT, i, 17, MPI_COMM_WORLD);
        }
        for (int i = 0; i < size / n; i++)
        {
            total += arr[i];
        }
       // printf("total is %d", total);

        for (int i = 1; i <= n - 1; i++)
        {
            MPI_Recv(&accum, 1, MPI_INT, i, 17, MPI_COMM_WORLD, &status);
            total += accum;
        }
        printf("total is %d\n", total);
    }
    else
    {
        int j=rank;
        int* a = new int[size / n];
        MPI_Recv(a, size / n, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
        printf("jo");
        for (int i = 0; i <size / n; i++)
        {
            accum += a[i];
        }
        printf("total is %d", accum);

        MPI_Send(&accum, 1,MPI_INT, 0, 17, MPI_COMM_WORLD);

       
    }
    MPI_Finalize();
    return 0 ;
}