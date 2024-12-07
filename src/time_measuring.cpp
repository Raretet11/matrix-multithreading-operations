#include <chrono>
#include <random>
#include "matrix.hpp"
#include "matrix_multithread_handler.hpp"

Matrix gen_matrix(int n, int m) {
    std::vector<std::vector<int>> data(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            data[i][j] = rand() % 10;
        }
    }
    return Matrix(data);
}

int main() {
    int n = 1000, l = 500, m = 1000;
    int thread_amounts = 16;
    Matrix a = gen_matrix(n, l);
    Matrix b = gen_matrix(l, m);
    MatrixMultithreadHandler mmh = MatrixMultithreadHandler();

    auto start = std::chrono::steady_clock::now();

    Matrix one_thread_mat = mmh.multiply(a, b);

    std::cerr << "Elapsed "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - start
                 )
                     .count()
              << "ms\n";

    start = std::chrono::steady_clock::now();

    Matrix multithread_mat = mmh.multithread_multiply(a, b, thread_amounts);

    std::cerr << "Elapsed "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - start
                 )
                     .count()
              << "ms\n";

    if (one_thread_mat == multithread_mat) {
        std::cout << "OK\n";
    }
    return 0;
}