#include "matrix_multithread_handler.hpp"
#include <cstddef>

Matrix MatrixMultithreadHandler::multiply(const Matrix &a, const Matrix &b) {
    if (a.column() != b.row()) {
        throw "InvalidMatrixSize";
    }

    Matrix res = Matrix(a.row(), b.column());
    for (size_t i = 0; i < res.row(); i++) {
        for (size_t j = 0; j < res.column(); j++) {
            for (size_t t = 0; t < a.column(); t++) {
                res.m_data[i][j] += a.m_data[i][t] * b.m_data[t][j];
            }
        }
    }
    return res;
}

void MatrixMultithreadHandler::process_matrix_computions(
    const Matrix &a,
    const Matrix &b,
    Matrix &result_matrix,
    std::vector<std::pair<size_t, size_t>> to_process
) {
    for (const auto &[i, j] : to_process) {
        int result = 0;
        for (size_t t = 0; t < a.column(); t++) {
            result += a.m_data[i][t] * b.m_data[t][j];
        }

        std::unique_lock l(write_values);
        result_matrix.m_data[i][j] = result;
    }
};

Matrix MatrixMultithreadHandler::multithread_multiply(
    const Matrix &a,
    const Matrix &b,
    int threads_amount
) {
    if (a.column() != b.row()) {
        throw "InvalidMatrixSize";
    }

    std::vector<std::thread> threads;

    int operations_in_one_thread =
        (a.row() * b.column() + threads_amount - 1) / threads_amount;
    std::vector<std::pair<size_t, size_t>> to_process;

    Matrix res = Matrix(a.row(), b.column());
    for (size_t i = 0; i < res.row(); i++) {
        for (size_t j = 0; j < res.column(); j++) {
            if (to_process.size() < operations_in_one_thread) {
                to_process.push_back({i, j});
            }

            if (to_process.size() == operations_in_one_thread ||
                i == res.row() - 1 && j == res.column() - 1) {
                std::thread current_thread = std::thread(
                    &MatrixMultithreadHandler::process_matrix_computions, this,
                    a, b, std::ref(res), to_process
                );
                threads.emplace_back(std::move(current_thread));

                to_process.clear();
            }
        }
    }

    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    return res;
}
