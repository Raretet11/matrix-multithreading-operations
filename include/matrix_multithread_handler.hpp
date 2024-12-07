#ifndef MATRIX_MULTITHREAD_HANDLER_
#define MATRIX_MULTITHREAD_HANDLER_

#include <mutex>
#include <thread>
#include "matrix.hpp"

class MatrixMultithreadHandler {
public:
    Matrix multiply(const Matrix &a, const Matrix &b);

    Matrix multithread_multiply(
        const Matrix &a,
        const Matrix &b,
        int threads_amount = 1
    );

private:
    void process_matrix_computions(
        const Matrix &a,
        const Matrix &b,
        Matrix &result_matrix,
        std::vector<std::pair<size_t, size_t>> to_process
    );
    std::mutex write_values;
};

#endif