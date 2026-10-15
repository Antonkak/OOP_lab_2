#include "matrix.h"
#include <ostream>
#include <stdexcept>


Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(std::size_t rows, std::size_t cols, double init)
    : rows_(rows), cols_(cols), data_(nullptr) {
    if (rows_ == 0 || cols_ == 0) {
        rows_ = 0;
        cols_ = 0;
        return;
    }
    data_ = new double[rows_ * cols_];
    for (std::size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] = init;
    }
}

Matrix::~Matrix() {
    delete[] data_;
    data_ = nullptr;
}


Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    const std::size_t n = rows_ * cols_;
    if (n == 0) {
        rows_ = 0;
        cols_ = 0;
        return;
    }
    data_ = new double[n];
    for (std::size_t i = 0; i < n; ++i) {
        data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

Matrix& Matrix::operator=(Matrix other) noexcept {
    swap(other);
    return *this;
}

void Matrix::swap(Matrix& other) noexcept {
    std::size_t tmp_r = rows_;
    std::size_t tmp_c = cols_;
    double* tmp_d = data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    other.rows_ = tmp_r;
    other.cols_ = tmp_c;
    other.data_ = tmp_d;
}

std::size_t Matrix::rows() const {
    return rows_;
}

std::size_t Matrix::cols() const {
    return cols_;
}

double Matrix::get(std::size_t r, std::size_t c) const {
    if (r >= rows_ || c >= cols_) {
        throw std::out_of_range("Matrix::get: индекс вне границ");
    }
    return data_[r * cols_ + c];
}

void Matrix::set(std::size_t r, std::size_t c, double value) {
    if (r >= rows_ || c >= cols_) {
        throw std::out_of_range("Matrix::set: индекс вне границ");
    }
    data_[r * cols_ + c] = value;
}


void Matrix::add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix::add: размеры матриц не совпадают");
    }
    for (std::size_t i = 0; i < rows_ * cols_; ++i) {
        data_[i] += other.data_[i];
    }
}

void Matrix::mul(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix::mul: cols_ != other.rows_");
    }
    const std::size_t result_rows = rows_;
    const std::size_t k = cols_;
    const std::size_t result_cols = other.cols_;

    double* buf = new double[result_rows * result_cols]();
    for (std::size_t r = 0; r < result_rows; ++r) {
        for (std::size_t j = 0; j < k; ++j) {
            const double a = data_[r * cols_ + j];
            for (std::size_t c = 0; c < result_cols; ++c) {
                buf[r * result_cols + c] += a * other.data_[j * other.cols_ + c];
            }
        }
    }
    delete[] data_;
    data_ = buf;
    cols_ = result_cols;
}

double Matrix::sum() const {
    double result = 0.0;
    for (std::size_t i = 0; i < rows_ * cols_; ++i) {
        result += data_[i];
    }
    return result;
}

void Matrix::print(std::ostream& os) const {
    os << '[';
    for (std::size_t r = 0; r < rows_; ++r) {
        os << '[';
        for (std::size_t c = 0; c < cols_; ++c) {
            os << data_[r * cols_ + c];
            if (c + 1 < cols_) {
                os << ", ";
            }
        }
        os << ']';
        if (r + 1 < rows_) {
            os << ", ";
        }
    }
    os << ']';
}
