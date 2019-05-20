#include <iostream>
#include <vector>   
#include <chrono>  
#include <algorithm>
#include <random>
#include <fstream>
#include <cmath>
#include "MCint.h"


void Error()
{
    std::ofstream myfile;
    double x = 0;
    myfile.open("error.txt");
    double exact_value = 0.3333333333333; //x^2 integrálja 0-tol 1-ig 1/3
    std::vector<int> sizes = {1000,10000,50000,100000,500000,1000000,5000000,10000000,50000000,100000000,500000000};

    for(unsigned int i=0;i<sizes.size();i++)
    {
        x = MonteCarlo( [](auto x, auto y, auto z){ return x*x; },
            [](auto x, auto y, auto z)->bool{ return x < 1; },
            0, 2, 0, 1, 0, 1,
            sizes[i]);
        myfile << sizes[i] << " " << x << " " << std::abs(exact_value - x) << std::endl;
        std::cout << sizes[i] << " " << x << " " << std::abs(exact_value - x) << std::endl;
    }
    //az illesztett függvény: f(x) = 0.4478/sqrt(x-8180,59)
}


int main()
{   
    std::cout.precision(10);
     
    {
    double result = -57.23958;
    double x = MonteCarlo( [](auto x, auto y, auto z){ return 1-z; },
                [](auto x, auto y, auto z)->bool{ return (x*x+y*y+z*z < 5*5 && z > 0 && z < 5); },
                 0, 5, 0, 5, 0, 5,
                 10000000); 

    std::cout << std::abs(x - result) << std::endl;
    }
    

    {
    double result = 313.04504;
    double x = MonteCarlo( [](auto x, auto y, auto z){ return x*x+10*x+2*std::sqrt(y) + std::log(z); },
                [](auto x, auto y, auto z)->bool{ return 1; },
                 -1.0, 2.0, 0, 3.0, 0, 4.0,
                 10000000);

    std::cout << std::abs(x - result) << std::endl;
    }
    
    //Error();
}
