#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_THREADS = 16; // Maximum number of threads

int size;
int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];

// Struct to pass arguments to the thread function
struct ThreadArgs {
    int startRow;
    int endRow;
};

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[][MAX_SIZE]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

// Function to perform matrix multiplication for a range of rows
void* matrixMultiplication(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    for (int i = args->startRow; i <= args->endRow; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    
    cout << "Enter the size of the matrices (max " << MAX_SIZE << "): ";
    cin >> size;
    
    pthread_t threads[MAX_THREADS];
    ThreadArgs threadArgs[MAX_THREADS];
    
    // Initialize matrices A and B with random values
    initializeMatrix(A);
    initializeMatrix(B);
    
    clock_t start = clock(); // Start timing
    
    int chunkSize = size / MAX_THREADS; // Calculate chunk size for each thread
    
    // Create threads for matrix multiplication
    for (int i = 0; i < MAX_THREADS; ++i) {
        threadArgs[i].startRow = i * chunkSize;
        threadArgs[i].endRow = (i == MAX_THREADS - 1) ? size - 1 : (i + 1) * chunkSize - 1;
        pthread_create(&threads[i], NULL, matrixMultiplication, (void*)&threadArgs[i]);
    }
    
    // Join threads
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    clock_t end = clock(); // End timing
    
    // Calculate execution time
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for matrix multiplication: " << time_taken << " seconds" << endl;
    
    // Write the result to a file
    ofstream outputFile("matrix_multiplication_result_parallel.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outputFile << C[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Matrix multiplication result is written to matrix_multiplication_result_parallel.txt" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    
    return 0;
}
