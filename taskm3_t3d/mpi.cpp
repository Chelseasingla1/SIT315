#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // For generating random numbers
#include <ctime>   // For seeding random number generator
#include <mpi.h>

using namespace std;

// Structure to represent traffic signal data
struct TrafficSignal {
    string timestamp;
    int traffic_light_id;
    int num_cars;

    TrafficSignal(string ts, int id, int cars) : timestamp(ts), traffic_light_id(id), num_cars(cars) {}
};

// Comparison function to sort TrafficSignal objects by number of cars in descending order
bool sortMethod(const TrafficSignal &first, const TrafficSignal &second) {
    return first.num_cars > second.num_cars;
}

// Function to read data from file and distribute it among processes
void distributeData(const string &filename, int num_processes, int process_rank, vector<TrafficSignal> &local_data) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    vector<TrafficSignal> all_data;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string timestamp;
        int traffic_light_id, num_cars;

        // Parse line into timestamp, traffic_light_id, and num_cars
        getline(ss, timestamp, ',');
        ss >> traffic_light_id;
        ss.ignore(); // Ignore the comma
        ss >> num_cars;

        all_data.emplace_back(timestamp, traffic_light_id, num_cars); // Add TrafficSignal directly to the vector
    }
    infile.close();

    // Distribute data among processes using MPI_Scatter
    int local_size = all_data.size() / num_processes;
    local_data.resize(local_size, TrafficSignal("", 0, 0)); // Initialize with default-constructed objects
    MPI_Scatter(all_data.data(), local_size * sizeof(TrafficSignal), MPI_CHAR,
                local_data.data(), local_size * sizeof(TrafficSignal), MPI_CHAR,
                0, MPI_COMM_WORLD);
}

// Function to find and print the top N most congested traffic lights
void printTopN(vector<TrafficSignal> &data, int N, int iteration) {
    // Seed the random number generator with the iteration number
    srand(time(nullptr) + iteration); // Seed random number generator with current time + iteration

    // Update the number of cars for each signal for the current iteration
    for (auto &signal : data) {
        signal.num_cars = rand() % 100 + 1; // Generate random number of cars between 1 and 100
    }

    vector<TrafficSignal> local_copy = data;
    sort(local_copy.begin(), local_copy.end(), sortMethod);

    cout << "Top " << N << " most congested traffic lights (Iteration " << iteration + 1 << "):" << endl;
    cout << "Traffic Light ID\tNumber of Cars" << endl;
    for (int i = 0; i < min(N, static_cast<int>(local_copy.size())); ++i) {
        cout << local_copy[i].traffic_light_id << "\t\t\t" << local_copy[i].num_cars << endl;
    }
}

int main(int argc, char *argv[]) {
    const string filename = "Traffic_data.txt";
    const int top_N = 5;
    const int num_iterations = 5; // Number of iterations

    int num_processes, process_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    vector<TrafficSignal> local_data;
    distributeData(filename, num_processes, process_rank, local_data);

    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        // Each process finds its top N congested traffic lights for the current iteration
        printTopN(local_data, top_N, iteration);

        // Synchronize processes before moving to the next iteration
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}