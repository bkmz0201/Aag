template<int p>
class Fp {
public:

    // Конструктор
    Fp(int x = 0): value(x % p){
        if(value < 0)
            value += p;
    }

    // Возвращает значение элемента поля
    int val() const{
        return value;
    }

    // Операция присваивания от целого числа
    Fp<p>& operator=(int x){
        value = x % p;
        if(value < 0)
            value += p;
        return *this;
    }

    // Операция сложения
    Fp<p> operator+(const Fp<p>& other) const{
        return Fp<p>((value + other.value) % p);
    }

    // Операция вычитания
    Fp<p> operator-(const Fp<p>& other) const{
        return Fp<p>((value - other.value + p) % p);
    }

    // Операция умножения
    Fp<p> operator*(const Fp<p>& other) const{
        return Fp<p>((value * other.value) % p);
    }

    // Операция деления
    Fp<p> operator/(const Fp<p>& other) const{
        int inverse = inversed(other.value, p);
        if (inverse == -1) {
            return Fp<p>();
        }
        return Fp<p>((value * inverse) % p);

    }

    // Операция смены знака
    Fp<p> operator-() const{
        return Fp<p>((p - value) % p);
    }

    // Операция += (сложение с присваиванием)
    Fp<p>& operator+=(const Fp<p>& other){
        value = (value + other.value) % p;
        return *this;
    }

    // Операция -= (вычитание с присваиванием)
    Fp<p>& operator-=(const Fp<p>& other){
        value = (value - other.value + p) % p;
        return *this;
    }

    // Операция *= (умножение с присваиванием)
    Fp<p>& operator*=(const Fp<p>& other){
        value = (value * other.value) % p;
        return *this;
    }

    // Операция /= (деление с присваиванием)
    Fp<p>& operator/=(const Fp<p>& other){
        int inverse = inversed(other.value, p);
        if (inverse != -1) {
            value = (value * inverse) % p;
        } else {
            value = 0;
        }
        return *this;

    }


    // Операция сравнения на равенство
    bool operator==(const Fp<p>& other) const{
        return value == other.value;
    }

    // Операция сравнения на неравенство
    bool operator!=(const Fp<p>& other) const{
        return value != other.value;
    }

private:
    int value; // Значение элемента поля


    // Функция для нахождения обратного элемента
    // Данная функция основывается на алгоритме Евклида а так же на коэфицентах безу
    // По тождеству Безу мы емеем bx + my = НОД(b, m), затем мы добиваемся чтобы НОД был равен 1,
    // то есть мы делаем преобраования до тех пор пока числа не станут взаимно простыми.
    // Тогда как раз таки x будет являтся обратным элементом b по модулу m
    int inversed(int b, int m) const {
        //переменные для хранения промезжуточных значений
        int m0 = m;
        int y = 0, x = 1;

        if (m == 1)
            return 0;

        while (b > 1) {
            int q = b / m;
            int t = m;
            m = b % m;
            b = t;
            t = y;
            y = x - q * y;
            x = t;
        }
        // Проверка на отрицательное значение обратного элемента
        if (x < 0)
            x += m0;

        return x;
    }
};