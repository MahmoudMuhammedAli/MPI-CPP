
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
    int row, col;
    int rank, size;
    MPI_Status status;
    int *mat1[row];
    int *mat2[row];
    int *mat3[row];
    int sum[row];
    // std::vector<std::array<int, h>> matrix;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
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
        cin >> row;
        std::cout << "enter the height" << std::endl;
        cin >> col;
        inOutCredit << row << col;

        inOutCredit.close();
    }
    inOutCredit >> row >> col;

    int r = (row) / size;

    if (rank == 0)
    {

        for (int i = 0; i < row; i++)
        {
            mat1[i] = (int *)malloc(col * sizeof(int));
        }

        for (int i = 0; i < row; i++)
        {
            mat2[i] = (int *)malloc(col * sizeof(int));
        }
        for (int i = 0; i < row; i++)
        {
            mat3[i] = (int *)malloc(col * sizeof(int));
        }
        int j;
        fill(mat1, row, col);
        fill(mat2, row, col);
        for (int i = 1; i < size; i++)
        {
            for (j = 0; j < r; j++)
            {

                MPI_Send(&mat1[j][0], col, MPI_INT, i, 17, MPI_COMM_WORLD);
                MPI_Send(&mat2[j][0], col, MPI_INT, i, 18, MPI_COMM_WORLD);
            }
            r += r;
            j += r;
        }
        for (int j = 0; j < r; j++)
        {
            for (int i = 0; i < row; i++)
            {
                mat3[j][i] = mat1[j][i] + mat2[j][i];
            }
        }

        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&mat3[i][0], col, MPI_INT, i, 17, MPI_COMM_WORLD, &status);
            // matrix.push_back( { c } );
        }
        // matrix.push_back(sum);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                std::cout << mat3[i][j] << " ";
            }
            cout << std::endl;
        }
    }
    else
    {
        // int *mat1[row];
        // for (int i = 0; i < w; i++)
        // {
        //     mat1[i] = (int *)malloc(h * sizeof(int));
        // }
        // int *mat2[w];
        // for (int i = 0; i < w; i++)
        // {
        //     mat2[i] = (int *)malloc(h * sizeof(int));
        // }
        // int *mat3[w];
        // for (int i = 0; i < w; i++)
        // {
        //     mat3[i] = (int *)malloc(h * sizeof(int));
        // }
        int *m1 = new int[col];
        int *m2 = new int[col];
        int *m3 = new int[col];
        for (int i = 0; i < r; i++)
        {
            MPI_Recv(m1, col, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
            MPI_Recv(m2, col, MPI_INT, 0, 18, MPI_COMM_WORLD, &status);
            for (int i = 0; i < col; i++)
            {
                m3[i] = m1[i] + m2[i];
            
            MPI_Send(m3, col, MPI_INT, 0, 17, MPI_COMM_WORLD);
        }
    }

    return 0;
}