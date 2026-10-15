#pragma once
#include <cstddef>
#include <iosfwd>

class Matrix {
public:
    Matrix();
    Matrix(std::size_t rows, std::size_t cols, double init = 0.0);
    ~Matrix();

    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix other) noexcept;

    void swap(Matrix& other) noexcept;

    std::size_t rows() const;
    std::size_t cols() const;
    double get(std::size_t r, std::size_t c) const;
    void set(std::size_t r, std::size_t c, double value);

    void add(const Matrix& other);
    void mul(const Matrix& other);
    double sum() const;

    void print(std::ostream& os) const;

private:
    std::size_t rows_;
    std::size_t cols_;
    double* data_;
};
