#include "Matrix.hpp"
#include "Fp.hpp"
#include "math.h"


template<int p>
class HammingCode {
public:
    // Конструктор
    HammingCode(size_t m) : m(m){
        generate_matrices();
    }
    // Функция для переумножения матриц G и H(T)
    Matrix<Fp<p>> sub(){
        Matrix<Fp<p>> subd = G * H.transpose();
        return subd;
    }
    // Функция для вывода матриц G и H
    void Print(){
        std::cout << "Matrix G:" << std::endl;
        std::cout << G << std::endl;
        std::cout << "Matrix H:" << std::endl;
        std::cout << H << std::endl;
    }

private:
    // Атрибуты
    size_t n;    // Количество символов в кодовом слове
    size_t k;    // Количество информационных символов
    size_t m;    // Количество проверочных символов
    Matrix<Fp<p>> H; // Проверочная матрица
    Matrix<Fp<p>> G; // Порождающая матрица


    // Вспомогательные методы
    void generate_matrices() {
        // Вычисление n и k. Для того чтобы вычислить n(количество линейно незавсимых комбинация)
        // мы возводим p(по какому модулю мы все берем) в m(количество "проверяющих символов" на слово так же вычитаем 0000(пустое слово)
        // Затем делим на p - 1, что бы сохранить ленйноую независимость
        // например рассмотрим p = 3: 001, 002 будут линейно зависимы.
        n = (pow(p, m) - 1)/(p - 1);
        k = n - m;
        // Создаем единичную матрицу размерности к, для пораждающей матрицы G
        Matrix<Fp<p>> one_matrix_g = Matrix<Fp<p>>::eye(k);
        // Создание вектора векторов с размерами k на m
        // Матрица А заполняется следующим образом: У нас есть единичная матрица размерности к,
        // обзавем ее элементы на первой строке l1, l2,...,lk
        // также есть матрица А(k, m) обзавем ее элементы t1, t2,...,tm
        // и так t1 = l2 + l3 + ... + lk;  t2 = l1 + l3 + .. + lk;  tm = l1 + l2 + ... + l(m - 1) + l(m + 1)+ ... + lk
        // То есть складываются все элементы, кроме тех у которых индексы и так повторяется для каждой строки
        std::vector<std::vector<Fp<p>>> A_data(k, std::vector<Fp<p>>(m));
        for(size_t i = 0; i < k; ++i) {
            for (size_t j = 0; j < m; ++j) {
                for (size_t l = 0; l < k; ++l) {
                    if (j != l)
                        A_data[i][j] += one_matrix_g(i, l);
                }
            }
        }
        // Создаем матрицу А из вектора векторов
        Matrix<Fp<p>> A = Matrix<Fp<p>>(A_data);
        // Создаем матрицу G с помощью горизонтальной конкатинации единичной матрицы и матрицы A
        G = one_matrix_g.horizontal_concatenate(A);
        // Транспонируем матрицу А
        Matrix<Fp<p>> A_transponir= A.transpose();
        // Отрицаем матрицу А
        Matrix<Fp<p>> A_otr = -A_transponir;
        // Создаем единичную матрицу размернстью m
        Matrix<Fp<p>> one_matrix_h = Matrix<Fp<p>>::eye(m);
        // Создаем матрицу H с помощью горизонтальной конкатинации матрицы -А и единичной матрицы
        H = A_otr.horizontal_concatenate(one_matrix_h);

    }
};