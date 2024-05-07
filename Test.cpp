#pragma once
#include "HammingCode.hpp"


int main() {

    freopen("output.txt", "w", stdout);
    HammingCode<3>  L(3);
    Fp<5> random_num(14);
    Fp<5> rr = random_num.random();
    std::cout << rr << std::endl;
    Matrix<Fp<3>> H_matrix = L.get_H();
    Matrix<Fp<3>> G_matrix = L.get_G();
    std::cout << H_matrix << std::endl;
    std::cout << G_matrix << std::endl;
    Matrix<Fp<3>> sub = G_matrix * H_matrix.transpose();
    std::cout << sub << std::endl;
    Fp<3> a = 9;
    Fp<3> b = 8;
    std::cout << a << '\n' << b << '\n' << a / b << '\n' << a + b << '\n' << a - b << std::endl;
    Matrix<Fp<3>> data(1, G_matrix.get_rows());
    for(size_t i = 0; i < data.get_cols(); i++){
        data(0, i) = rand();
    }
    std::cout << "data:" << std::endl;
    std::cout << data << std::endl;
    Matrix<Fp<3>> codeword = L.encode(data);
    std::cout << "codeword:" << std::endl;
    std::cout << codeword << std::endl;
    Matrix<Fp<3>> decode_word = L.decode(codeword);
    std::cout << "decode:" << std::endl;
    std::cout << decode_word << std::endl;
    Matrix<Fp<3>> error_word = L.add_error(codeword);
    std::cout << "error_word:" << std::endl;
    std::cout << error_word << std::endl;
    Matrix<Fp<3>> syndrom = L.sybrom(error_word);
    std::cout << "syndrom:" << std::endl;
    std::cout << syndrom << std::endl;
    Matrix<Fp<3>> decode_error_word = L.decode(error_word);
    std::cout << "decode_error_word:" << std::endl;
    std::cout << decode_error_word << std::endl;


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