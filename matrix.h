#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <array>
#include <iterator>
#include <algorithm>

template<typename T, T Init, std::size_t N=2>
class Matrix{
    using matr = std::map< std::array<int,N> , T>;

    std::array<int,N> idx;
    matr m;

    int dim{0};

    bool CheckIndex(){
        return std::all_of(idx.cbegin(), idx.cend(), [](int nIndex) { return nIndex >= 0; }); // проверка, что индекс задан корректно
    }

public:
    Matrix(){};
    Matrix(Matrix & other){
        // копировать только один элемент матрицы
        idx = other.idx;
        if( other.CheckIndex()){
            m[idx] = other.getValue();
        }
    }

    class iterator {
    private:
        typename matr::iterator _it;
        matr *_m;
    public:
        iterator(matr *val, typename matr::iterator it) : _m( val ), _it(it) { };

        // Проверка на равенство
        bool operator==( const iterator& other ) const {
            if( this == &other ) {
                return true;
            }
            return (_it == other._it);
        }

        // Проверка на неравенство
        bool operator!=( const iterator& other ) const {
            return !operator==( other );
        }

        // Получение текущего значения
        auto operator*() const {
            if(_it != _m->end()) {
                return std::tuple_cat(_it->first, std::make_tuple(_it->second));
            } else{
                return std::tuple_cat(std::array<int, N>(), std::make_tuple(-1));
            }
        }

        // Переход к следующему узлу
        void operator++() {
            if( _it != _m->end()){
                ++_it;
            }
        }
    };

    Matrix &operator[](int index) {
        idx[dim] = index;

        if (++dim == N)
            dim = 0;

        return *this;
    }

    Matrix &operator=(T val) {
        if (CheckIndex()) {
            if (val == Init) {
                // удалить
                m.erase(m.find(idx));
                idx.fill(-1);
            }
            else {
                m[idx] = val;
            }
        }
        dim = 0;
        return *this;
    }

    bool operator==(T value) {
        return (getValue() == value);
    }

    bool operator!=(T value) {
        return !(*this == value);
    }

    Matrix &operator = (Matrix & other) {
        // копировать только один элемент матрицы
        if( this != &other){
            m->clear();
            idx = other.idx;
            if( other.CheckIndex()){
                m[idx] = other.getValue();
            }
            dim = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix &other){
        os << other.getValue();
        return os;
    }

    int size() {
        return m.size();
    }

    T getValue() {
        auto it = m.find(idx);
        if (it != m.end()){
            return it->second;
        } else{
            return Init;
        }
        dim = 0;
    }

    // Получить итератор на начало списка
    iterator begin() {
        return iterator(&m,m.begin());
    };

    // Получить итератор на конец списка
    iterator end(){
        return iterator(&m,m.end());
    };
};


#endif // HASHFUNC_H
