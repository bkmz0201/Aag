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
    Matrix<Fp<p>> get_H() const{
        return  H;
    }
    Matrix<Fp<p>> get_G() const{
        return G;
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
        n = pow(p, m);


        std::vector<std::vector<Fp<p>>> A_data(n, std::vector<Fp<p>>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                A_data[i][j] = (i + 1) / pow(p, j);
            }
        }


        for(size_t one_arg = 0; one_arg < A_data.size(); ++one_arg){
            for(size_t i = one_arg + 1; i < A_data.size(); ++i){
                int fl = 0;
                Fp<p> del;
                int check_first = 0;
                for(size_t j = 0; j < m; ++j){
                    if(A_data[one_arg][j] != 0){
                        if(j == 0 || check_first == 1){
                            if(A_data[one_arg][j] / A_data[i][j] != 0){
                                fl++;
                                del = A_data[one_arg][j] / A_data[i][j];
                            }
                            check_first = 0;
                        }
                        else{
                            if(A_data[one_arg][j] / A_data[i][j] == del)
                                fl++;
                        }
                    }
                    else{
                        if(A_data[i][j] == 0){
                            fl++;
                            if(j == 0)
                                check_first = 1;
                        }
                    }

                }
                if(m == fl){
                    A_data.erase(A_data.begin() + i);
                    i--;
                }
            }
        }

        for(size_t i = 0; i < A_data.size(); ++i){
            int null = 0;
            int one = 0;
            for(size_t j = 0; j < m; ++j){
                if(A_data[i][j] == 1)
                    one++;
                if(A_data[i][j] == 0)
                    null++;
            }

            if((one == 1) && (null == m - 1)) {
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
        Matrix<Fp<p>> A_transp= A.transpose();
        Matrix<Fp<p>> one_matrix_h = Matrix<Fp<p>>::eye(m);
        H = A_transp.horizontal_concatenate(one_matrix_h);

    }
};