// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
template <class T>
void CrossOut(T** matrix, size_t n, int** help, const size_t& indexRow,
    const size_t& indexColumn);
template <class T>
int Determinant(T** matrix, const size_t& n);

template <class T>
class matrix {
public:
    matrix();
    ~matrix();
    matrix(const matrix<T>& matr);
    matrix(const size_t& rowFrom, const size_t& columnFrom);
    size_t Rows() const { return row; }
    size_t Cols() const { return column; }
    matrix<T> Inverse() const;
    T* operator[](const size_t& index) { return data[index]; }
    T* operator[](const size_t& index) const { return data[index]; }
    matrix<T>& operator=(const matrix& matr);
    bool operator==(const matrix& rhs) const;
    bool operator!=(const matrix& rhs) const;
    template <class T1>
    friend matrix<T1> operator+(const matrix<T1>& matr1, const matrix<T1>& matr2);
    template <class T1>
    friend matrix<T1> operator-(const matrix<T1>& matr1, const matrix<T1>& matr2);
    template <class T1>
    friend matrix<T1> operator*(const matrix<T1>& matr1, const matrix<T1>& matr2);
    void Print() {
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < column; ++j) {
                 std::cout << std::showpoint << std::setprecision(3) << data[i][j] << "   ";
            }
            
            std::cout << std::endl;
        }
    }
