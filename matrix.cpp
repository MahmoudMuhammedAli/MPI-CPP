#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int w, h;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
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
    }
    return 0;
}