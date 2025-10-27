# 🔥 Parallel_2D_Heat_Eqn_Solver

## 📘 Overview
This project implements a **2D Heat Equation Solver** in **C++** using **OpenMP** for parallelization.  
It simulates heat diffusion over a square plate by numerically solving the **heat equation** using the **finite difference method**.  

The computed temperature distribution is saved to output files, which are then visualized using a **Python script** that employs **NumPy** and **Matplotlib**.

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

## How it Works

The solver uses the finite difference method to discretize the 2D heat equation:

$$
\frac{\partial u}{\partial t} = \alpha \left(\frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2}\right)
$$

where \( u(x, y, t) \) is the temperature at position \( (x, y) \) and time \( t \), and \( \alpha \) is the thermal diffusivity.

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
g++ -fopenmp report_2d_pde1.cpp -o heat_solver
```
### 2.Run the program
```bash
./heat_solver
```
### 3.View results
First intstall the necessary dependencies in python using the command, it is reccomended to install them in a virtual environment
``` bash
python -m venv .venv
```
Activate the virtual environment (Git Bash)
```bash
source .venv/Scripts/activate
```
Install the dependencies
```bash
python -m pip install matplotlib
python -m pip install numpy
```
To View the results we have to run the python file, which whill take the ".dat" file as input and give us a graphicacl representation of the result
```bash
python plot_dat.py --no-show
```
Now we have the result of the parallel and serial methods in two separate .png files respectively
