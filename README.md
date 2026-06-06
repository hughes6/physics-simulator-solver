# Physics Simulator

A C++ physics simulation engine for modeling point-mass motion under external forces, gravity, and linear drag. The simulator supports both Euler and Runge-Kutta 4 (RK4) numerical integration methods and includes automated testing and visualization tools.

---

## Features

* Euler integration
* Runge-Kutta 4 (RK4) integration
* Constant force and acceleration inputs
* Gravity simulation
* Linear air resistance (drag)
* Automated test suite
* Python-based plotting and validation tools

---

## Compilation

```bash
g++ main.cpp -o main
```

---

## Running the Simulator

```bash
./main
```

### Configuration

The integration method and output filename are configured in `main.cpp`.

```cpp
solver.init_integrate('r');      // 'e' = Euler, 'r' = RK4
solver.update_filename("test.txt");
```

---

## Initial State Vector

Parameter 1 is a `std::vector<double>` containing the simulation state.

| Index | Description               |
| ----- | ------------------------- |
| 0     | Mass (m)                  |
| 1     | Time Step (dt)            |
| 2     | Simulation Length         |
| 3-5   | Acceleration (ax, ay, az) |
| 6-8   | Velocity (vx, vy, vz)     |
| 9-11  | Temporary Solver State    |
| 12-14 | Position (x, y, z)        |
| 15-17 | Temporary Solver State    |

Example:

```cpp
std::vector<double> state(18);
```

**Note:** Temporary state values are used internally by the solver and should generally be initialized to zero.

---

## Force Vector

Parameter 2 is a `std::vector<double>` describing applied forces and accelerations.

| Index | Description         |
| ----- | ------------------- |
| 0     | Force X (fx)        |
| 1     | Force Y (fy)        |
| 2     | Force Z (fz)        |
| 3     | Acceleration X (ax) |
| 4     | Acceleration Y (ay) |
| 5     | Acceleration Z (az) |

Example gravity configuration:

```cpp
forces[5] = -32.174;
```

This applies Earth's gravitational acceleration in ft/s² along the Z-axis.

---

## Drag Coefficient

Parameter 3 is a `double` representing the linear air resistance coefficient.

```cpp
double drag_coeff = 0.05;
```

Higher values produce stronger damping effects on velocity.

---

## Testing

The project includes a built-in testing framework.

```cpp
EngineTester tester;
tester.run();
```

After generating test outputs, execute:

```bash
python test.py
```

### Python Test Configuration

Inside `test.py`:

| Variable | Purpose                              |
| -------- | ------------------------------------ |
| populate | Generate test output files           |
| test     | Execute validation tests             |
| remove   | Delete generated files after testing |

---

## Visualization

Simulation output can be visualized using the included plotting utility.

```bash
python plot.py
```

### Requirements

```bash
pip install matplotlib numpy
```

### Plot Configuration

Inside `plot.py`:

| Variable | Purpose                   |
| -------- | ------------------------- |
| filename | Simulation output file    |
| save     | Save generated figures    |
| combined | Generate combined plots   |
| separate | Generate individual plots |

---

## Output Format

Each output row contains:

```text
x y z vx vy vz ax ay az
```

representing position, velocity, and acceleration at each simulation time step.

---

## Physics Model

The simulator solves Newton's Second Law:

F = ma

and supports:

* Constant external forces
* Gravity
* Linear drag
* Numerical integration using Euler or RK4 methods

This project is intended for learning numerical methods, physics simulation, and basic engine development concepts.
