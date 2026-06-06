#ifndef TEST_HPP
#define TEST_HPP

#include <memory>

#include "solver.hpp"

class EngineTester : public Solver{
  public:
    EngineTester() = default;
    void run();

    private:
    std::unique_ptr<Solver> solver;
    std::vector<double> states;
    std::vector<double> applied_forces;
    double drag;
};

#endif 

void EngineTester::run() {
  std::vector<double> s1 =  {1, 1, 5, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 1
  std::vector<double> s2 =  {1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 2
  std::vector<double> s3 =  {2, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 3
  std::vector<double> s4 =  {1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 4
  std::vector<double> s5 =  {1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 5
  std::vector<double> s6 =  {1, 1, 5, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// 6
  std::vector<double> a1 = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // 1
  std::vector<double> a2 = {0.0, 0.0, 0.0, 2, 0.0, 0.0}; // 2
  std::vector<double> a3 = {10.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // 3
  std::vector<double> a4 = {0.0, 0.0, 0.0, 0.0, 0.0, -32.174}; // 4
  std::vector<double> a5 = {0.0, 0.0, 32.174, 0.0, 0.0, -32.174}; // 5
  std::vector<double> a6 =  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};// 6

  std::vector<std::string> f = {"1_test", "2_test", "3_test", "4_test", "5_test", "6_test"};
  std::vector<double> d = {0.0, 0.0, 0.0, 0.0, 0.0, 0.01};
  std::vector<std::vector<double>> s = {s1, s2, s3, s4, s5, s6};
  std::vector<std::vector<double>> a = {a1, a2, a3, a4, a5, a6};

  for(int i = 0; i < 6; i++) {
    solver = std::make_unique<Solver>(s[i], a[i], d[i]);
    solver->update_filename(f[i] + "-e.txt");
    solver->init_integrate('e');
    solver->solve();
    solver->write_to_file();

    solver = std::make_unique<Solver>(s[i], a[i], d[i]);
    solver->update_filename(f[i] + "-r.txt");
    solver->init_integrate('r');
    solver->solve();
    solver->write_to_file();
  }

}

