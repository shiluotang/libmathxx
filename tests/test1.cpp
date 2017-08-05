#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctime>

#include "../src/matrix/matrix.hpp"

time_t clock_now() {
    std::time_t now;
    if (std::time(&now) == -1)
        throw std::runtime_error("Failed to retrieve the calendar time!");
    return now;
}

int main(int argc, char* argv[]) try {
    using namespace std;
    using namespace mathxx::matrix;

    stack_matrix<double, 3, 3> sm1(0), sm2(1);
    heap_matrix<double> hm1(3, 3), hm2(3, 3, 1);

    std::size_t N = 0xffffffu;
    time_t t1, t2;
    t1 = clock_now();
    for (std::size_t i = 0; i < N; ++i) {
        hm1 = hm2 + hm2;
    }
    sm1 = sm2 + sm2;
    t2 = clock_now();
    cout << hm1 << endl;
    cout << sm1 << endl;
    double elapsed = std::difftime(t2, t1);
    cout << "N = " << N
        << ", Total = " << elapsed << " s"
        << ", Average = " << elapsed / N << " s"
        << ", QPS = " << N / elapsed
        << endl;
} catch (std::exception const &e) {
    std::cerr << "[C++ Exception]: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
