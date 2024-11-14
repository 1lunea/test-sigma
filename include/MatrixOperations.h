#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>
#include <stdexcept>

class MatrixOperations {
public:
    // Vector operations
    std::vector<double> addVectors(const std::vector<double>& v1, const std::vector<double>& v2);
    std::vector<double> subtractVectors(const std::vector<double>& v1, const std::vector<double>& v2);
    double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2);
    std::vector<double> scalarMultiply(const std::vector<double>& v, double scalar);
    
    // Matrix operations
    using Matrix = std::vector<std::vector<double>>;
    Matrix addMatrices(const Matrix& m1, const Matrix& m2);
    Matrix subtractMatrices(const Matrix& m1, const Matrix& m2);
    Matrix multiplyMatrices(const Matrix& m1, const Matrix& m2);
    Matrix scalarMultiply(const Matrix& m, double scalar);
    Matrix transpose(const Matrix& m);
    
private:
    void validateVectorDimensions(const std::vector<double>& v1, const std::vector<double>& v2) const;
    void validateMatrixDimensions(const Matrix& m1, const Matrix& m2) const;
    void validateMatrixMultiplication(const Matrix& m1, const Matrix& m2) const;
};

#endif 