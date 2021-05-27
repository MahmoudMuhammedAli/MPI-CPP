#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <mpi.h>
#include <array>

void fill(int **mat, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            mat[i][j] = j + 1;
        }
    }
}
using namespace std;
int main(int argc, char *argv[])
{
    int w, h;
    int rank, size;
    MPI_Status status;
    int *mat1[w];
    int *mat2[w];
    int *mat3[w];
    int sum[w];
    // std::vector<std::array<int, h>> matrix;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        cout << "Master node is running" << std::endl;
        fstream inOutCredit;
        inOutCredit.open("./mat.txt", std::ios::in | std::ios::out);
        if (!inOutCredit /*||inOutCredit.eof()*/)
        {
            inOutCredit.open("../credit.dat", ios::out | ios::binary);

            if (!inOutCredit)
            {
                cerr << "inOutCredit File could not be opened." << endl;
                exit(EXIT_FAILURE);
            }
            std::cout << "enter the width" << std::endl;
            cin >> w;
            std::cout << "enter the height" << std::endl;
            cin >> h;
            inOutCredit << w << h;

            inOutCredit.close();
        }
        inOutCredit >> w >> h;

        for (int i = 0; i < w; i++)
        {
            mat1[i] = (int *)malloc(h * sizeof(int));
        }

        for (int i = 0; i < w; i++)
        {
            mat2[i] = (int *)malloc(h * sizeof(int));
        }
        for (int i = 0; i < w; i++)
        {
            mat3[i] = (int *)malloc(h * sizeof(int));
        }

        fill(mat1, w, h);
        fill(mat2, w, h);
        for (int i = 1; i < w; i++)
        {
            MPI_Send(&mat1[i][0], h, MPI_INT, i, 17, MPI_COMM_WORLD);
            MPI_Send(&mat2[i][0], h, MPI_INT, i, 18, MPI_COMM_WORLD);
        }
        for (int j = 0; j < h; j++)
            mat3[0][j] = mat1[0][j] + mat2[0][j];

        // matrix.push_back( sum );
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&mat3[i][0], h, MPI_INT, i, 17, MPI_COMM_WORLD, &status);
            // matrix.push_back( { c } );
            for (int j = 0; j < h; j++)
            {
                std::cout << mat3[i][j] << std::endl;
            }
        }
        // for (int i = 0; i < w; i++)
        // {
        //     for (int j = 0; j < h; j++)
        //     {
        //         std::cout << " " << matrix[i][j] << std::endl;
        //     }
        // }
    }
    else
    {
        cout << "you're in node:" << rank << endl;
        int *mat1[w];
        for (int i = 0; i < w; i++)
        {
            mat1[i] = (int *)malloc(h * sizeof(int));
        }
        int *mat2[w];
        for (int i = 0; i < w; i++)
        {
            mat2[i] = (int *)malloc(h * sizeof(int));
        }
        int *mat3[w];
        for (int i = 0; i < w; i++)
        {
            mat3[i] = (int *)malloc(h * sizeof(int));
        }
        MPI_Recv(mat1, w, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
        MPI_Recv(mat2, w, MPI_INT, 0, 18, MPI_COMM_WORLD, &status);
        for (int i = 0; i < w; i++)
        {
            mat3[0][i] = mat1[0][i] + mat2[0][i];
        }
        MPI_Send(mat3, w, MPI_INT, 0, 17, MPI_COMM_WORLD);
    }
    return 0;
}
