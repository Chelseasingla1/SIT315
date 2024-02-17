#include <chrono>               // For measuring time
#include <cstdlib>              // For memory allocation and random number generation
#include <iostream>             // For standard input/output operations
#include <ctime>                // For seeding random number generator

using namespace std::chrono;   // Namespace for chrono library
using namespace std;            // Namespace for standard library

// Function to generate random values in a given array
void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;   // Generate random number between 0 and 99
    }
}



int main() {
    unsigned long size = 100000000;        // Size of the vectors
    srand(time(0));                         // Seed the random number generator
    int *v1, *v2, *v3;                      // Pointers to arrays for vectors

    auto start = high_resolution_clock::now();    // Record the start time

    v1 = (int *)malloc(size * sizeof(int)); // Allocate memory for vectors v1
    v2 = (int *)malloc(size * sizeof(int)); // Allocate memory for vectors v2
    v3 = (int *)malloc(size * sizeof(int)); // Allocate memory for vectors v3

    randomVector(v1, size);                 // Generate random values for v1
    randomVector(v2, size);                 // Generate random values for v2

    for (int i = 0; i < size; i++) { //loop
    v3[i] = v1[i] + v2[i];
    }
    
    auto stop = high_resolution_clock::now();     // Record the stop time
    auto duration = duration_cast<microseconds>(stop - start);    // Calculate the duration

    // Output the execution time
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;


    return 0;
}
