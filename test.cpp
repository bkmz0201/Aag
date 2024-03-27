

#include "Matrix.hpp"

int main() {
    // Создание матрицы 3x3 и заполнение ее значениями
    Matrix<int> mat1(3, 3);
    for (size_t i = 0; i < mat1.get_rows(); ++i) {
        for (size_t j = 0; j < mat1.get_cols(); ++j) {
            mat1(i, j) = i * mat1.get_cols() + j;
        }
    }

    // Вывод созданной матрицы
    std::cout << "Matrix mat1:" << std::endl;
    std::cout << mat1;

    // Создание матрицы 3x3 из вектора векторов
    std::vector<std::vector<int>> vec = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    Matrix<int> mat2(vec);

    // Вывод второй матрицы
    std::cout << "Matrix mat2:" << std::endl;
    std::cout << mat2;

    // Операция сложения двух матриц
    Matrix<int> sum = mat1 + mat2;

    // Вывод результата сложения
    std::cout << "Matrix sum (mat1 + mat2):" << std::endl;
    std::cout << sum;

    // Умножение матрицы на число
    Matrix<int> mult_const = mat1 * 2;

    // Вывод результата умножения матрицы на число
    std::cout << "Matrix mult_const (mat1 * 2):" << std::endl;
    std::cout << mult_const;

    // Транспонирование матрицы
    Matrix<int> transposed = mat1.transpose();

    // Вывод транспонированной матрицы
    std::cout << "Transposed Matrix mat1:" << std::endl;
    std::cout << transposed;

    return 0;
}
