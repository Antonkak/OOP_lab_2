#include <gtest/gtest.h>
#include <ostream>
#include <sstream>
#include <stdexcept>

#include "../src/matrix.h"


TEST(MatrixTest, DefaultCtorIsEmpty) {
    const Matrix m;
    EXPECT_EQ(m.rows(), 0u);
    EXPECT_EQ(m.cols(), 0u);
    EXPECT_DOUBLE_EQ(m.sum(), 0.0);
}

TEST(MatrixTest, CtorFillsInitValue) {
    const Matrix m(2, 3, 1.5);
    ASSERT_EQ(m.rows(), 2u);
    ASSERT_EQ(m.cols(), 3u);
    for (std::size_t r = 0; r < 2; ++r) {
        for (std::size_t c = 0; c < 3; ++c) {
            EXPECT_DOUBLE_EQ(m.get(r, c), 1.5);
        }
    }
}

TEST(MatrixTest, GetSet) {
    Matrix m(2, 2, 0.0);
    m.set(0, 0, 5.0);
    m.set(1, 1, -2.5);
    EXPECT_DOUBLE_EQ(m.get(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(m.get(1, 1), -2.5);
    EXPECT_DOUBLE_EQ(m.get(0, 1), 0.0);
}

TEST(MatrixTest, GetSetOutOfBoundsThrows) {
    Matrix m(2, 2, 1.0);
    EXPECT_THROW(static_cast<void>(m.get(2, 0)), std::out_of_range);
    EXPECT_THROW(m.set(0, 2, 1.0), std::out_of_range);
}

TEST(MatrixTest, DegenerateSizeIsEmpty) {
    const Matrix m(0, 5, 1.0);
    EXPECT_EQ(m.rows(), 0u);
    EXPECT_EQ(m.cols(), 0u);
}


TEST(MatrixTest, CopyCtorIsDeep) {
    Matrix a(2, 2, 1.0);
    const Matrix b(a);
    a.set(0, 0, 100.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 100.0);
}

TEST(MatrixTest, CopyCtorOfEmpty) {
    const Matrix a;
    const Matrix b(a);
    EXPECT_EQ(b.rows(), 0u);
    EXPECT_EQ(b.cols(), 0u);
    EXPECT_DOUBLE_EQ(b.sum(), 0.0);
}

TEST(MatrixTest, MoveCtorStealsDataAndEmptiesSource) {
    Matrix a(2, 2, 3.0);
    Matrix b(std::move(a));
    EXPECT_EQ(b.rows(), 2u);
    EXPECT_EQ(b.cols(), 2u);
    EXPECT_DOUBLE_EQ(b.get(1, 1), 3.0);
    // источник «обнулён»
    EXPECT_EQ(a.rows(), 0u);
    EXPECT_EQ(a.cols(), 0u);
}

TEST(MatrixTest, CopyAssignCopyAndSwap) {
    const Matrix a(1, 2, 7.0);
    Matrix b(3, 3, 0.0);
    b = a;
    EXPECT_EQ(b.rows(), 1u);
    EXPECT_EQ(b.cols(), 2u);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 7.0);
}

TEST(MatrixTest, SelfAssignmentIsSafe) {
    Matrix a(2, 2, 4.0);
    Matrix* pa = &a;
    a = *pa;
    EXPECT_EQ(a.rows(), 2u);
    EXPECT_EQ(a.cols(), 2u);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 4.0);
}

TEST(MatrixTest, MoveAssignEmptiesSource) {
    Matrix a(1, 1, 42.0);
    Matrix b;
    b = std::move(a);
    EXPECT_EQ(b.rows(), 1u);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 42.0);
    EXPECT_EQ(a.rows(), 0u);
}

TEST(MatrixTest, Swap) {
    Matrix a(1, 2, 1.0);
    Matrix b(2, 1, 2.0);
    a.swap(b);
    EXPECT_EQ(a.rows(), 2u);
    EXPECT_EQ(a.cols(), 1u);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 2.0);
    EXPECT_EQ(b.rows(), 1u);
    EXPECT_EQ(b.cols(), 2u);
    EXPECT_DOUBLE_EQ(b.get(0, 1), 1.0);
}

TEST(MatrixTest, Add) {
    Matrix a(2, 2, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);
    Matrix b(2, 2, 5.0);
    a.add(b);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(a.get(0, 1), 7.0);
    EXPECT_DOUBLE_EQ(a.get(1, 0), 8.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 9.0);
}

TEST(MatrixTest, AddSizeMismatchThrows) {
    Matrix a(2, 2, 1.0);
    Matrix b(3, 3, 1.0);
    EXPECT_THROW(a.add(b), std::invalid_argument);
}

TEST(MatrixTest, AddEmptyToEmpty) {
    Matrix a;
    Matrix b;
    a.add(b);
    EXPECT_EQ(a.rows(), 0u);
}

TEST(MatrixTest, Mul) {
    Matrix a(2, 2, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);
    Matrix b(2, 2, 0.0);
    b.set(0, 1, 1.0);
    b.set(1, 0, 1.0);
    a.mul(b);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(a.get(0, 1), 1.0);
    EXPECT_DOUBLE_EQ(a.get(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 3.0);
}

TEST(MatrixTest, MulNonSquare) {
    Matrix a(2, 3, 1.0);
    Matrix b(3, 2, 1.0);
    a.mul(b);
    EXPECT_EQ(a.rows(), 2u);
    EXPECT_EQ(a.cols(), 2u);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 3.0);
}

TEST(MatrixTest, MulSizeMismatchThrows) {
    Matrix a(2, 3, 1.0);
    Matrix b(2, 3, 1.0);
    EXPECT_THROW(a.mul(b), std::invalid_argument);
}


TEST(MatrixTest, SumClassicExample) {
    Matrix m(2, 2, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);
    EXPECT_DOUBLE_EQ(m.sum(), 10.0);
}

TEST(MatrixTest, SumSingleElementAndEmpty) {
    Matrix one(1, 1, 2.5);
    EXPECT_DOUBLE_EQ(one.sum(), 2.5);
    EXPECT_DOUBLE_EQ(Matrix().sum(), 0.0);
}

TEST(MatrixTest, SumWithNegatives) {
    Matrix m(1, 3, 0.0);
    m.set(0, 0, 1.5);
    m.set(0, 1, -2.0);
    m.set(0, 2, 0.5);
    EXPECT_DOUBLE_EQ(m.sum(), 0.0);
}


TEST(MatrixTest, Print) {
    std::ostringstream os;
    Matrix m(2, 2, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);
    m.print(os);
    EXPECT_EQ(os.str(), "[[1, 2], [3, 4]]");
}

TEST(MatrixTest, PrintEmpty) {
    std::ostringstream os;
    Matrix().print(os);
    EXPECT_EQ(os.str(), "[]");
}
