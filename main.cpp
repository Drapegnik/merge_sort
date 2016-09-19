#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main(int argc, char **argv) {
    int n, size, rank, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    fin >> n;
    vector<int> v = vector<int>(n);
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;
        v[i] = x;
    }

    for (int i = 0; i < n; i++)
        fout << v[i] <<" ";

    MPI_Init(NULL, NULL);   // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get the rank of the process
    MPI_Get_processor_name(processor_name, &name_len);  // Get the name of the processor

    // Print off a hello world message
    cout << "Hello from processor " << processor_name << ", rank " << rank << " out of " << size << endl;

    MPI_Finalize(); // Finalize the MPI environment.
    return 0;
}