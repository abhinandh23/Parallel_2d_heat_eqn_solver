#include <bits/stdc++.h>
#include <cmath>
#include <omp.h>
#include <fstream>
using namespace std;
// initialize the temperature values
void initialize(vector<vector<double>>& u, int nx, int ny) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            u[i][j] = 0.0;
        }
    }
    
    // Hot center region
    int cx = nx / 2;
    int cy = ny / 2;
    int radius = nx / 10;
    
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            if ((i - cx) * (i - cx) + (j - cy) * (j - cy) <= radius * radius) {
                u[i][j] = 100.0;
            }
        }
    }
}

// apply boundary conditions
void applyBoundaryConditions(vector<vector<double>>& u, int nx, int ny) {
    for (int j = 0; j < ny; j++) {
        u[0][j] = 0.0;
        u[nx-1][j] = 0.0;
    }
    
    for (int i = 0; i < nx; i++) {
        u[i][0] = 0.0;
        u[i][ny-1] = 0.0;
    }
}

// SERIAL method
void solveSerial(int nx, int ny, double dx, double dy, 
                 double alpha, double dt, int nsteps) {
    
    vector<vector<double>> u(nx, vector<double>(ny));
    vector<vector<double>> u_new(nx, vector<double>(ny));
    
    initialize(u, nx, ny);
    applyBoundaryConditions(u, nx, ny);
    
    double rx = alpha * dt / (dx * dx);
    double ry = alpha * dt / (dy * dy);
    
    cout << "\n=== SERIAL IMPLEMENTATION ===" << endl;
    cout << "Grid size: " << nx << " x " << ny << endl;
    
    double start_time = omp_get_wtime();
    
    // Time stepping loop
    for (int n = 0; n < nsteps; n++) {
        // Update interior points
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                u_new[i][j] = u[i][j] + 
                              rx * (u[i+1][j] - 2*u[i][j] + u[i-1][j]) +
                              ry * (u[i][j+1] - 2*u[i][j] + u[i][j-1]);
            }
        }
        
        // Copy back
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                u[i][j] = u_new[i][j];
            }
        }
        
        applyBoundaryConditions(u, nx, ny);
        

    }
    
    double end_time = omp_get_wtime();
    double serial_time = end_time - start_time;
    
    cout << "Serial execution time: " << serial_time << " seconds" << endl;
    
    // Save result
    ofstream outfile("heat_solution_serial.dat");
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            outfile << i * dx << " " << j * dy << " " << u[i][j] << endl;
        }
        outfile << endl;
    }
    outfile.close();
    cout << "Results saved to heat_solution_serial.dat" << endl;
}

// PARALLEL Implementation with OpenMP
void solveParallel(int nx, int ny, double dx, double dy, 
                   double alpha, double dt, int nsteps, int num_threads) {
    
    omp_set_num_threads(num_threads);
    
    vector<vector<double>> u(nx, vector<double>(ny));
    vector<vector<double>> u_new(nx, vector<double>(ny));
    
    initialize(u, nx, ny);
    applyBoundaryConditions(u, nx, ny);
    
    double rx = alpha * dt / (dx * dx);
    double ry = alpha * dt / (dy * dy);
    
    cout << "\n=== PARALLEL IMPLEMENTATION ===" << endl;
    cout << "Grid size: " << nx << " x " << ny << endl;
    cout << "Number of threads: " << num_threads << endl;
    
    double start_time = omp_get_wtime();
    
    // Time stepping loop
    for (int n = 0; n < nsteps; n++) {
        // Update interior points in parallel
        #pragma omp parallel for collapse(2) schedule(static)
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                u_new[i][j] = u[i][j] + 
                              rx * (u[i+1][j] - 2*u[i][j] + u[i-1][j]) +
                              ry * (u[i][j+1] - 2*u[i][j] + u[i][j-1]);
            }
        }
        
        // Copy back in parallel
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                u[i][j] = u_new[i][j];
            }
        }
        
        applyBoundaryConditions(u, nx, ny);
        
    
    }
    
    double end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    
    cout << "Parallel execution time: " << parallel_time << " seconds" << endl;
    
    // Saveing result
    ofstream outfile("heat_solution_parallel.dat");
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            outfile << i * dx << " " << j * dy << " " << u[i][j] << endl;
        }
        outfile << endl;
    }
    outfile.close();
    cout << "Results saved to heat_solution_parallel.dat" << endl;
}


int main() {
    //parameters
    int nx = 100;        // Grid points in x
    int ny = 100;        // Grid points in y
    double Lx = 1.0;     // Domain length in x
    double Ly = 1.0;     // Domain length in y
    double dx = Lx / (nx - 1);
    double dy = Ly / (ny - 1);
    double alpha = 0.01; // Thermal diffusivity
    double dt = 0.00001;  // Time step
    int nsteps = 1000;     // Number of time steps
    
    // Number of threads for parallel version
    int num_threads = 4;  
    

    cout << "2D Heat Equation Solver" << endl;
    cout<<"Authors"<<endl;
        cout<<"1. Abhinandh Rajeev (2023BCS0074)"<<endl;
        cout<<"2. Jugal Kakkat (2023BCS0041)"<<endl;
    cout << "========================================" << endl;
    
    // Run serial version
    solveSerial(nx, ny, dx, dy, alpha, dt, nsteps);
    
    // Run parallel version
    solveParallel(nx, ny, dx, dy, alpha, dt, nsteps, num_threads);

    
    return 0;
}