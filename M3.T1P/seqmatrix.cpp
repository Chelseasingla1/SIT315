#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 700; // size of matric to used

int main()
{
    cout << "Filling Matrixes with random values of size: " << N << endl;

    int A[N][N]; // matrix A
    int B[N][N]; // matrix B
    int C[N][N]; // matrix C

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

    // multiplying matrix A and B and storing the result in matrix C
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();// stoping time after multiplication
    
    // calculating duration of multiplication
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Time taken for multiplication: " << duration.count()/1E6 << " seconds" << endl;

    return 0;
}