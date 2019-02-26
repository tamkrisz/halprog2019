#include <iostream>
#include <cmath>

double integrate(double a, double b, int n)
{
    double sum=0;
    double init, end, x, step;
    int j;
    step = (b-a)/n;
    init = cos(a)*exp(-a*a)/2;
    end = cos(b)*exp(-b*b)/2;
    for (j=1;j<=n-1;j++)
    {
        x = j*step+a;
        sum += cos(x)*exp(-x*x);
    }
    sum = (sum+init+end)*step;
    return sum;
}



int main()
{
  std::cout.precision(16);
  std::cout << "N   " << "Integral" << std::endl;
  for(int i=1;i<100;i++)
  {
    std::cout << i << "   " <<  integrate(-1,3,i) << std::endl;
  }
  return 0;
}