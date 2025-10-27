🔥 Parallel_2D_Heat_Eqn_Solver
📘 Overview

This project implements a 2D Heat Equation Solver in C++ using OpenMP for parallelization.
It simulates heat diffusion over a square plate by numerically solving the heat equation using the finite difference method.

The computed temperature distribution is saved to output files, which are then visualized using a Python script that employs NumPy and Matplotlib.

🧮 Mathematical Model

The 2D heat equation is given by:

∂
𝑢
∂
𝑡
=
𝛼
(
∂
2
𝑢
∂
𝑥
2
+
∂
2
𝑢
∂
𝑦
2
)
∂t
∂u
	​

=α(
∂x
2
∂
2
u
	​

+
∂y
2
∂
2
u
	​

)

where:

𝑢
(
𝑥
,
𝑦
,
𝑡
)
u(x,y,t) = temperature at location (x, y) and time t

𝛼
α = thermal diffusivity constant

⚙️ Features

✅ Serial and Parallel (OpenMP) implementations
✅ Adjustable grid size, time step, and number of iterations
✅ Measures and compares serial and parallel execution times
✅ Generates .dat files for visualization
✅ Python script for graphical representation using Matplotlib

🧩 Implementation Details
Component	Description
Language	C++
Parallel Library	OpenMP
Visualization	Python (NumPy, Matplotlib)
Boundary Conditions	Fixed zero temperature on all edges
Initial Condition	Circular hot region in the center
🧱 Program Parameters
Parameter	Description	Default
nx, ny	Number of grid points	100 × 100
Lx, Ly	Plate dimensions	1.0 × 1.0
alpha	Thermal diffusivity	0.01
dt	Time step	0.00001
nsteps	Number of time steps	1000
num_threads	OpenMP threads	4
🛠️ Compilation & Execution
1. Compile the code

Make sure your compiler supports OpenMP (e.g. g++).

g++ -fopenmp parallel_2d_heat_eqn_solver.cpp -o heat_solver

2. Run the program
./heat_solver


You’ll see output similar to:

2D Heat Equation Solver
Authors
1. Abhinandh Rajeev (2023BCS0074)
2. Jugal Kakkat (2023BCS0041)
========================================

=== SERIAL IMPLEMENTATION ===
Grid size: 100 x 100
Serial execution time: 1.243 seconds
Results saved to heat_solution_serial.dat

=== PARALLEL IMPLEMENTATION ===
Grid size: 100 x 100
Number of threads: 4
Parallel execution time: 0.392 seconds
Results saved to heat_solution_parallel.dat

📊 Visualization (Python)

After running the solver, you’ll have .dat files that contain temperature values.
You can visualize them using the following Python script:

import numpy as np
import matplotlib.pyplot as plt

# Load data
data = np.loadtxt("heat_solution_parallel.dat")
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]

# Reshape data
n = int(np.sqrt(len(x)))
X = x.reshape(n, n)
Y = y.reshape(n, n)
Z = z.reshape(n, n)

# Plot
plt.figure(figsize=(6,5))
plt.contourf(X, Y, Z, cmap='hot')
plt.colorbar(label='Temperature (°C)')
plt.title('2D Heat Distribution (Parallel)')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()

⚡ Speedup Analysis

You can calculate speedup using:

Speedup
=
𝑇
𝑠
𝑒
𝑟
𝑖
𝑎
𝑙
𝑇
𝑝
𝑎
𝑟
𝑎
𝑙
𝑙
𝑒
𝑙
Speedup=
T
parallel
	​

T
serial
	​

	​


For example, if:

Serial time = 1.243 s

Parallel time = 0.392 s

Then:

Speedup
=
1.243
0.392
=
3.17
Speedup=
0.392
1.243
	​

=3.17

You can visualize Speedup vs Grid Size in Python:

import matplotlib.pyplot as plt

grid_size = [50, 100, 300, 500]
speedup = [0.550, 1.555, 2.377, 2.994]

plt.figure(figsize=(8,5))
plt.plot(grid_size, speedup, marker='o', color='b', linewidth=2)
plt.title('Speedup vs Grid Size')
plt.xlabel('Grid Size')
plt.ylabel('Speedup')
plt.grid(True)
plt.show()

📁 Output Files
File Name	Description
heat_solution_serial.dat	Results from serial version
heat_solution_parallel.dat	Results from parallel version

Each file contains columns:

x_coordinate   y_coordinate   temperature_value

👨‍💻 Authors

Abhinandh Rajeev
 — 2023BCS0074

Jugal Kakkat
 — 2023BCS0041

📚 References

OpenMP Documentation — https://www.openmp.org

Finite Difference Methods for Heat Equation — MIT OCW 18.336

Matplotlib Documentation — https://matplotlib.org
