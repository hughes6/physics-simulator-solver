# Physics Simulator

A simple physics simulator in C++ using Euler and Runge-Kutta 4 (RK4) integration methods.

## Compilation

g++ main.cpp -o main

## Usage

./main

### Default behavior
Configure integration method in main on line 20:   solver.init_integrate('r');
Set file name in main on line 23:   solver.update_filename("test.txt");

Pass in vector<double> of initial states to solver as parameter 1
[0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] [16] [17]
 m  dt len   ax  ay  az  vx  vy  vz  0   0    0    x    y    z    0    0    0v
len is simulation length, 0's are just temporary state(t+1) for solver

Pass in vector<double> of force/accelerations to solver as parameter 2
[0] [1] [2] [3] [4] [5]
fx  fy  fz  ax  ay  az
these are constant forces, pass in az = -32.174 for gravity on

Pass in double of air resistance coefficient (linear) to solver as parameter 3

Built with testing functionality for testing functions

### Test cases
Run tester with EngineTester t; and t.run() 
then run python test.py to test cases 1-6, seen in engine tester class

Inputs in python tester - populate: set to true to generate files
                        - test: set to true to run tests
                        - remove: set to true to deleta files after

## Graphing & Testing

After simulation, you can visualize the results or validate the solver:

python plot.py      (requires matplotlib, numpy)

Inputs in python plotter - filename: set to name of file output to plot
                         - save: set to true to save the plots to current dir
                         - combined: set to true to generate combined plot
                         - separate: set to true to generate separate plots
                         - separate and combined: set to true to generate both plots

## Notes
- The simulation solves Newton's second law for a point mass under constant forces, drag, and gravity.
- Output columns: x y z vx vy vz ax ay az at each time step.