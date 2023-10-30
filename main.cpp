#include <iostream>
#include <cassert>

#include "matrix.h"

void DemoMatrix2D() {

    std::cout << "DemoMatrix2D\n";

    Matrix<int, -1> matrix;

    auto a = matrix[0][0];

    assert( a == -1);
    assert( matrix.size() == 0);

    ((matrix[100][100] = 217) = 0) = 314;

    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    for (auto[x,y,v] : matrix) {
        std::cout << x << y << v << std::endl;
    }

}

void DemoMatrix3D(){
    std::cout << "DemoMatrix3D\n";

    Matrix<int, -1, 3> matrix;

    auto a = matrix[0][0][0];

    assert( a == -1);
    assert( matrix.size() == 0);

    matrix[3][100][100] =  111;
    matrix[2][100][101] =  222;
    ((matrix[1][102][100] = 15) = 21) = 333;

    std::cout << "size: " << matrix.size() << std::endl;

    for (auto[x,y,z,v] : matrix ) {
        std::cout << x << y << z << v << std::endl;
    }

}

int main()
{
//    DemoMatrix2D();
//    DemoMatrix3D();

    Matrix<int, 0> matrix;

    for( auto i = 1; i < 10; ++i){
        matrix[i][i] = i;
        matrix[9-i][i] = i;
    }

    for( auto y = 1; y < 9; ++y){
        for( auto x = 1; x < 9; ++x){
            std::cout << matrix[x][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "size: " << matrix.size() << std::endl;

    for (auto[x,y,v] : matrix) {
        std::cout << "[" << x << ","<< y << "]=" << v << std::endl;
    }

    return 0;
}
