#pragma once
#include <iostream>

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
        if(other.value == 0)
            return 0;
        int inverse = inversed(other, p);
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
        if(other.value == 0)
            return 0;
        int inverse = inversed(other, p);
        value = (value * inverse) % p;
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

    // Вывод элемента
    template <int Tstream>
    friend std::ostream &operator<<(std::ostream &out, const Fp<Tstream>& el);

private:
    int value; // Значение элемента поля

    int inversed(const Fp<p>& b, int m) const {

        for(int x = 0; x < m; ++x) {
            if ((b * x).val() == 1)
                return x;
        }
    }
};

template <int Tstream>
std::ostream &operator<<(std::ostream &out, const Fp<Tstream>& el) {
    out << el.val();
    return out;
}
