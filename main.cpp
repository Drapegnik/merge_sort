#include <iostream>
#include <fstream>
#include <mpi.h>
#include "merge_sort.cpp"
#include "utils.cpp"

#define ROOT 0
#define LINE_LENGTH 80

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main(int argc, char **argv) {
    int *a;
    int n, size, rank, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    fin >> n;
    int *v = new int[n];
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;
        v[i] = x;
    }

    double start_t, end_t;
    start_t = realtime();

    MPI_Init(NULL, NULL);   // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get the rank of the process
    MPI_Get_processor_name(processor_name, &name_len);  // Get the name of the processor

    int step = n / size;
    int master_count = step + n % size;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == ROOT) {    // master: send params to all process

        print_line(0, LINE_LENGTH, 2);
        print_master();
        cout << " I'm master" << endl << "array: ";
        print(v, n, true);
        print_line(1, LINE_LENGTH, 2);

        int start = 0;

        print_master();
        cout << "\t*receive*\t";
        print(v, master_count, true);
        start += master_count;

        for (int i = 1; i < size; i++) {
            MPI_Send(v + start, step, MPI_INT, i, 77, MPI_COMM_WORLD);
            start += step;
        }
    } else {
        a = new int[step];
        MPI_Recv(a, step, MPI_INT, ROOT, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << "$ proc" << rank << ":\t*receive*\t";
        print(a, step, true);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT)    // master: receive params from all process
    {
        print_line(1, LINE_LENGTH, 2);

        int *sorted = merge_sort(v, 0, master_count - 1);
        print_master();
        cout << "\t*sort*\t\t";
        print(sorted, master_count, true);

        print_master();
        cout << "\t*merge*\t\t";
        print(sorted, master_count, false);

        int length = master_count;

        int *temp = new int[step];
        for (int i = 1; i < size; i++) {
            MPI_Recv(temp, step, MPI_INT, i, 77, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << " + ";
            print(temp, step, false);

            sorted = merge(sorted, temp, length, step);
            length += step;
        }

        end_t = realtime();

        print_line(2, LINE_LENGTH, 1);

        print_master();
        cout << "\t*sorted*\t";
        print(sorted, length, true);

        for (int i = 0; i < length; i++)
            fout << sorted[i] << " ";

        print_master();
        printf("\t*total time*\t%.3lfs\n", end_t - start_t);
    } else {
        a = merge_sort(a, 0, step - 1);
        cout << "$ proc" << rank << ":\t*send*\t\t";
        print(a, step, true);
        MPI_Send(a, step, MPI_INT, ROOT, 77, MPI_COMM_WORLD);
    }

    MPI_Finalize(); // Finalize the MPI environment.

    delete[] a;
    delete[] v;
    return 0;
}