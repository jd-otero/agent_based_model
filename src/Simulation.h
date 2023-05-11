#ifndef SIMULATION_H
#define SIMULATION_H

// Simulation Class

#include <iostream>
#include <omp.h>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include "Intervention.h"
#include "Intervention.cpp"

using namespace std;
using std::vector;

class Simulation
{
public:
    vector<std::vector<string>> simulationData(string);
    vector<std::vector<float>> generalData(string);
    int weightedRandom(vector<float>);
    void initialize(string, string);
    list<int> deathRate(Environment *, list<int>, int);
    int birthRate(int, Environment *, int);
    void deleteMosquitoes(list<int>, Environment *);
    void addMosquitoes(int, Environment *, int, int);
    list<int> updateMosquitoes(Environment *);
    void updateHumans(int);
    void writeFile(vector<vector<int>>, string);
    void simulate();

    Simulation(int, bool, bool, bool, float, string, string);

private:
    int nDays;
    string humanOutputFile;
    string mosquitoOutputFile;
    map<int, Environment> environments;
    map<int, Human> humans;
    map<int, Mosquito> mosquitoes;
    Movement mover;
    Intervention interventor;
    bool containerIntervention;
    bool insecticideIntervention;
    bool netIntervention;
    float sensitivity;
};

#endif