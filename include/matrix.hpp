#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <cstddef>
#include <iostream>
#include <vector>

class MatrixMultithreadHandler;

class Matrix {
public:
    friend class MatrixMultithreadHandler;
    friend bool operator==(const Matrix &a, const Matrix &b);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    operator std::vector<std::vector<int>>() const;

    Matrix() = default;
    Matrix(size_t n, size_t m, int value = 0);

    Matrix(const std::vector<std::vector<int>> &data_);

    [[nodiscard]] size_t row() const;
    [[nodiscard]] size_t column() const;

private:
    std::vector<std::vector<int>> m_data;
};

#endif