private:
    T** data;
    size_t row;
    size_t column;
};
template <class T>
int Determinant(T** matrix, const size_t& n) {
    int temp = 0;
    int k = 1;
    if (n == 1) {
        temp = matrix[0][0];
    }
    else if (n == 2) {
        temp = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            size_t m = n - 1;
            int** temp_matr = new int* [m];
            for (size_t j = 0; j < m; ++j) temp_matr[j] = new int[m];
            CrossOut(matrix, n, temp_matr, 0, i);
            temp = temp + k * matrix[0][i] * Determinant(temp_matr, m);
            k = -k;
            for (size_t ind = 0; ind < m; ++ind) delete[] temp_matr[ind];
            delete[] temp_matr;
        }
    }
    return temp;
}
// cross out rows and columns
template <class T>
void CrossOut(T** matrix, size_t n, int** help, const size_t& indexRow,
    const size_t& indexColumn) {
    size_t ki = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i != indexRow) {
            for (size_t j = 0, kj = 0; j < n; ++j) {
                if (j != indexColumn) {
                    help[ki][kj] = matrix[i][j];
                    ++kj;
                }
            }
            ++ki;
        }
    }
}
template <class T>
matrix<T> matrix<T>::Inverse() const {
    if (column != row) {
        matrix<T> InversMatrix(0, 0);
        return InversMatrix;
    }

    size_t n = row;
    // allocate the memory
    T** matr = new T * [n];
    double** obr_matr = new double* [n];
    double** inversMatrix = new double* [n];
    for (size_t i = 0; i < n; ++i) {
        matr[i] = new T[n];
        obr_matr[i] = new double[n];
        inversMatrix[i] = new double[n];
    }
    // copy the data
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < column; ++j) matr[i][j] = data[i][j];
    }
    int det = Determinant(matr, n);
    if (det) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                size_t m = n - 1;
                int** help = new int* [m];
                for (size_t k = 0; k < m; ++k) help[k] = new int[m];
                CrossOut(matr, n, help, i, j);
                obr_matr[i][j] = pow(-1.0, i + j + 2) * Determinant(help, m) / det;
                for (size_t indexdel = 0; indexdel < m; ++indexdel)
                    delete[] help[indexdel];
                delete[] help;
            }
        }
    }
    else {
        matrix<T> InversMatrix(0, 0);
        for (size_t i = 0; i < n; i++) {
            delete[] inversMatrix[i];
            delete[] obr_matr[i];
            delete[] matr[i];
        }
        delete[] obr_matr;
        delete[] inversMatrix;
        delete[] matr;
        return InversMatrix;
    }
    // Transposition
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) inversMatrix[j][i] = obr_matr[i][j];
    }

    // copy the data from the inversMatrix
    matrix<T> InversMatrix(row, column);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) InversMatrix.data[i][j] = inversMatrix[i][j];
    }
    // delete
    for (size_t i = 0; i < n; i++) {
        delete[] inversMatrix[i];
        delete[] obr_matr[i];
        delete[] matr[i];
    }
    delete[] obr_matr;
    delete[] inversMatrix;
    delete[] matr;

    return InversMatrix;
}
template <class T>
matrix<T>::matrix(const matrix<T>& matr) {
    // allocate the memory
    data = new T * [matr.row];
    for (size_t i = 0; i < matr.row; ++i) data[i] = new T[matr.column];

    // copy the data from matr
    for (size_t i = 0; i < matr.row; ++i) {
        for (size_t j = 0; j < matr.column; ++j) data[i][j] = matr.data[i][j];
    }
    column = matr.column;
    row = matr.row;
}
template <class T>
matrix<T>& matrix<T>::operator=(const matrix& matr) {
    if (&matr != this) {
        for (size_t i = 0; i < row; ++i) delete[] data[i];
        delete[] data;
        // allocate the memory
        data = new T * [matr.row];
        for (size_t i = 0; i < matr.row; ++i) data[i] = new T[matr.column];

        // copy the data from matr
        for (size_t i = 0; i < matr.row; ++i) {
            for (size_t j = 0; j < matr.column; ++j) data[i][j] = matr.data[i][j];
        }
        column = matr.column;
        row = matr.row;
    }
    return *this;
}
template <class T>
matrix<T>::matrix() : column(1), row(1) {
    data = new T * [row];
    for (size_t i = 0; i < row; ++i) data[i] = new T[column];
    data[0][0] = 0;
}
template <class T>
matrix<T>::matrix(const size_t& rowFrom, const size_t& columnFrom)
    : row(rowFrom), column(columnFrom) {
    data = new T * [row];
    for (size_t i = 0; i < row; ++i) data[i] = new T[column];
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < column; ++j) data[i][j] = 0;
    }
}
template <class T>
matrix<T>::~matrix() {
    for (size_t i = 0; i < row; ++i) delete[] data[i];
    delete[] data;
}
template <class T1>
matrix<T1> operator+(const matrix<T1>& matr1, const matrix<T1>& matr2) {
    if (matr1.row == matr2.row && matr1.column == matr2.column) {
        matrix<T1> SumMatrix(matr2.row, matr1.column);
        for (size_t i = 0; i < matr1.row; ++i) {
            for (size_t j = 0; j < matr1.column; ++j)
                SumMatrix.data[i][j] = matr1.data[i][j] + matr2.data[i][j];
        }
        return SumMatrix;
    }
    else {
        matrix<T1> SumMatrix(0, 0);
        return SumMatrix;
    }
}
template <class T1>
matrix<T1> operator-(const matrix<T1>& matr1, const matrix<T1>& matr2) {
    if (matr1.row == matr2.row && matr1.column == matr2.column) {
        matrix<T1> SumMatrix(matr1.row, matr2.column);
        for (size_t i = 0; i < matr1.row; ++i) {
            for (size_t j = 0; j < matr1.column; ++j)
                SumMatrix.data[i][j] = matr1.data[i][j] - matr2.data[i][j];
        }
        return SumMatrix;
    }
    else {
        matrix<T1> SumMatrix(0, 0);
        return SumMatrix;
    }
}
template <class T1>
matrix<T1> operator*(const matrix<T1>& matr1, const matrix<T1>& matr2) {
    if (matr1.column == matr2.row) {
        matrix<T1> MultiplicationMatrix(matr1.row, matr2.column);
        for (size_t i = 0; i < matr1.row; ++i) {
            for (size_t j = 0; j < matr2.column; ++j) {
                for (size_t k = 0; k < matr2.column; ++k)
                    MultiplicationMatrix.data[i][j] +=
                    matr1.data[i][k] * matr2.data[k][j];
            }
        }

        for (size_t i = 0; i < matr1.row; ++i) {
            for (size_t j = 0; j < matr2.column; ++j) {
                if (MultiplicationMatrix.data[i][j] < 1e-15)
                    MultiplicationMatrix.data[i][j] = 0;
            }
        }
        return MultiplicationMatrix;
    }
    else {
        matrix<T1> MultiplicationMatrix(0, 0);
        return MultiplicationMatrix;
    }
}
template <class T>
bool matrix<T>::operator==(const matrix<T>& rhs) const {
    if (row != rhs.row || column != rhs.column) return false;
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < column; ++j) {
            if (data[i][j] != rhs.data[i][j]) return false;
        }
    }
    return true;
}
template <class T>
bool matrix<T>::operator!=(const matrix& rhs) const {
    return !(*this == rhs);
}
