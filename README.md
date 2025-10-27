# 🔥 Parallel_2D_Heat_Eqn_Solver

## 📘 Overview
This project implements a **2D Heat Equation Solver** in **C++** using **OpenMP** for parallelization.  
It simulates heat diffusion over a square plate by numerically solving the **heat equation** using the **finite difference method**.  

The computed temperature distribution is saved to output files, which are then visualized using a **Python script** that employs **NumPy** and **Matplotlib**.

---

## 🧮 Mathematical Model

The 2D heat equation is given by:

\[
\frac{\partial u}{\partial t} = \alpha \left( 
\frac{\partial^2 u}{\partial x^2} + 
\frac{\partial^2 u}{\partial y^2} 
\right)
\]

where:
- \( u(x, y, t) \) = temperature at location (x, y) and time t  
- \( \alpha \) = thermal diffusivity constant  

---

## ⚙️ Features

✅ Serial and Parallel (OpenMP) implementations  
✅ Adjustable grid size, time step, and number of iterations  
✅ Measures and compares serial and parallel execution times  
✅ Generates `.dat` files for visualization  
✅ Python script for graphical representation using Matplotlib  

---

## 🧩 Implementation Details

| Component | Description |
|------------|--------------|
| **Language** | C++ |
| **Parallel Library** | OpenMP |
| **Visualization** | Python (NumPy, Matplotlib) |
| **Boundary Conditions** | Fixed zero temperature on all edges |
| **Initial Condition** | Circular hot region in the center |

---

## 🧱 Program Parameters

| Parameter | Description | Default |
|------------|--------------|----------|
| `nx`, `ny` | Number of grid points | 100 × 100 |
| `Lx`, `Ly` | Plate dimensions | 1.0 × 1.0 |
| `alpha` | Thermal diffusivity | 0.01 |
| `dt` | Time step | 0.00001 |
| `nsteps` | Number of time steps | 1000 |
| `num_threads` | OpenMP threads | 4 |

---

## 🛠️ Compilation & Execution

### **1. Compile the code**
Make sure your compiler supports **OpenMP** (e.g. `g++`).

```bash
g++ -fopenmp parallel_2d_heat_eqn_solver.cpp -o heat_solver
