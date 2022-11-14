# MATRIX 

### Функциал класса:
- [X] Обратная матрица 
- [X] Определитель
- [X] Умножение матриц
- [X] Сумма матриц
- [X] Вычитание матриц
- [X] Сравнение матриц и пр.

# Тело класса:
```c++
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
```
