#include "HammingCode.hpp"


int main() {
    HammingCode<2>  L(3);
    Matrix<Fp<2>> sub = L.sub();
    L.Print();
    std::cout << "The result of multiplication:" << std::endl;
    std::cout << sub << std::endl;


    // Создание матрицы 3x3 и заполнение ее значениями
    Matrix<Fp<5>> mat1(3, 3);
    for (size_t i = 0; i < mat1.get_rows(); ++i) {
        for (size_t j = 0; j < mat1.get_cols(); ++j) {
            mat1(i, j) = i * mat1.get_cols() + j;
        }
    }

    // Вывод созданной матрицы
    std::cout << "Matrix mat1:" << std::endl;
    std::cout << mat1 << std::endl;

    // Создание матрицы 3x3 из вектора векторов
    std::vector<std::vector<Fp<5>>> vec = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    Matrix<Fp<5>> mat2(vec);

    // Вывод второй матрицы
    std::cout << "Matrix mat2:" << std::endl;
    std::cout << mat2 << std::endl;

    // Операция сложения двух матриц
    Matrix<Fp<5>> sum = mat1 + mat2;


    Matrix<Fp<5>> mul = mat1 * mat2;

    // Вывод результата сложения
    std::cout << "Matrix sum (mat1 + mat2):" << std::endl;
    std::cout << sum << std::endl;

    std::cout << "Matrix mul (mat1 * mat2):" << std::endl;
    std::cout << mul << std::endl;

    // Умножение матрицы на число
    Matrix<Fp<5>> mult_const = mat1 * 2;

    // Вывод результата умножения матрицы на число
    std::cout << "Matrix mult_const (mat1 * 2):" << std::endl;
    std::cout << mult_const << std::endl;

    // Транспонирование матрицы
    Matrix<Fp<5>> transposed = mat1.transpose();

    // Вывод транспонированной матрицы
    std::cout << "Transposed Matrix mat1:" << std::endl;
    std::cout << transposed << std::endl;

    return 0;
}