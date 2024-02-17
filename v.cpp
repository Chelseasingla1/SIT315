#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Function to generate random values in a given vector
void randomVector(vector<int>& vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;   // Generate random number between 0 and 99
    }
}

// Function to perform vector addition in parallel
void parallelVectorAddition(int *v1, int *v2, int *v3, int size, int partition_size) {
    int num_threads = thread::hardware_concurrency();

    // Create threads
    thread t[num_threads];

    // Launch threads
    for (int i = 0; i < num_threads; i++) {
        int start = i * partition_size;
        int end = (i == num_threads - 1) ? size : start + partition_size;

        t[i] = thread([&](int start, int end) {
            for (int i = start; i < end; i++) {
                v3[i] = v1[i] + v2[i];
            }
        }, start, end);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        t[i].join();
    }
}

int main() {
    unsigned long size = 100000000;

    vector<int> v1(size), v2(size), v3(size);

    srand(time(0));

    randomVector(v1, size);
    randomVector(v2, size);

    int partition_sizes[] = {100000, 1000000, 10000000, (int)1e7, (int)1e6, (int)1e5};

    for (int partition_size : partition_sizes) {
        auto start = high_resolution_clock::now();

        parallelVectorAddition(&v1[0], &v2[0], &v3[0], size, partition_size);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Partition size: " << partition_size << ", Time taken by function: " << duration.count() << " microseconds" << endl;
    }

    return 0;
}
