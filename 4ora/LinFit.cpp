#include <iostream>
#include <vector>
#include <array>
#include <numeric>


auto f = [](double a, double b)
{
    return a + std::pow(b,2);
};

std::array<double, 2> LinFit(std::vector<double> X, std::vector<double> Y, std::array<double, 2> result)
{
    const double avgX = std::accumulate(X.begin(), X.end(), 0.0) / X.size();
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    std::for_each(X.begin(), X.end(), [&](double& d) { d-=avgX;});
    std::for_each(Y.begin(), Y.end(), [&](double& d) { d-=avgY;});
    double b = std::inner_product(X.begin(), X.end(), Y.begin(), 0.0) / std::accumulate(X.begin(), X.end(), 0.0, f);
    double m = avgY - b*avgX;
    result[0] = b; //meredekség
    result[1] = m; //tengelymetszet
    return result;
};

double R2(std::vector<double> X, std::vector<double> Y, std::array<double, 2> result)
{
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    std::vector<double> Y_orig = Y;
    //sum(y[i] - avgY)^2
    std::for_each(Y.begin(), Y.end(), [&](double& d) { d-=avgY;});
    const double Stot = std::accumulate(Y.begin(), Y.end(), 0.0, f);

    //sum(y[i] - f[i])^2;
    for(int i=0;i<X.size();i++)
    {
        Y_orig[i] -= result[0]*X[i] + result[1];
    }
    const double Sres = std::accumulate(Y_orig.begin(), Y_orig.end(), 0.0, f);

    //R^2
    const double R2 = 1 - Sres/Stot;
    return R2;
};


int main()
{
    const std::vector<double> X = {1,2,3,4,5,7,10};
    const std::vector<double> Y2 = {3.11,4.92,7.05,9.2,11.01,15.4,20.97};
    const std::vector<double> Y3 = {3.3,4.6,7,9.50,11.51,15.5,20.8};
    const std::vector<double> Y = {3,5,7,9,11,15,21};

    std::array<double, 2> result = LinFit(X,Y3,result);
    std::cout << "Meredekseg= " << result[0] << std::endl;
    std::cout << "Tengelymetszet= " << result[1] << std::endl;
    std::cout << "R^2= " << R2(X,Y3,result) << std::endl;
}
