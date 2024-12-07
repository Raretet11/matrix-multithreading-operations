#include "matrix.hpp"
#include <cstddef>

Matrix::Matrix(size_t n, size_t m, int value) {
    m_data.assign(n, std::vector<int>(m, value));
};

Matrix::Matrix(const std::vector<std::vector<int>> &data_) : m_data(data_){};

size_t Matrix::row() const {
    return m_data.size();
};

size_t Matrix::column() const {
    if (row() == 0) {
        return 0;
    }
    return m_data[0].size();
};

Matrix::operator std::vector<std::vector<int>>() const {
    return m_data;
};

bool operator==(const Matrix &a, const Matrix &b) {
    return a.m_data == b.m_data;
};

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (auto line : matrix.m_data) {
        for (auto x : line) {
            os << x << ' ';
        }
        os << '\n';
    }
    return os;
}
