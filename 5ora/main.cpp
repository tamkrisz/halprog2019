#include <iostream>
#include "vec.h"




int main() {
    Vector2d<int> intV1 = {1, 2};
    Vector2d<int> intV2 = {3, 5};
    Vector2d<double> doubleV1 = {3.0, 4.0};
    Vector2d<double> doubleV2 = {1.5, 2.5};
    

    //+/-
    auto w = intV1 + intV2;
    auto w2 = doubleV1 + doubleV2;
    std::cout << "+ operator test" << std::endl;
    std::cout << w.x << " " << w.y << std::endl;
    std::cout << w2.x << " " << w2.y << std::endl;
    auto w3 = intV1 - intV2;
    auto w4 = doubleV1 - doubleV2;
    std::cout << "- operator test" << std::endl;
    std::cout << w3.x << " " << w3.y << std::endl;
    std::cout << w4.x << " " << w4.y << std::endl;

    //dot
    std::cout << "dot product test" << std::endl;
    std::cout << doubleV1 << std::endl;
    std::cout << dot(intV1,intV2) << std::endl;
    
    
    std::cout << "length(double) = " << length(doubleV2) << std::endl;
    std::cout << "sqlength(double) = " << sqlength(doubleV2) << std::endl;
    std::cout << "length(int) = " << length(intV1) << std::endl;
    std::cout << "sqlength(int) = " << sqlength(intV1) << std::endl;

    //+=
    std::cout << std::endl <<  "+= operator test" << std::endl;
    std::cout << "(" << intV1.x << " " << intV1.y << ") + "; 
    std::cout << "(" << intV2.x << " " << intV2.y << ") = "; 
    intV1 += intV2;
    std::cout << "(" << intV1.x << " " << intV1.y << ")" << std::endl; 
    std::cout << "(" << doubleV1.x << " " << doubleV1.y << ") + "; 
    std::cout << "(" << doubleV2.x << " " << doubleV2.y << ") = "; 
    doubleV1 += doubleV2;
    std::cout << "(" << doubleV1.x << " " << doubleV1.y << ")" << std::endl; 

    //-=
    std::cout << std::endl <<  "-= operator test" << std::endl;
    std::cout << "(" << intV1.x << " " << intV1.y << ") + "; 
    std::cout << "(" << intV2.x << " " << intV2.y << ") = "; 
    intV1 += intV2;
    std::cout << "(" << intV1.x << " " << intV1.y << ")" << std::endl; 
    std::cout << "(" << doubleV1.x << " " << doubleV1.y << ") + "; 
    std::cout << "(" << doubleV2.x << " " << doubleV2.y << ") = "; 
    doubleV1 += doubleV2;
    std::cout << "(" << doubleV1.x << " " << doubleV1.y << ")" << std::endl; 

    //In/out
    std::cout << std::endl << "Input/output test:" << std::endl;
    Vector2d<double> V{};
    std::cin >> V;
    std::cout << V;
 } 
