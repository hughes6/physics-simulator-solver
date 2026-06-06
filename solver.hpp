#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "data.hpp" //struct for input data

struct Solver {
public:
  Solver() = default;
  Solver(std::vector<double> x, std::vector<double> y, double z) : data(x, y, z) {integrator = 'e';}
  void init_integrate(char input);
  double truncate(double value, int decimals);
  void euler_integrate();
  double euler_solve();
  void rk_integrate(std::vector<double>& mid_states);
  double rk_solve(std::vector<double>& mid_states);
  void solve();
  void print_result();
  void write_to_file();
  void update_filename(std::string st);

private:
  Data data;
  char integrator; //e is euler  r is rk4
};

#endif

void Solver::init_integrate(char input) {
  if(input != 'r' || input != 'e') {
    // call solverexception
  }
  std::string method = (input == 'r') ? "rk4" : "euler"; 
  std::cout << "Integration method set to: " << method << "\n";
}

double Solver::truncate(double value, int decimals) {
  double multiplier = std::pow(10.0, decimals);
  return std::trunc(value * multiplier) / multiplier;
}

void Solver::euler_integrate(){
  // x(t+1) = x(t) + del_t*vx(t)
  data.states[15] = truncate(data.states[12] + data.states[1]*data.states[6], 5);
  data.states[16] = truncate(data.states[13] + data.states[1]*data.states[7], 5);
  data.states[17] = truncate(data.states[14] + data.states[1]*data.states[8], 5);
  data.states[9]  = truncate(data.states[6] + data.states[1]*data.states[3], 5);
  data.states[10] = truncate(data.states[7] + data.states[1]*data.states[4], 5);  
  data.states[11] = truncate(data.states[8] + data.states[1]*data.states[5], 5); 
  data.states[12] = data.states[15]; 
  data.states[13] = data.states[16]; 
  data.states[14] = data.states[17]; 
  data.states[6]  = data.states[9];  
  data.states[7]  = data.states[10]; 
  data.states[8]  = data.states[11]; 
}

double Solver::euler_solve(){
  auto app_force = data.applied_forces;
  double F_x = 0, F_y = 0, F_z = 0;
  // const force - linear drag
  F_x = truncate(app_force[0] - data.drag*data.states[6], 5); 
  F_y = truncate(app_force[1] - data.drag*data.states[7], 5);
  F_z = truncate(app_force[2] - data.drag*data.states[8], 5); 
  // ax=Fx/m
  data.states[3] = truncate(app_force[3] + F_x/data.states[0], 5);
  data.states[4] = truncate(app_force[4] + F_y/data.states[0], 5);
  data.states[5] = truncate(app_force[5] + F_z/data.states[0], 5);
}

void Solver::rk_integrate(std::vector<double>& mid_states){
  std::vector<double> k(24);
  double dt = data.states[1];

  // ---- K1 ----// k1 = dt * vx; k1v = dt * ax
  double k1x  = dt * data.states[6],  k1vx = dt * data.states[3];
  double k1y  = dt * data.states[7],  k1vy = dt * data.states[4];
  double k1z  = dt * data.states[8],  k1vz = dt * data.states[5];

  // ---- K2 ---- (evaluate at t + dt/2 using k1 slopes)
  mid_states[0] = data.states[6] + 0.5*k1vx; 
  mid_states[2] = data.states[7] + 0.5*k1vy; 
  mid_states[4] = data.states[8] + 0.5*k1vz; 
  rk_solve(mid_states);
  double k2x  = dt * mid_states[0],  k2vx = dt * mid_states[1];
  double k2y  = dt * mid_states[2],  k2vy = dt * mid_states[3];
  double k2z  = dt * mid_states[4],  k2vz = dt * mid_states[5];

  // ---- K3 ---- (evaluate at t + dt/2 using k2 slopes)
  mid_states[0] = data.states[6] + 0.5*k2vx; 
  mid_states[2] = data.states[7] + 0.5*k2vy; 
  mid_states[4] = data.states[8] + 0.5*k2vz; 
  rk_solve(mid_states);
  double k3x  = dt * mid_states[0],  k3vx = dt * mid_states[1];
  double k3y  = dt * mid_states[2],  k3vy = dt * mid_states[3];
  double k3z  = dt * mid_states[4],  k3vz = dt * mid_states[5];

  // ---- K4 ---- (evaluate at t + dt using k3 slopes)
  mid_states[0] = data.states[6] + k3vx;
  mid_states[2] = data.states[7] + k3vy; 
  mid_states[4] = data.states[8] + k3vz; 
  rk_solve(mid_states);
  double k4x  = dt * mid_states[0],  k4vx = dt * mid_states[1];
  double k4y  = dt * mid_states[2],  k4vy = dt * mid_states[3];
  double k4z  = dt * mid_states[4],  k4vz = dt * mid_states[5];

  //x = k1 + 2k2 + 2k3 + k4
  data.states[12] = data.states[12] + (1.0/6.0) * (k1x  + 2.0*k2x  + 2.0*k3x  + k4x);
  data.states[6]  = data.states[6]  + (1.0/6.0) * (k1vx + 2.0*k2vx + 2.0*k3vx + k4vx);
  data.states[13] = data.states[13] + (1.0/6.0) * (k1y  + 2.0*k2y  + 2.0*k3y  + k4y) ;
  data.states[7]  = data.states[7]  + (1.0/6.0) * (k1vy + 2.0*k2vy + 2.0*k3vy + k4vy);
  data.states[14] = data.states[14] + (1.0/6.0) * (k1z  + 2.0*k2z  + 2.0*k3z  + k4z); 
  data.states[8]  = data.states[8]  + (1.0/6.0) * (k1vz + 2.0*k2vz + 2.0*k3vz + k4vz);

  mid_states[0] = data.states[6]; 
  mid_states[2] = data.states[7]; 
  mid_states[4] = data.states[8]; 
  rk_solve(mid_states);
  data.states[3] = mid_states[1]; 
  data.states[4] = mid_states[3]; 
  data.states[5] = mid_states[5]; 
}

