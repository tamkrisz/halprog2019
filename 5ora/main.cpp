#include <iostream>
#include <cmath> 
#include "vec.h"


int main() {
    Vector2d<double> V1 = {3.0, 4.0};
    Vector2d<double> V2 = {1.5, 2.5};
    Vector2d<double> V1copy = {3.0, 4.0};
    //+-
    Vector2d<double> V1addV2res = {4.5, 6.5};
    Vector2d<double> V1subV2res = {1.5, 1.5};
    //norm
    Vector2d<double> normV1 = {0.6, 0.8};
    
    //dot
    double dotV1V2 = 14.5;
    double lengthV1 = 5;
    double sqlengthV1 = 25;
    

    const double diff = 0.0000000001;


    //+operator test
    auto w2 = V1 + V2;
    if(std::abs(w2.x - V1addV2res.x) > diff || std::abs(w2.y - V1addV2res.y) > diff) std::cout << "+operator failed" << std::endl;

    //-operator test
    w2 = V1 - V2;
    if(std::abs(w2.x - V1subV2res.x) > diff || std::abs(w2.y - V1subV2res.y) > diff) std::cout << "-operator failed" << std::endl;

    


    //dot test
    if(std::abs(dot(V1,V2) - dotV1V2) > diff) std::cout << "dot failed" << std::endl;

    //length
    if(std::abs(length(V1) - lengthV1) > diff) std::cout << "length failed" << std::endl;
    //sqlength
    if(std::abs(sqlength(V1) - sqlengthV1) > diff) std::cout << "sqlength failed" << std::endl;
    //normalize
    auto normV1Test = normalize(V1);
    if(std::abs(normV1Test.x - normV1.x) > diff || std::abs(normV1Test.y - normV1.y) > diff) std::cout << "normalize failed" << std::endl;


    
    //+= test
    V1+=V2;
    if((std::abs(V1.x - V1addV2res.x) > diff) || (std::abs(V1.y - V1addV2res.y) >diff)) std::cout << "+=operator failed" << std::endl;
    //-= test
    V1copy-=V2;
    if((std::abs(V1copy.x - V1subV2res.x) > diff) || (std::abs(V1copy.y - V1subV2res.y) > diff)) std::cout << "-=operator failed" << std::endl;
    
    auto V1old = V1;
    V1*=10;
    if(std::abs(10*V1old.x -V1.x) > diff || std::abs(10*V1old.y - V1.y) > diff) std::cout << "*= scalar failed" << std::endl;
    V1/=10;
    if(std::abs(V1old.x -V1.x) > diff || std::abs(V1old.y - V1.y) > diff) std::cout << "/= scalar failed" << std::endl;

    //* operator
    Vector2d<double> c = {1.0,2.0};
    Vector2d<double> d = 10.0*c;
    if(std::abs(10*c.x -d.x) > diff || std::abs(10*c.y - d.y) > diff) std::cout << "* scalar failed" << std::endl;

    //In/out
    std::cout << std::endl << "Input/output test:" << std::endl;
    Vector2d<double> V{};
    std::cin >> V;
    std::cout << V;
 } 
