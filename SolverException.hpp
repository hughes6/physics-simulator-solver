#ifndef SOLVEREXCEPTION_HPP
#define SOLVEREXCEPTION_HPP

#include <iostream>
#include <stdexcept>

class SolverException {
  public:
  void incomplete_data();
};

void SolverException::incomplete_data() {
  std::cout << "wrong data \n";
}

#endif