double Solver::rk_solve(std::vector<double>& mid_states){
  auto a = data.applied_forces;
  double F_x = 0, F_y = 0, F_z = 0;
  F_x = a[0] - data.drag*mid_states[0]; // const - drag * v(x)
  mid_states[1] = truncate(a[3] + F_x/data.states[0], 5);// ax(t) = Fx/m

  F_y = a[1] - data.drag*mid_states[2];
  mid_states[3] = truncate(a[4] + F_y/data.states[0], 5);

  F_z = a[2] - data.drag*mid_states[4];
  mid_states[5] = truncate(a[5] + F_z/data.states[0], 5);
}

void Solver::solve() {
  auto app_force = data.applied_forces;
  double time = data.states[2], dt = data.states[1];
  int count = 0;
  if(integrator == 'r') {
    std::vector<double> mid_states(6);
    for(double i = 0; i < time; i += dt) {
      std::cout << "loop iter: " << count << "\n";
      data.insert(count, 1, data.states[12]); //x
      data.insert(count, 2, data.states[13]); //y
      data.insert(count, 3, data.states[14]); //z
      data.insert(count, 4, data.states[6]);  //vx
      data.insert(count, 5, data.states[7]);  //vy
      data.insert(count, 6, data.states[8]);  //vz
      data.insert(count, 7, data.states[3]);  //ax
      data.insert(count, 8, data.states[4]);  //ay
      data.insert(count, 9, data.states[5]);  //az
      // [0] [1] [2] [3] [4] [5] [6] [7] [8] t(0)
      //  x   y   z   vx  vy  vz  ax  ay  az 
      rk_integrate(mid_states);
      count ++;
    }
  } else if(integrator == 'e') {
    for(double i = 0; i < time; i += dt) {
      data.insert(count, 0, data.states[12]); //x
      data.insert(count, 1, data.states[13]); //y
      data.insert(count, 2, data.states[14]); //z
      data.insert(count, 3, data.states[6]);  //vx
      data.insert(count, 4, data.states[7]);  //vy
      data.insert(count, 5, data.states[8]);  //vz
      data.insert(count, 6, data.states[3]);  //ax
      data.insert(count, 7, data.states[4]);  //ay
      data.insert(count, 8, data.states[5]);  //az
    
      euler_solve(); // solve for accel
      euler_integrate();   // update v & x
      count ++;
    }
  }
}

void Solver::print_result() {
  auto t = data.states[1];
  double cur_time = 0;
  int n = 7, m = 5;
  for(int i =0; i < data.results.size() / 9; i++) {
      std::cout << "time:" << std::left << std::setw(n) << cur_time << " x:" << std::left << std::setprecision(m) << std::setw(n) << data.at(i, 0) << "  vx:" << std::left << std::setprecision(m) << std::setw(n) << data.at(i, 3) << "  ax:" << std::left << std::setprecision(m) << std::setw(n) << data.at(i, 6) << "  y:" << std::left <<  std::setprecision(m) <<std::setw(n) << data.at(i, 1) << "  vy:" << std::left <<  std::setprecision(m) <<std::setw(n) << data.at(i, 4) << "  ay:" << std::left <<  std::setprecision(m) <<std::setw(n) << data.at(i, 7) <<"  z:" << std::left <<    std::setprecision(m) << std::setw(n) << data.at(i, 2) << "  vz:" << std::left <<  std::setprecision(m) <<std::setw(n) << data.at(i, 5) << "  az:" << std::left <<  std::setprecision(m) << std::setw(n) << data.at(i, 8) << std::endl;
    cur_time += t;
  }
}

void Solver::write_to_file() {
  auto t = data.states[1];
  auto f = data.filename;
  std::ofstream fout(f);
  if (!fout.is_open()) {
    std::cerr << "Failed to open " << f << ".\n";
    return;
  }
  int m = 3;
  double cur_time = 0;
  fout << "time x y z vx vy vz ax ay az\n";
  for(int i = 0; i < data.results.size() / 9; i++) {
    fout << std::setprecision(m) << cur_time << ", " 
      << std::setprecision(m) << data.at(i, 0) << ", "  // x
      << std::setprecision(m) << data.at(i, 1) << ", "  // y
      << std::setprecision(m) << data.at(i, 2) << ", "  // z
      << std::setprecision(m) << data.at(i, 3) << ", "  // vx
      << std::setprecision(m) << data.at(i, 4) << ", "  // vy
      << std::setprecision(m) << data.at(i, 5) << ", "  // vz
      << std::setprecision(m) << data.at(i, 6) << ", "  // ax
      << std::setprecision(m) << data.at(i, 7) << ", "  // ay
      << std::setprecision(m) << data.at(i, 8) << "\n"; // az
    cur_time += t;
}
  fout.close();
}

void Solver::update_filename(std::string st) {
  data.filename = st;
  std::cout << "Filename updated to " << st << "\n";
}