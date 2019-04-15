#include <iostream>
#include <vector>
#include <array>
#include <numeric>

auto add = [](double a, double b)
{
    return a + b;
};

std::array<double, 3> LinFit(std::vector<double> const& X, std::vector<double> const& Y)
{
    const double avgX = std::accumulate(X.begin(), X.end(), 0.0) / X.size();
    const double avgY = std::accumulate(Y.begin(), Y.end(), 0.0) / Y.size();
    const double b = std::inner_product(X.begin(), X.end(), Y.begin(), 0.0, add, [avgX,avgY](auto const x, auto const y){return (x-avgX)*(y-avgY);}) / std::accumulate(X.begin(), X.end(), 0.0, [avgX](auto const a, auto const x){return a + (x-avgX)*(x-avgX);});
    const double m = avgY - b*avgX;
    //R^2
    const double Stot = std::accumulate(Y.begin(), Y.end(), 0.0, [avgY](auto const a, auto const y){return a + (y-avgY)*(y-avgY);});
    const double Sres = std::inner_product(X.begin(), X.end(), Y.begin(), 0.0, add, [b,m,avgX](auto const x, auto const y){return (y - b*x - m)*(y - b*x - m);});
    const double R2 = 1 - Sres/Stot;
    std::array<double, 3> result = {b, m, R2};
    return result;
}

int main()
{
    const std::vector<double> X = {1,2,3,4,5,7,10};
    const std::vector<double> Y = {3,5.1,7,9,11.1,14.8,20.95};

    std::array<double, 3> result = LinFit(X,Y);
    std::array<double, 3> test = {1.98317,1.0698,0.9998};
    //elvárt eredmények: meredkség=2, tengelymetszet=1, r^2 = 1
    //használt calculator: https://www.graphpad.com/quickcalcs/linear2/
    //használt calculator: R^2 https://www.socscistatistics.com/tests/regression/default.aspx
    //a test eredményeket ilyen pontosággal adta csak meg
    if(std::abs(result[0] - test[0]) > 0.00001) std::cout << "Meredekseg hiba" << result[0] << std::endl;
    if(std::abs(result[1] - test[1]) > 0.00001) std::cout << "Tengelymetszetű hiba" << result[1] << std::endl;
    if(std::abs(result[2] - test[2]) > 0.00001) std::cout << "R^2 hiba" << result[2] << std::endl;
}
