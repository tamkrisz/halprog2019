#include <iostream>
#include "vec.h"

int main() {
    Vector2<int> intV1 = {1, 2};
    Vector2<int> intV2 = {3, 5};
    Vector2<double> doubleV1 = {3.0, 4.0};
    Vector2<double> doubleV2 = {1.5, 2.5};
    
    //+ operator
    auto w = intV1 + intV2;
    auto w2 = doubleV1 + doubleV2;
    std::cout << w.x << " " << w.y << std::endl;
    std::cout << w2.x << " " << w2.y << std::endl;
/*
    //+= operator
    intV1 += intV2;
    std::cout << intV1.x << " " << intV1.y << std::endl; 
    doubleV1 += doubleV2;
    std::cout << doubleV1.x << " " << doubleV1.y << std::endl;
*/
    //dot
    std::cout << doubleV1 << std::endl;
    std::cout << dot(intV1,intV2) << std::endl;
    
    std::cout << "double= " << length(doubleV1) << std::endl;
    std::cout << "int= " << length(intV1) << std::endl;

 } 
