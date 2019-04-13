#include <iostream>
#include <vector>
#include <array>
#include <numeric>

double func (double x, double y) {return x-10;}
double func2 (double x, double y) {return y-10;}

auto f = [](double a, double b)
{
    return a + b*b;
};

std::array<double, 2> LinFit(std::vector<double> const& X, std::vector<double> const& Y)
{
    const double avgX = std::accumulate(X.begin(), X.end(), 0.0) / X.size();
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();

    double b = 0;
    double temp = 0;
    for(int i=0;i<X.size();i++)
    {
        b += (X[i]-avgX) * (Y[i] - avgY);
        temp += (X[i]-avgX) * (X[i]-avgX);
    }
    b /= temp;
    const double m = avgY - b*avgX;
    std::array<double, 2> result = {b, m};
    return result;
};

double R2(std::vector<double> const& X, std::vector<double> const& Y, std::array<double, 2> &result)
{
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    double Stot = 0;
    double Sres = 0;
    for(int i=0;i<X.size();i++)
    {
        Stot += (Y[i]-avgY) * (Y[i]-avgY);
        Sres += (Y[i] - result[0]*X[i] - result[1]) * (Y[i] - result[0]*X[i] - result[1]);
    }
    //R^2
    const double R2 = 1 - Sres/Stot;
    return R2;
};


int main()
{
    const std::vector<double> X = {1,2,3,4,5,7,10};
    const std::vector<double> Y = {3,5,7,9,11,15,21};

    std::array<double, 2> result = LinFit(X,Y);
    //elvárt eredmények: meredkség=2, tengelymetszet=1, r^2 = 1
    //használt calculator: https://ncalculators.com/statistics/r-squared-calculator.htm
    std::cout << "Meredekseg= " << result[0] << std::endl;
    std::cout << "Tengelymetszet= " << result[1] << std::endl;
    std::cout << "R^2= " << R2(X,Y,result) << std::endl;
}
