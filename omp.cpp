#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int MAX_SIZE = 100;

int size;
int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[][MAX_SIZE]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiplication() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    
    cout << "Enter the size of the matrices (max " << MAX_SIZE << "): ";
    cin >> size;
    
    // Initialize matrices A and B with random values
    initializeMatrix(A);
    initializeMatrix(B);
    
    clock_t start = clock(); // Start timing
    
    // Perform matrix multiplication
    matrixMultiplication();
    
    clock_t end = clock(); // End timing
    
    // Calculate execution time
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for matrix multiplication (sequential): " << time_taken << " seconds" << endl;
    
    // Write the result to a file
    ofstream outputFile("matrix_multiplication_result_sequential.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outputFile << C[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Matrix multiplication result is written to matrix_multiplication_result_sequential.txt" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    
    return 0;
}
