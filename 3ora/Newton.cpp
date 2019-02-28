#include <iostream>
#include <cmath>

double func1(double x, double num)
{
  return x*x - num;
}

double func2(double x)
{
  return 2*x;
}

template<typename T, typename F1, typename F2>
T Newton(F1 f1, F2 f2, T x0, T num)
{
  double x1 = 0; 
  double temp = 0;
  std::cout << "x0= " << x0 << std::endl;
  int i = 1;
  while(abs(temp-x0) > 0.0001)
  {
    temp = x0;
    x1 = x0 - f1(x0,num)/f2(x0);
    x0 = x1;
    std::cout << temp << std::endl;
  } 
  return x1;
}

int main()
{
  std::cout << Newton(func1, func2, 10.0, 612.0);
  return 0;
}
