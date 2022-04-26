#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <cassert>

#define PRINT_TIME(code) do { \
    auto start = system_clock::now(); \
    code \
    auto end   = system_clock::now(); \
    auto duration = duration_cast<microseconds>(end - start); \
    cout << "time spent: " << double(duration.count()) << "us" << endl; \
} while(0)

using namespace std;

using namespace chrono;

using vec = vector<float>; 

const int scale[] = {256, 512, 1024, 2048};
const string data_path("./data/");

void Gemm(const int &size, vec &a, vec &b, vec &c) {
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            for(int k = 0; k < size; k++)
                c[i*size+j] += a[i*size+k] * b[k*size+j];
}

void CheckResult(const vec &c, const string &result_path) {
    ifstream file_result(result_path);
    int nelems = c.size();
    float res_i;
    for(int i = 0; i < nelems; i++) {
        file_result >> res_i;
        assert(c[i] == res_i);
    }
    file_result.close();
}

// c = a * b
void Benchmark(const int &size) {
    const int nelems = size * size;
    const string a_path(data_path+to_string(size)+"a");
    const string b_path(data_path+to_string(size)+"b");
    const string result_path(data_path+to_string(size)+"result");
    ifstream file_a(a_path);
    ifstream file_b(b_path);

    vec a(nelems);
    vec b(nelems);
    vec c(nelems);

    for(int i = 0; i < nelems; i++) {
        file_a >> a[i];
    }
    for(int i = 0; i < nelems; i++) {
        file_b >> b[i];
    }

    PRINT_TIME(
       Gemm(size, a, b, c);
    );
    
    CheckResult(c, result_path);

    file_a.close();
    file_b.close();
}

int main() {
    for(auto size: scale) {
        cout << "Running, dataset: size " << size << endl;
        Benchmark(size);
        cout << "Passed, dataset: size " << size << endl;
        cout << endl;
    }
    return 0;
}