#include <iostream>
#include <vector>   
#include <chrono>  
#include <algorithm>
#include "matrix.h"
#include <random>
#include <fstream>
#include <cmath>

int main()
{   

    std::ofstream myfile;
    myfile.open("matmul_time.txt");
    
    std::mt19937 gen(1);
    std::normal_distribution<double> distr(1000,200);

    double time_elapsed = 0;
    double min = 1000000;
    double max = 0;
    int N = 100;
    std::vector<int> sizes = {500,1000,1500,2000};
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
            if(time_elapsed > max) max = time_elapsed;
        }
        
        myfile << N << " " << min << " " << max << std::endl;
        std::cout << N << " " << min << " " << max << std::endl;
        min = 1000000;
    }
}
