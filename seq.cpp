#include <iostream>
#include <fstream>
#include <chrono>

const int N = 100; // Size of matrices

void matrixMultiplication(int A[][N], int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N];
    int B[N][N];
    int C[N][N];

    // Initialize matrices A and B with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    // Perform matrix multiplication
    auto start = std::chrono::high_resolution_clock::now();
    matrixMultiplication(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Write the result to a file
    std::ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                outputFile << C[i][j] << " ";
            }
            outputFile << std::endl;
        }
        outputFile.close();
    } else {
        std::cout << "Unable to open the output file." << std::endl;
    }

    // Print the execution time
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
