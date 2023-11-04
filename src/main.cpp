#include <omp.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "vector.hpp"

using namespace std;

#define deltaT 0.05
#define G 6.6743e-11
int nBodies, nCycles, nThreads;
double *masses;
Point *pos;
Vector *acc, *vel;

ofstream fout;

void initialize(string filename) {
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Error: Could not open '" << filename << "'\n";
        exit(0);
    }

    fin >> nBodies >> nCycles;

    masses = new double[nBodies];
    pos = new Point[nBodies];
    acc = new Vector[nBodies];
    vel = new Vector[nBodies];

    for (int i = 0; i < nBodies; ++i) {
        fin >> masses[i];
        fin >> pos[i].x >> pos[i].y;
        fin >> vel[i].x >> vel[i].y;
    }

    fin.close();
}

void solve_serial() {
    for (int cycle = 0; cycle < nCycles; ++cycle) {
        for (int i = 0; i < nBodies; ++i) {
            for (int j = 0; j < nBodies; ++j) {
                if (i != j)
                    acc[i] += G * masses[j] / pow(max(1e-6, !(pos[i] - pos[j])), 3) * (pos[j] - pos[i]);
            }
        }

        for (int i = 0; i < nBodies; ++i) {
            pos[i] += deltaT * vel[i];
            vel[i] += deltaT * acc[i];
            acc[i] = 0;
        }

        fout << deltaT * (cycle + 1);
        for (int i = 0; i < nBodies; ++i)
            fout << ',' << pos[i].x << ',' << pos[i].y;
        fout << '\n';
    }
}

void solve_parallel() {
    const int step = ceil((double)nBodies / nThreads);

#pragma omp parallel num_threads(nThreads)
    {
        int thread = omp_get_thread_num();
        int l = thread * step;
        int r = min(nBodies, l + step);

        // #pragma omp critical
        //         cout << "Thread " << thread << ": " << l << ' ' << r << '\n';

        for (int cycle = 0; cycle < nCycles; ++cycle) {
            for (int i = l; i < r; ++i) {
                for (int j = i + 1; j < nBodies; ++j) {
                    Vector force = G / pow(max(1e-6, !(pos[i] - pos[j])), 3) * (pos[j] - pos[i]);
#pragma omp atomic
                    acc[i].x += force.x * masses[j];
#pragma omp atomic
                    acc[i].y += force.y * masses[j];
#pragma omp atomic
                    acc[j].x -= force.x * masses[i];
#pragma omp atomic
                    acc[j].y -= force.y * masses[i];
                }
            }

#pragma omp barrier

            for (int i = l; i < r; ++i) {
                pos[i] += deltaT * vel[i];
                vel[i] += deltaT * acc[i];
                acc[i] = 0;
            }

#pragma omp barrier
#pragma omp single nowait
            {
                fout << deltaT * (cycle + 1);
                for (int i = 0; i < nBodies; ++i)
                    fout << ',' << pos[i].x << ',' << pos[i].y;
                fout << '\n';
            }
        }
    }
}

int main(int argC, char *argV[]) {
    // string input_file = "../data/input.txt";
    // string output_file = "../data/output.csv";
    // nThreads = 8;

    if (argC != 4) {
        cout << "Wrong number of arguments\n";
        return 0;
    }
    string input_file = argV[1];
    string output_file = argV[2];
    nThreads = stoi(argV[3]);

    initialize(input_file);

    ios_base::sync_with_stdio(false);

    fout = ofstream(output_file);
    if (!fout.is_open()) {
        cout << "Error: Could not open '" << output_file << "'\n";
        return 0;
    }

    fout.precision(6);
    fout.setf(ios_base::fixed | ios_base::right);

    fout << "masses";
    for (int i = 0; i < nBodies; ++i) {
        fout << ',' << masses[i];
    }
    fout << '\n';

    double wall_start = omp_get_wtime();
    double cpu_start = clock();

    if (nThreads == 1)
        solve_serial();
    else
        solve_parallel();

    double wall_end = omp_get_wtime();
    double cpu_end = clock();

    cout << "Wall: " << wall_end - wall_start << " s.\n";
    cout << "CPU:  " << (cpu_end - cpu_start) / 1000000 << " s.\n";

    fout.close();
    return 0;
}