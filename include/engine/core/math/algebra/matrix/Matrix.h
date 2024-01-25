/******************************************************************************
 * @file   Matrix.h
 * @author Valentin Dumitru
 * @date   2023-10-03
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cmath>
#include <memory>
#include <algorithm>
#include <engine/core/asserts/Asserts.h>
#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/asserts/MatrixAsserts.h"
#include "engine/core/math/algebra/matrix/MatrixMixedAlgorithms.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "MatrixAlgorithms.h"

namespace GLESC::Math {
    template<typename Type, size_t N, size_t M>
    class Matrix {
        S_ASSERT_TRUE(N > 0 && M > 0, "Matrix must have at least one row and one column.");
    public:
        // =========================================================================================
        // ======================================= Constructors ====================================
        // =========================================================================================
        
        Matrix() {
            MatrixAlgorithms::setMatrxZero(this->data);
        }
        
        explicit Matrix(const Type diagonal) {
            MatrixAlgorithms::setMatrixDiagonal(this->data, diagonal);
        }
        
        /**
         * @brief Constructor array list
         * @param data
         */
        explicit Matrix(const Type (&data)[N][M]) {
            MatrixAlgorithms::setMatrix(this->data, data);
        }
        
        
        /**
         * @brief Copy constructor
         * @param other
         */
        Matrix(const Matrix<Type, N, M> &other) {
            MatrixAlgorithms::copyMatrix(this->data, other.data);
        }
        
        /**
         * @brief Move constructor
         * @param list
         */
        Matrix(Matrix<Type, N, M> &&other) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(other.data));
        }
        
        Matrix(const MatrixData<Type, N, M> &other) {
            MatrixAlgorithms::copyMatrix(this->data, other);
        }
        
        
        
        // =========================================================================================
        // ========================================= Operators =====================================
        // =========================================================================================
        
        
        // ================================== Assignment Operators =================================
        
        /**
         * @brief Copy assignment operator.
         * @param other The matrix to copy from.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator=(const Matrix<Type, N, M> &other) noexcept {
            MatrixAlgorithms::copyMatrix(this->data, other.data);
            return *this;
        }
        
        Matrix<Type, N, M> &operator=(MatrixData<Type, N, M> &other) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, other);
            return *this;
        }
        
        Matrix<Type, N, M> &operator=(MatrixData<Type, N, M> &&other) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(other));
            return *this;
        }
        
        /**
         * @brief Move assignment operator.
         * @param rhs The matrix to move from.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator=(Matrix<Type, N, M> &&rhs) noexcept {
            MatrixAlgorithms::moveMatrix(this->data, std::move(rhs.data));
            return *this;
        }
        
        /**
         * @brief Assignment operator from a 2D array.
         * @param data 2D array to assign from.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator=(Type (&data)[N][M]) {
            MatrixAlgorithms::setMatrix(this->data, data);
            return *this;
        }
        
        /**
         * @brief In-place element-wise multiplication with another matrix.
         * @param rhs The matrix to multiply with.
         * @return Reference to the modified instance.
         */
        template<size_t X>
        Matrix<Type, N, X> &operator*=(const Matrix<Type, M, X> &rhs) {
            MatrixAlgorithms::matrixMul(this->data, rhs.data, data);
            return *this;
        }
        
        /**
         * @brief In-place scalar multiplication.
         * @param scalar The scalar to multiply with.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator*=(Type scalar) {
            MatrixAlgorithms::matrixScalarMul(this->data, scalar, data);
            return *this;
        }
        
        /**
         * @brief In-place scalar addition.
         * @param rhs The scalar to add.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator+=(Type rhs) {
            MatrixAlgorithms::matrixScalarAdd(this->data, rhs, data);
            return *this;
        }
        
        /**
         * @brief In-place element-wise addition with another matrix.
         * @param rhs The matrix to add with.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator+=(const Matrix<Type, N, M> &rhs) {
            MatrixAlgorithms::matrixAdd(this->data, rhs.data, data);
            return *this;
        }
        
        /**
         * @brief In-place element-wise subtraction with another matrix.
         * @param rhs The matrix to subtract with.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator-=(const Matrix<Type, N, M> &rhs) {
            MatrixAlgorithms::matrixSub(this->data, rhs.data, data);
            return *this;
        }
        
        /**
         * @brief In-place scalar subtraction.
         * @param rhs The scalar to subtract.
         * @return Reference to the modified instance.
         */
        Matrix<Type, N, M> &operator-=(Type rhs) {
            MatrixAlgorithms::matrixScalarSub(this->data, rhs, data);
            return *this;
        }
        
        /**
         * @brief In-place scalar division.
         * @param scalar The scalar to divide by.
         * @return Reference to the modified instance.
         * @throws MathException if division by zero
         */
        Matrix<Type, N, M> &operator/=(Type scalar) {
            MatrixAlgorithms::matrixScalarDiv(this->data, scalar, data);
            return *this;
        }
        
        /**
         * @brief In-place division by another matrix.
         * @param rhs The matrix to divide by.
         * @return Reference to the modified instance.
         * @throws MathException if division by zero
         */
        Matrix<Type, N, M> &operator/=(const Matrix<Type, N, M> &rhs) {
            if (eq(rhs.determinant(), Type(0))) {
                throw MathException("Division by zero");
            }
            *this *= rhs.inverse();
            return *this;
        }
        
        // ================================== Arithmetic Operators =================================
        
        [[nodiscard]] Matrix<Type, N, M> operator+(const Matrix<Type, N, M> &rhs) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixAdd(this->data, rhs.data, result.data);
            return result;
        }
        
        [[nodiscard]] Matrix<Type, N, M> operator+(Type scalar) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixScalarAdd(this->data, scalar, result.data);
            return result;
        }
        
        [[nodiscard]] Matrix<Type, N, M> operator-(const Matrix<Type, N, M> &rhs) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixSub(this->data, rhs.data, result.data);
            return result;
        }
        
        [[nodiscard]] Matrix<Type, N, M> operator-(Type scalar) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixScalarSub(this->data, scalar, result.data);
            return result;
        }
        
        [[nodiscard]] Matrix<Type, N, M> operator-() const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixScalarMul(this->data, Type(-1), result.data);
            return result;
        }
        
        /**
         * @brief Multiplying Matrix by Matrix
         * @details A matrix NxM multiplied by a matrix MxX results in a matrix N x X
         * For example:
         * | 1 2 3 |   | 7  8  |   | 58  64  |
         * | 4 5 6 | * | 9  10 | = | 139 154 |
         *             | 11 12 |
         * 2x3      *  3x2       = 2x2
         * @tparam X
         * @param other
         * @return
         */
        template<size_t X>
        [[nodiscard]] Matrix<Type, N, X> operator*(const Matrix<Type, M, X> &other) const {
            Matrix<Type, N, X> result;
            MatrixAlgorithms::matrixMul(this->data, other.data, result.data);
            return result;
        }
        
        /**
         * @brief Multiplying Matrix by Vector
         * @details A matrix NxM multiplied by a vector Mx1 results in a vector N
         * (which acts as a matrix Nx1)
         * For example:
         * | 1 2 3 |   | 7 |   | 58  |
         * | 4 5 6 | * | 8 | = | 139 |
         *             | 9 |
         *    2x3    *  3x1  =   2x1
         * @tparam X The dimension of the vector
         * @param vector The vector to multiply with
         * @return The result of the multiplication
         */
        [[nodiscard]] std::array<Type, N> operator*(const Vector<Type, M> &vector) const {
            std::array<Type, N> result;
            MatrixData<Type, N, 1> vectorDataMatrixified({vector.data});
            MatrixAlgorithms::matrixMul(this->data, vectorDataMatrixified.data, result.data);
            return result;
        }
        
        
        [[nodiscard]] Matrix<Type, N, M> operator*(Type scalar) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixScalarMul(this->data, scalar, result.data);
            return result;
        }
        
        
        [[nodiscard]] Matrix<Type, N, M> operator/(Type scalar) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixScalarDiv(this->data, scalar, result.data);
            return result;
        }
        
        
        /**
         * @brief Matrix division by matrix
         * @details The matrix division by matrix is defined as the multiplication of the first
         * matrix by the inverse of the second matrix
         * @param rhs
         * @return
         */
        template<size_t X>
        [[nodiscard]] Matrix<Type, N, M> operator/(const Matrix<Type, M, X> &rhs) const {
            Matrix<Type, N, M> result;
            MatrixAlgorithms::matrixDiv(this->data, rhs.data, result.data);
            return result;
        }
        
        // =============================================================================================================
        // ============================================== Access Operators =============================================
        // =============================================================================================================
        
        [[nodiscard]] const std::array<Type, M> &operator[](size_t index) const {
            return data[index];
        }
        
        [[nodiscard]] std::array<Type, M> &operator[](size_t index) {
            return data[index];
        }
        
        /**
         * @brief Access operator for the matrix, getters are always const
         * @param i The row index
         * @param j The column index
         * @return The value at the given row and column
         */
        [[nodiscard]] const Type &get(size_t i, size_t j) const {
            return data[i][j];
        }
        
        /**
         * @brief Access operator for the matrix, getters are always const
         * @param i The row index
         * @return The const row at the given index
         */
        [[nodiscard]] const MatrixRow<Type, M> &get(size_t i) const {
            return data[i];
        }
        
        [[nodiscard]] size_t rows() const {
            return N;
        }
        
        [[nodiscard]] size_t cols() const {
            return M;
        }
        
        // =============================================================================================================
        // =========================================== Comparison Operators ============================================
        // =============================================================================================================
        
        [[nodiscard]] bool operator==(const Matrix<Type, N, M> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                for (size_t k = 0; k < M; ++k) {
                    if (!eq(this->data[i][k], rhs.data[i][k])) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        [[nodiscard]] bool operator!=(const Matrix<Type, N, M> &rhs) const {
            return !(*this == rhs);
        }
        
        // =============================================================================================================
        // ============================================= Matrix Functions ==============================================
        // =============================================================================================================
        
        [[nodiscard]] Matrix<Type, M, N> transpose() const {
            Matrix<Type, M, N> result;
            MatrixAlgorithms::transpose(this->data, result.data);
            return result;
        }
        
        // TODO: Check if this determinant is more efficient than gaussian elimination
        //   also, don't recalculate, store it
        [[nodiscard]]Type determinant() const {
            return MatrixAlgorithms::laplaceExpansionDeterminant(this->data);
        }
        
        [[nodiscard]] Matrix<Type, N, N> inverse() const {
            Matrix<Type, N, N> inv;
            MatrixAlgorithms::matrixInverse(this->data, inv.data);
            return inv;
        }
        
        /**
         * @brief Applies a rotation to the model matrix with a vector
         * @param translation
         * @return
         */
        [[nodiscard]] Matrix<Type, N, M> translate(const Vector<Type, N - 1> &translation) const {
            S_ASSERT_MAT_IS_SQUARE(N, M);
            Matrix<Type, N, M> result;
            MatrixAlgorithms::translate(this->data, translation.data, result.data);
            return result;
        }
        
        /**
         * @brief Applies a scale to the model matrix with a vector
         * @param scale
         * @return
         */
        [[nodiscard]] Matrix<Type, N, N> scale(const Vector<Type, N - 1> &scale) const {
            Matrix<Type, N, N> result;
            MatrixAlgorithms::scale(this->data, scale.data, result.data);
            return result;
        }
        
        
        /**
          * @brief Applies a rotation to the model matrix.
          * @details The
          * @tparam VecType
          * @param degrees
          * @return
          */
        template<typename VecType>
        [[nodiscard]] Matrix<Type, N, M> rotate(const VecType &degrees) const {
            static_assert(N != 3 && M != 3 || N != 4 && M != 4, "Rotation is only supported for 2D and 3D matrices");
            Matrix<Type, N, N> result;
            if constexpr (std::is_same_v<VecType, Type> && N == 3 && M == 3)
                MatrixMixedAlgorithms::rotate2D(this->data, static_cast<Type>(degrees), result.data);
            
            else if constexpr (std::is_same_v<VecType, Vector<Type, 3>> && N == 4 && M == 4)
                MatrixMixedAlgorithms::rotate3D(this->data, static_cast<Vector<Type, 3>>(degrees).data, result.data);
            else
                S_ASSERT_TRUE(false, "Vector type is not supported for rotation");
            
            return result;
        }
        
        /**
         * @brief Calculates the rank of the matrix.
         * @details The rank of a matrix is the maximum number of linearly independent rows or
         * columns. This implementation uses Gaussian elimination.
         * @return size_t representing the rank of the matrix.
         */
        [[nodiscard]] size_t rank() {
            return MatrixAlgorithms::gaussianElimination(this->data).rank;
        }
        
        
        [[nodiscard]] Matrix<Type, 3, 3> lookAt(const Vector<Type, 2> &target) const {
            Matrix<Type, 3, 3> result;
            MatrixMixedAlgorithms::lookAt2D(this->data, target.data, result.data);
            return result;
        }
        
        [[nodiscard]] Matrix<Type, 4, 4> lookAt(const Vector<Type, 3> &target, const Vector<Type, 3> &up) const {
            Matrix<Type, 4, 4> result;
            MatrixMixedAlgorithms::lookAt3D(this->data, target.data, up.data, result.data);
            return result;
        }
        
        
        [[nodiscard]] std::string toString() const {
            std::string result;
            for (size_t i = 0; i < N; ++i) {
                result += "[";
                for (size_t j = 0; j < M; ++j) {
                    result += std::to_string(this->data[i][j]);
                    if (j != M - 1) {
                        result += ", ";
                    }
                }
                result += "]\n";
            }
            return result;
        }
        
        // =============================================================================================================
        // ============================================ Iterator =======================================================
        // =============================================================================================================
        
        
        
        /**
         * @brief Iterator class for the matrix
         * @tparam MatrixType The matrix, we use this to allow reusing the iterator for const and non-const matrices
         * @tparam ValueType
         */
        template<typename MatrixType,
                 typename MatrixRowType,
                 typename ValueType>
        class MatrixIterator : std::iterator<std::forward_iterator_tag, MatrixRowType>{
            MatrixType *matrix;
            size_t row;
            // Also, we need to assert that the type inside the matrix has the same constness as the matrix itself
            static_assert(std::is_const<MatrixType>::value == std::is_const<ValueType>::value,
                          "Matrix type and ValueType must have the same constness");
        
        public:
            // Use a constructor that takes a matrix and an initial row index
            MatrixIterator(MatrixType *m, size_t initialRow) : matrix(m), row(initialRow) {}
            
            // Increment the row index
            MatrixIterator &operator++() {
                ++row;
                return *this;
            }
            
            // Postfix increment
            MatrixIterator operator++(int) {
                MatrixIterator copy = *this;
                ++(*this);
                return copy;
            }
            
            // Dereference operator
            MatrixRowType &operator*() const {
                return (*matrix)[row];
            }
            
            // Comparison for equality
            bool operator!=(const MatrixIterator &other) const {
                return row != other.row;
            }
            
        };
        
        using Iterator = MatrixIterator<GLESC::Math::Matrix<Type, N, M>, MatrixRow<Type, M>, Type>;
        using ConstIterator = MatrixIterator<const GLESC::Math::Matrix<Type, N, M>, const MatrixRow<Type, M>,
                const Type>;
        
        // And the begin/end functions would return Iterator/ConstIterator appropriately
        Iterator begin() { return Iterator(this, 0); }
        
        Iterator end() { return Iterator(this, N); }
        
        ConstIterator begin() const { return ConstIterator(this, 0); }
        
        ConstIterator end() const { return ConstIterator(this, N); }
        
        /**
         * @brief Matrix data
         * @details Matrix data is stored in a vector of vectors
         * M is the number of columns or the width of the matrix
         * N is the number of rows (or vertices) or the height of the matrix
         */
        MatrixData<Type, N, M> data;
    }; // class Matrix
} // namespace GLESC::Math
using Mat2   [[maybe_unused]] = GLESC::Math::Matrix<float, 2, 2>;
using Mat3   [[maybe_unused]] = GLESC::Math::Matrix<float, 3, 3>;
using Mat4   [[maybe_unused]] = GLESC::Math::Matrix<float, 4, 4>;
using Mat2D  [[maybe_unused]] = GLESC::Math::Matrix<double, 2, 2>;
using Mat3D  [[maybe_unused]] = GLESC::Math::Matrix<double, 3, 3>;
using Mat4D  [[maybe_unused]] = GLESC::Math::Matrix<double, 4, 4>;
using Mat2I  [[maybe_unused]] = GLESC::Math::Matrix<int, 2, 2>;
using Mat3I  [[maybe_unused]] = GLESC::Math::Matrix<int, 3, 3>;
using Mat4I  [[maybe_unused]] = GLESC::Math::Matrix<int, 4, 4>;
using Mat2Ui [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 2, 2>;
using Mat3Ui [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 3, 3>;
using Mat4Ui [[maybe_unused]] = GLESC::Math::Matrix<unsigned int, 4, 4>;
using Mat2L  [[maybe_unused]] = GLESC::Math::Matrix<long, 2, 2>;
using Mat3L  [[maybe_unused]] = GLESC::Math::Matrix<long, 3, 3>;
using Mat4L  [[maybe_unused]] = GLESC::Math::Matrix<long, 4, 4>;
using Mat2Ul [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 2, 2>;
using Mat3Ul [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 3, 3>;
using Mat4Ul [[maybe_unused]] = GLESC::Math::Matrix<unsigned long, 4, 4>;
using Mat2F  [[maybe_unused]] = GLESC::Math::Matrix<float, 2, 2>;
using Mat3F  [[maybe_unused]] = GLESC::Math::Matrix<float, 3, 3>;
using Mat4F  [[maybe_unused]] = GLESC::Math::Matrix<float, 4, 4>;


namespace GLESC::Math {
    inline Mat4D perspective(double fovRadians, double aspectRatio, double nearPlane, double farPlane) {
        Mat4D result;
        
        double f = 1.0 / tan(fovRadians / 2.0);
        
        result[0][0] = f / aspectRatio;
        result[1][1] = f;
        result[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
        result[2][3] = (2.0 * farPlane * nearPlane) / (nearPlane - farPlane);
        result[3][2] = -1.0;
        result[3][3] = 0.0;
        
        return result;
    }
}