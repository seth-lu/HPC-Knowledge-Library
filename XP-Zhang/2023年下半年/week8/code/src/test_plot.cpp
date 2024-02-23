#include "../include/matplotlibcpp.h"
#include <cmath>
#include <iostream>

namespace plt = matplotlibcpp;

int main() {
  std::vector<double> x = {1, 2, 3, 4};
  std::vector<double> y = {1, 4, 9, 16};

  plt::plot(x, y);
  plt::show();

  return 0;
}