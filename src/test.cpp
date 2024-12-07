#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest.h"
#include "matrix_multithread_handler.hpp"

TEST_CASE("Simple one thread multiplication test") {
    MatrixMultithreadHandler mmh = MatrixMultithreadHandler();
    Matrix a = Matrix({{1, 2}, {2, 3}, {1, 3}});
    Matrix b = Matrix({{3, 4}, {7, 8}});
    Matrix c = mmh.multiply(a, b);

    std::vector<std::vector<int>> result = {{17, 20}, {27, 32}, {24, 28}};
    CHECK(c == result);

    a = Matrix({{1, 1}, {0, 1}});
    b = Matrix({{5, 2}, {0, 0}});
    c = mmh.multiply(a, b);
    result = {{5, 2}, {0, 0}};
    CHECK(c == result);

    a = Matrix(std::vector<std::vector<int>>{{1}});
    b = Matrix(std::vector<std::vector<int>>{{5}});
    c = mmh.multiply(a, b);
    result = std::vector<std::vector<int>>{{5}};
    CHECK(c == result);

    a = Matrix({{1, 1, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}});
    b = Matrix(std::vector<std::vector<int>>{{5}, {0}, {1}});
    c = mmh.multiply(a, b);
    result = {{5}, {0}, {5}, {1}};
    CHECK(c == result);
}

TEST_CASE("Simple multithread multiplication test") {
    MatrixMultithreadHandler mmh = MatrixMultithreadHandler();
    Matrix a = Matrix({{1, 2}, {2, 3}, {1, 3}});
    Matrix b = Matrix({{3, 4}, {7, 8}});
    Matrix c = mmh.multithread_multiply(a, b);

    std::vector<std::vector<int>> result = {{17, 20}, {27, 32}, {24, 28}};
    CHECK(c == result);

    a = Matrix({{1, 1}, {0, 1}});
    b = Matrix({{5, 2}, {0, 0}});
    c = mmh.multithread_multiply(a, b);
    result = {{5, 2}, {0, 0}};
    CHECK(c == result);

    a = Matrix(std::vector<std::vector<int>>{{1}});
    b = Matrix(std::vector<std::vector<int>>{{5}});
    c = mmh.multithread_multiply(a, b);
    result = std::vector<std::vector<int>>{{5}};
    CHECK(c == result);

    a = Matrix({{1, 1, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}});
    b = Matrix(std::vector<std::vector<int>>{{5}, {0}, {1}});
    c = mmh.multithread_multiply(a, b);
    result = {{5}, {0}, {5}, {1}};
    CHECK(c == result);
}
