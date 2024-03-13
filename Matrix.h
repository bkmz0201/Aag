#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
class Matrix {
public:
    Matrix();                                      // Конструктор пустой матрицы
    Matrix(size_t rows, size_t cols);              // Конструктор матрицы заданных размеров
    Matrix(const std::vector<std::vector<T>>& v);  // Конструктор матрицы из вектора векторов
    Matrix(const Matrix<T>& other);                // Конструктор копирования

    Matrix<T>& operator=(const Matrix<T>& other);  // Оператор присваивания

    T& operator()(size_t i, size_t j);              // Доступ к элементу (i, j)
    const T& operator()(size_t i, size_t j) const;  // Доступ к элементу (i, j) для константной матрицы

    size_t get_rows() const;  // Получение количества строк
    size_t get_cols() const;  // Получение количества столбцов

    bool operator==(const Matrix<T>& other) const;  // Сравнение матриц
    bool operator!=(const Matrix<T>& other) const;  // Сравнение матриц

    Matrix<T> operator*(const T& x) const;              // Умножение матрицы на элемент
    Matrix<T> operator+(const Matrix<T>& other) const;  // Сложение матриц
    Matrix<T> operator-(const Matrix<T>& other) const;  // Вычитание матриц
    Matrix<T> operator-() const;                        // Отрицание матрицы
    Matrix<T> operator*(const Matrix<T>& other) const;  // Умножение матриц

    Matrix<T> transpose() const;  // Транспонирование матрицы

    // Получение подматрицы, начиная с позиции (row, col) и размерами (rows, cols)
    Matrix<T> submatrix(size_t row, size_t col, size_t rows, size_t cols) const;

    static Matrix<T> eye(size_t n);                    // Создание единичной матрицы
    static Matrix<T> zeros(size_t rows, size_t cols);  // Создание нулевой матрицы

    Matrix<T> horizontal_concatenate(const Matrix<T>& other) const;  // Конкатенация матриц по горизонтали
    Matrix<T> vertical_concatenate(const Matrix<T>& other) const;    // Конкатенация матриц по вертикали

    // «Красивый» вывод матрицы
    template <typename Tstream>
    friend std::ostream &operator<<(std::ostream &out, const Matrix<Tstream>& m);

private:
    size_t rows;                      // количество строк
    size_t cols;                      // количество столбцов
    std::vector<std::vector<T>> data; // данные матрицы
};

template <typename Tstream>
std::ostream &operator<<(std::ostream &out, const Matrix<Tstream>& m) {
    const int MAX_NUM_DIGITS = 5;
    out << std::endl;
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            out << std::setw(MAX_NUM_DIGITS) << m(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}