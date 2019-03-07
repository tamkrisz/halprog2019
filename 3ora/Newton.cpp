#include <iostream>
#include <cmath>

double func1(double x)
{
  return x*x - 1651465.0;
}

double func2(double x)
{
  return 2*x;
}

template<typename F1, typename F2, typename T>
T Newton(F1 f1, F2 f2, T x0)
{
  //std::cout << "x0= " << x0 << std::endl;
  while(abs(f1(x0)/f2(x0)) > 0.00001)
  {
    x0 -= f1(x0)/f2(x0);
    //std::cout << x0 << std::endl;
  } 
  return x0;
}

int main()
{
  //std::cout << Newton(func1, func2, 10.0); 
  std::cout << Newton([](double x){ return x*x - 612.0; }, [](double x){ return 2.0*x; }, 10.0);
  return 0;
}
