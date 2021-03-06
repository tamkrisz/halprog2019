#include <iostream>
#include <cmath>

double sqrt_newton(double num, double x0)
{
  double x1;
  //std::cout << "x0= " << x0 << std::endl;
  int i = 1;

  do 
  {
    x1 = (x0 - (((x0 * x0) - num)/(2* x0)));
    x0 = x1;
    //std::cout << "x" << i << "= " << x1 << std::endl;
    i++;
  } while ((x1 * x1) > num);
  return x1;
}

int main()
{
  std::cout << sqrt_newton(612,10);
  return 0;
}
