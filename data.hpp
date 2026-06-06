#ifndef DATA_HPP
#define DATA_HPP

#include <cmath>
#include <functional>
#include <vector>

#include "SolverException.hpp"

struct Data {
  Data () = default;
  Data(const std::vector<double>& x, const std::vector<double>& y, const double z) 
    : states(x), 
      applied_forces(y), 
      drag(z) 
      {
        filename = "output.txt";
        results.resize((states.at(2) / states.at(1)) * columns);
      }
  std::vector<double> states;
  std::vector<double> applied_forces;
  std::vector<double> results;
  int columns = 9;
  float drag;
  std::string filename;
  SolverException e;

  void validate_inputs();
  double at(int row, int column);
  void insert(int row, int column, double data);
};

#endif

void Data::validate_inputs() {
  if(states.empty()) {e.incomplete_data();}//exception
}

double Data::at(int r, int c) {
  return results[r * 9 + c];
}

void Data::insert(int r, int c, double data){
  // std::cout << "inserting " << data << " into position " << r*9+c << std::endl;
  results[r * 9 + c] = data;
}
