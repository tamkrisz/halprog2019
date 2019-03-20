#include <iostream>
#include "vec.h"


int main() {
    Vector2d<double> V1 = {3.0, 4.0};
    Vector2d<double> V2 = {1.5, 2.5};
    Vector2d<double> V1copy = {3.0, 4.0};
    //+-
    Vector2d<double> V1addV2res = {4.5, 6.5};
    Vector2d<double> V1subV2res = {1.5, 1.5};
    
    //dot
    double dotV1V2 = 14.5;
    double lengthV1 = 5;
    double sqlengthV1 = 25;


    //+operator test
    auto w2 = V1 + V2;
    if(abs(w2.x - V1addV2res.x) > 0.00000001 || abs(w2.y - V1addV2res.y) > 0.00000001) std::cout << "+operator failed" << std::endl;

    //-operator test
    w2 = V1 - V2;
    if(abs(w2.x - V1subV2res.x) > 0.00000001 || abs(w2.y - V1subV2res.y) > 0.00000001) std::cout << "-operator failed" << std::endl;

    


    //dot test
    if(abs(dot(V1,V2) - dotV1V2) > 0.00000001) std::cout << "dot failed" << std::endl;

    //length
    if(abs(length(V1) - lengthV1) > 0.00000001) std::cout << "length failed" << std::endl;
    //sqlength
    if(abs(sqlength(V1) - sqlengthV1) > 0.00000001) std::cout << "sqlength failed" << std::endl;
    
    //+= test
    V1+=V2;
    if((abs(V1.x - V1addV2res.x) > 0.00000001) || (abs(V1.y - V1addV2res.y) >0.00000001)) std::cout << "+=operator failed" << std::endl;
    //-= test
    V1copy-=V2;
    if((abs(V1copy.x - V1subV2res.x) > 0.00000001) || (abs(V1copy.y - V1subV2res.y) > 0.00000001)) std::cout << "-=operator failed" << std::endl;

    //In/out
    std::cout << std::endl << "Input/output test:" << std::endl;
    Vector2d<double> V{};
    std::cin >> V;
    std::cout << V;
 } 
