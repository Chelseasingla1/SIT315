#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 100;

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[][MAX_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiplication(int A[][MAX_SIZE], int B[][MAX_SIZE], int C[][MAX_SIZE], int size) {
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
    
    int size;
    cout << "Enter the size of the matrices (max " << MAX_SIZE << "): ";
    cin >> size;
    
    int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE];
    
    // Initialize matrices A and B with random values
    initializeMatrix(A, size);
    initializeMatrix(B, size);
    
    clock_t start = clock(); // Start timing
    
    // Perform matrix multiplication
    matrixMultiplication(A, B, C, size);
    
    clock_t end = clock(); // End timing
    
    // Calculate execution time
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken for matrix multiplication: " << time_taken << " seconds" << endl;
    
    // Write the result to a file
    ofstream outputFile("matrix_multiplication_result.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outputFile << C[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Matrix multiplication result is written to matrix_multiplication_result.txt" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    
    return 0;
}
