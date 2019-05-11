#include <iostream>
#include <vector>   
#include <algorithm>
#include <random>
#include <cmath>

template<typename F1, typename F2>
double MonteCarlo(F1 f1, F2 f2, double x_l, double x_u, double y_l, double y_u, double z_l, double z_u, int N)
{
    if(x_l > x_u)  { std::cout << "Wrong intervals! X upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    if(y_l > y_u)  { std::cout << "Wrong intervals! Y upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    if(z_l > z_u)  { std::cout << "Wrong intervals! Z upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    
    double x_value = 0;
    double y_value = 0;
    double z_value = 0;

    std::random_device rd; 
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> disX(x_l, x_u);
    std::uniform_real_distribution<double> disY(y_l, y_u);
    std::uniform_real_distribution<double> disZ(z_l, z_u);

    const double V0 = (x_u-x_l) * (y_u-y_l) * (z_u-z_l);
    double integral_value = 0.0;

    for(auto i=0;i<N;i++)
    {
        x_value = disX(gen);
        y_value = disY(gen);
        z_value = disZ(gen);
        if(f2(x_value,y_value,z_value)) integral_value += f1(x_value,y_value,z_value);
    }
    
    integral_value *= V0/N;

    return integral_value;
}
