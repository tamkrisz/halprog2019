#include <iostream>
#include <vector>
#include <array>
#include <numeric>


auto f = [](double a, double b)
{
    return a + std::pow(b,2);
};

void LinFit(std::vector<double> X, std::vector<double> Y, std::array<double, 2> &result)
{
    const double avgX = std::accumulate(X.begin(), X.end(), 0.0) / X.size();
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    std::for_each(X.begin(), X.end(), [&](double& d) { d-=avgX;});
    std::for_each(Y.begin(), Y.end(), [&](double& d) { d-=avgY;});
    double b = std::inner_product(X.begin(), X.end(), Y.begin(), 0.0) / std::accumulate(X.begin(), X.end(), 0.0, f);
    double m = avgY - b*avgX;
    result[0] = b; //meredekség
    result[1] = m; //tengelymetszet
} 

int main()
{
    std::vector<double> X = {1,2,3,4,5,7,10};
    std::vector<double> Y2 = {3.11,4.92,7.05,9.20,11.01,15.4,20.97};
    std::vector<double> Y = {3,5,7,9,11,15,21};
    //m = 2, b = 1
    
    std::array<double, 2> result;

    LinFit(X,Y,result);
    std::cout << result[0] << " " << result[1] << std::endl;
    LinFit(X,Y2,result);
    std::cout << result[0] << " " << result[1] << std::endl;
}
