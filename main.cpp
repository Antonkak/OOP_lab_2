#include <iostream>
#include "matrix.h"

int main() {

    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    Matrix s(a);
    s.add(b);
    std::cout << "a + b = ";
    s.print(std::cout);
    std::cout << "\n";

    Matrix m(a);
    m.mul(b);
    std::cout << "a * b = ";
    m.print(std::cout);
    std::cout << "\n";

    a.set(0, 0, 5.0);
    std::cout << "after set(0, 0, 5.0) = ";
    a.print(std::cout);
    std::cout << "\n";
    std::cout << "dimension a: " << a.rows() << "x" << a.cols() << "\n";

    std::cout << "sum(a) = " << a.sum() << "\n";

    Matrix copy(a);
    Matrix moved(std::move(copy));
    std::cout << "moved = ";
    moved.print(std::cout);
    std::cout << ", copy empty: " << (copy.rows() == 0 && copy.cols() == 0) << "\n";

    Matrix assigned(3, 3, 9.0);
    assigned = a;
    std::cout << "assigned = a  ->  ";
    assigned.print(std::cout);
    std::cout << "\n";

    return 0;
}
