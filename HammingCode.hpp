#include "Matrix.hpp"
#include "Fp.hpp"
#include <cmath>
#include "time.h"

template<int p>
class HammingCode {
public:
    // Конструктор
    HammingCode(size_t m) : m(m) {
        generate_matrices();
    }

    Matrix<Fp<p>> get_H() const {
        return H;
    }

    Matrix<Fp<p>> get_G() const {
        return G;
    }


    Matrix<Fp<p>> encode(const Matrix<Fp<p>> &data) const {
        return data * G;
    }

    Matrix<Fp<p>> decode(const Matrix<Fp<p>> &codeword) const {
        Matrix<Fp<p>> syndrom = calculate_syndrome(codeword);
        size_t error_flag = -1;
        for (size_t i = 0; i < syndrom.get_rows(); ++i) {
            if (syndrom(i, 0) != 0) {
                error_flag = i;
                break;
            }
        }
        Matrix<Fp<p>> data(1, G.get_rows());
        if (error_flag == -1) {
            for (size_t i = 0; i < G.get_rows(); i++) {
                data(0, i) = codeword(0, i);
            }
            return data;
        } else {
            size_t error_pos = index(syndrom);
            Matrix<Fp<p>> codeword_1 = codeword;
            codeword_1(0, error_pos) += 1;
            return decode(codeword_1);
        }

    }

    Matrix<Fp<p>> sybrom(const Matrix<Fp<p>> &codeword) {
        return calculate_syndrome(codeword);
    }

    // Добавляет случайную ненулевую ошибку в случайную или error_pos позицию
    static Matrix<Fp<p>> add_error(const Matrix<Fp<p>> &codeword, size_t error_pos = -1) {
        Fp<p> num;
        Fp<p> random_num = num.random();
        Matrix<Fp<p>> error_codeword = codeword;
        if (error_pos != 1) {
            if (error_pos >= codeword.get_cols())
                error_pos %= codeword.get_cols();
            error_codeword(0, error_pos) += random_num;
        } else {
            srand((time(0)));
            size_t random_pos = rand() % codeword.get_cols();
            error_codeword(0, random_pos) += random_num;
        }
        return error_codeword;
    }


private:
    // Атрибуты
    size_t n;    // Количество символов в кодовом слове
    size_t k;    // Количество информационных символов
    size_t m;    // Количество проверочных символов
    Matrix<Fp<p>> H; // Проверочная матрица
    Matrix<Fp<p>> G; // Порождающая матрица

    // Вспомогательные методы
    Matrix<Fp<p>> calculate_syndrome(const Matrix<Fp<p>> &codeword) const {
        return H * codeword.transpose();
    }

    int index(const Matrix<Fp<p>> &syndrom) const {
        for (size_t i = 0; i < H.get_cols(); ++i) {
            for (size_t l = 1; l < p; ++l) {
                int fl = 0;
                for (size_t j = 0; j < H.get_rows(); ++j) {

                    if (H(j, i) == syndrom(j, 0) * l)
                        fl++;
                    else
                        break;
                }
                if (fl == H.get_rows())
                    return i;
            }
        }
    }

    // Вспомогательные методы
    void generate_matrices() {
        n = pow(p, m);


        std::vector<std::vector<Fp<p>>> A_data(n, std::vector<Fp<p>>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                A_data[i][j] = (i + 1) / pow(p, j);
            }
        }


        for (size_t one_arg = 0; one_arg < A_data.size(); ++one_arg) {
            for (size_t i = one_arg + 1; i < A_data.size(); ++i) {
                int fl = 0;
                Fp<p> del;
                int check_first = 0;
                for (size_t j = 0; j < m; ++j) {
                    if (A_data[one_arg][j] != 0) {
                        if (j == 0 || check_first == 1) {
                            if (A_data[one_arg][j] / A_data[i][j] != 0) {
                                fl++;
                                del = A_data[one_arg][j] / A_data[i][j];
                            }
                            check_first = 0;
                        } else {
                            if (A_data[one_arg][j] / A_data[i][j] == del)
                                fl++;
                        }
                    } else {
                        if (A_data[i][j] == 0) {
                            fl++;
                            if (j == 0)
                                check_first = 1;
                        }
                    }

                }
                if (m == fl) {
                    A_data.erase(A_data.begin() + i);
                    i--;
                }
            }
        }

        for (size_t i = 0; i < A_data.size(); ++i) {
            int null = 0;
            int one = 0;
            for (size_t j = 0; j < m; ++j) {
                if (A_data[i][j] == 1)
                    one++;
                if (A_data[i][j] == 0)
                    null++;
            }

            if ((one == 1) && (null == m - 1)) {
                A_data.erase(A_data.begin() + i);
                i--;

            }
            if (null == m) {
                A_data.erase(A_data.begin() + i);
                i--;

            }
        }

        Matrix<Fp<p>> A = Matrix<Fp<p>>(A_data);
        k = A.get_rows();
        Matrix<Fp<p>> one_matrix_g = Matrix<Fp<p>>::eye(k);
        G = one_matrix_g.horizontal_concatenate(-A);
        Matrix<Fp<p>> A_transp = A.transpose();
        Matrix<Fp<p>> one_matrix_h = Matrix<Fp<p>>::eye(m);
        H = A_transp.horizontal_concatenate(one_matrix_h);

    }
};