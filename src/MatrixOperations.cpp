#include "MatrixOperations.h"

// Vector operations
std::vector<double> MatrixOperations::addVectors(const std::vector<double>& v1, const std::vector<double>& v2) {
    validateVectorDimensions(v1, v2);
    std::vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

std::vector<double> MatrixOperations::subtractVectors(const std::vector<double>& v1, const std::vector<double>& v2) {
    validateVectorDimensions(v1, v2);
    std::vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

double MatrixOperations::dotProduct(const std::vector<double>& v1, const std::vector<double>& v2) {
    validateVectorDimensions(v1, v2);
    double result = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

std::vector<double> MatrixOperations::scalarMultiply(const std::vector<double>& v, double scalar) {
    std::vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}

// Matrix operations
MatrixOperations::Matrix MatrixOperations::addMatrices(const Matrix& m1, const Matrix& m2) {
    validateMatrixDimensions(m1, m2);
    Matrix result(m1.size(), std::vector<double>(m1[0].size()));
    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m1[0].size(); ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

MatrixOperations::Matrix MatrixOperations::subtractMatrices(const Matrix& m1, const Matrix& m2) {
    validateMatrixDimensions(m1, m2);
    Matrix result(m1.size(), std::vector<double>(m1[0].size()));
    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m1[0].size(); ++j) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}

MatrixOperations::Matrix MatrixOperations::multiplyMatrices(const Matrix& m1, const Matrix& m2) {
    validateMatrixMultiplication(m1, m2);
    Matrix result(m1.size(), std::vector<double>(m2[0].size(), 0));
    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m2[0].size(); ++j) {
            for (size_t k = 0; k < m2.size(); ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

MatrixOperations::Matrix MatrixOperations::scalarMultiply(const Matrix& m, double scalar) {
    Matrix result = m;
    for (auto& row : result) {
        for (auto& element : row) {
            element *= scalar;
        }
    }
    return result;
}

MatrixOperations::Matrix MatrixOperations::transpose(const Matrix& m) {
    Matrix result(m[0].size(), std::vector<double>(m.size()));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[0].size(); ++j) {
            result[j][i] = m[i][j];
        }
    }
    return result;
}

// Validation methods
void MatrixOperations::validateVectorDimensions(const std::vector<double>& v1, const std::vector<double>& v2) const {
    if (v1.size() != v2.size()) {
        throw std::runtime_error("Vector dimensions do not match!");
    }
}

void MatrixOperations::validateMatrixDimensions(const Matrix& m1, const Matrix& m2) const {
    if (m1.size() != m2.size() || m1[0].size() != m2[0].size()) {
        throw std::runtime_error("Matrix dimensions do not match!");
    }
}

void MatrixOperations::validateMatrixMultiplication(const Matrix& m1, const Matrix& m2) const {
    if (m1[0].size() != m2.size()) {
        throw std::runtime_error("Invalid matrix dimensions for multiplication!");
    }
} 