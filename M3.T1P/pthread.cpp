#include <iostream>
#include <cstdlib>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;
#define MAX_THREADS 8

const int N = 500;

int A[N][N]; // matrix A
int B[N][N]; // matrix B
int C[N][N]; // matrix C

int thread_counter = 0;
int chunk_size = N / MAX_THREADS;

void *multiplyMatrix(void *args)
{
    int thread_id = thread_counter++;
    // Compute the chunk of rows for the current thread
    int start_row = thread_id * chunk_size;
    int end_row = (thread_id + 1) * chunk_size;

    for (int i = start_row; i < end_row; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

int main()
{
    // int N ;
    // cout << "Enter size of the matrix: ";
    // cin >> N; // inputting size for matrixes

    cout << "Filling Matrixes with random values : " << N << endl;

    srand(time(0));

    // filling all the 2d arrays with randon valus between 1 to 100
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    auto start = std::chrono::high_resolution_clock::now(); // starting time for before multiplication

    // multiplyinh matrix A and B and storing the result in matrix C
    pthread_t matrix_thread[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_create(&matrix_thread[i], NULL, &multiplyMatrix, NULL);
    }

    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_join(matrix_thread[i], NULL);
    }

    auto end = std::chrono::high_resolution_clock::now(); // stoping time after multiplication

    // calculating duration of multiplication
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Time taken for multithread multiplication by pthread library : " << duration.count() / 1e6 << " seconds" << endl;

    return 0;
}