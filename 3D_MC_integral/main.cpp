#include <iostream>
#include <vector>   
#include <chrono>  
#include <algorithm>
#include <random>
#include <fstream>
#include <cmath>

template<typename F1, typename F2>
double MonteCarlo(F1 f1, F2 f2, double x_l, double x_u, double y_l, double y_u, double z_l, double z_u, int N)
{
    if(x_l > x_u)  { std::cout << "Wrong intervals! X upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    if(y_l > y_u)  { std::cout << "Wrong intervals! Y upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    if(z_l > z_u)  { std::cout << "Wrong intervals! Z upper limit is smaller than lower limit!" << std::endl; std::exit(-1);  }
    
    double x_value;
    double y_value;
    double z_value;

    double integral_value = 0.0;

    std::random_device rd; 
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> disX(x_l, x_u);
    std::uniform_real_distribution<double> disY(y_l, y_u);
    std::uniform_real_distribution<double> disZ(z_l, z_u);



    for(auto i=0;i<N;i++)
    {
        x_value = disX(gen);
        y_value = disY(gen);
        z_value = disZ(gen);
        integral_value += f1(x_value,y_value,z_value);
    }
    double V0 = (x_u-x_l) * (y_u-y_l) * (z_u - z_l);
    //std::cout << integral_value;
    integral_value *= V0/N;
    
    //std::cout << integral_value;
    return integral_value;
}

int main()
{   
    std::cout.precision(8);
/*
    std::ofstream myfile;
    myfile.open("matmul_time.txt");
    myfile << N << " " << min << " " << std::endl;
    std::cout << N << " " << min << " " << std::endl;
*/
    double x;
   /* x = MonteCarlo( [](auto x, auto y, auto z){ return exp(-x*x-y*y-z*z); },
                [](auto x, auto y, auto z)->bool{ return x*x+y*y+z*z < 16.0; },
                 -4.0, 4.0, -4.0, 4.0, -4.0, 4.0,
                 100);*/

    x = MonteCarlo( [](auto x, auto y, auto z){ return 2*x-3*y+z*z; },
            [](auto x, auto y, auto z)->bool{ return 1; },
             -4.0, 4.0, -4.0, 4.0, -4.0, 4.0,
             1000000);

    
    std::cout << x;
    //integrandus, a második az integrálási tartomány (igazat ad vissza, ha a pont benne van a tartományban), az utolsó 6 az integrálási tartomány bennfoglaló téglatestje, sample size.

}
