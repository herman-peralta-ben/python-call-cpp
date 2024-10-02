// mac: g++ -shared -o lib/libparallelsum.so -fPIC -pthread -std=c++11 parallel_sum.cpp
// windows: g++ -shared -o lib/libparallelsum.dll -pthread parallel_sum.cpp

#include <iostream>
#include <thread>
#include <chrono>

// using namespace std;

// Function to calculate the sum of part of an array
void partial_sum(int *arr, int start, int end, long *result) {
    *result = 0;
    for (int i = start; i < end; ++i) {
        *result += arr[i];
    }
}

// Multithreaded function that computes the total sum
extern "C" long compute_sum(int *arr, int size) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    long result1, result2;
    // Create two threads, each calculating a part of the array
    std::thread t1(partial_sum, arr, 0, size / 2, &result1);
    std::thread t2(partial_sum, arr, size / 2, size, &result2);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Return the total sum
    long result = result1 + result2;
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "parallel_sum.cpp: result: " << result << std::endl;
    std::cout << "parallel_sum.cpp: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    
    return result;
}
