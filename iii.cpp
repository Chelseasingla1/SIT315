#include <chrono>               // For measuring time
#include <cstdlib>              // For memory allocation and random number generation
#include <iostream>             // For standard input/output operations
#include <ctime>                // For seeding random number generator
#include <thread>               // For multithreading

using namespace std::chrono;   // Namespace for chrono library
using namespace std;            // Namespace for standard library

// Function to generate random values in a given array
void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;   // Generate random number between 0 and 99
    }
}

// Function to perform vector addition in parallel
void parallelVectorAddition(int *v1, int *v2, int *v3, int size) {
    int num_threads = 4; // Number of threads
    int chunk_size = size / num_threads;

    // Create threads
    thread t[num_threads];

    // Launch threads
    for (int i = 0; i < num_threads; i++) {
        t[i] = thread(
            [&](int start, int end) {
                for (int i = start; i < end; i++) {
                    v3[i] = v1[i] + v2[i];
                }
            },
            i * chunk_size, (i + 1) * chunk_size);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        t[i].join();
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

    parallelVectorAddition(v1, v2, v3, size); // Perform vector addition in parallel

    auto stop = high_resolution_clock::now();     // Record the stop time
    auto duration = duration_cast<microseconds>(stop - start);    // Calculate the duration

    // Output the execution time
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    free(v1);                               // Free the allocated memory
    free(v2);                               // Free the allocated memory
    free(v3);                               // Free the allocated memory

    return 0;
}
