#include <iostream>
#include <cmath>

template<typename F1, typename F2, typename T>
T Newton(F1 f1, F2 f2, T x0)
{
  T diff = 1;
  while(std::abs(diff) > 0.00001)
  {
    diff = f1(x0)/f2(x0);
    x0 -= diff;
  } 
  return x0;
}

int main()
{
  std::cout.precision(16);
  std::cout << Newton([](double x){ return x*x - 612.0; }, [](double x){ return 2.0*x; }, 10.0);
  return 0;
}
