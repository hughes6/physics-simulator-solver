#include <iostream>
#include <string>
#include <vector>

#include "test.hpp"

void print(std::string s) {
  std::cout << s << "\n";
}

int main (int argc, char* argv[]) {
  std::cout << "Main is running \n";

  std::vector<double> init_states, app_forces;
  init_states = {1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//m dt len a- v- v1- x-
  app_forces = {0.0, 0.0, 0.0, 2.0, 0.0, 0.0};//Fx,y,z Ax,y,z
  double drag = 0.00;

  Solver solver(init_states, app_forces, drag);
  solver.init_integrate('r');
  solver.solve();
  // solver.print_result();
  solver.update_filename("test.txt");
  solver.write_to_file();

  // EngineTester t;
  // t.run();

  return 0;
}