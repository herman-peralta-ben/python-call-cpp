// unix: g++ -shared -o lib/libsimplesum.so -fPIC simple_sum.cpp
// windows: g++ -shared -o lib/libsimplesum.dll simple_sum.cpp

#include <iostream>
#include <thread>

extern "C" {
    int add(int a, int b) {
        return a + b;
    }
}
