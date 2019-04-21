#include <iostream>
#include <vector>   
#include <chrono>  
#include <algorithm>
#include "matrix.h"
#include <random>
#include <fstream>
#include <cmath>


//az illesztett függvény: f(x) = 1.0991e-05*(x-484.79)^3
int main()
{   

    std::ofstream myfile;
    myfile.open("matmul_time.txt");
    
    std::mt19937 gen(1);
    std::normal_distribution<double> distr(10,5);

    int time_elapsed = 0;
    double min = 1000000;
    int N = 100;
    std::vector<int> sizes = {500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400};
    for(int l=0;l<sizes.size();l++)
    {
        N = sizes[l];
        Matrix<double> a(N);
        Matrix<double> b(N);    
        Matrix<double> c(N);
        for(int k=0;k<20;k++)
        {
            for(int i=0;i<N*N;i++)
            {
                a[i] = distr(gen);
                b[i] = distr(gen);
            }
            auto t0 = std::chrono::high_resolution_clock::now();
            c = a*b;
            auto t1 = std::chrono::high_resolution_clock::now();
            time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
            if(time_elapsed < min) min = time_elapsed;
        }
        note
        myfile << N << " " << min << " " << std::endl;
        std::cout << N << " " << min << " " << std::endl;
        min = 1000000;
    }
}
