// Main file

#include <iostream>
#include "Simulation.h"
#include "Simulation.cpp"

using namespace std;

// HCP run
// int main(int argc, char *argv[])
// {
//     int nDays = 365;
//     bool insecticideIntervention = false;
//     bool containerIntervention = false;
//     bool netIntervention = false;
//     float sensitivity = 0.990;
//     string outputFile = "data/output/out_" + string(argv[1]) + ".csv";
//     string outputMosquitoFile = "data/output/out_mos_" + string(argv[1]) + ".csv";

//     Simulation model(nDays, insecticideIntervention, containerIntervention, netIntervention, sensitivity, outputFile, outputMosquitoFile);
//     model.simulate();
//     return 0;
// };

// Local run
int main()
{
    int nDays = 360;
    bool insecticideIntervention = false;
    bool containerIntervention = false;
    bool netIntervention = false;
    float sensitivity = 0.0;
    string outputFile = "data/out_test.csv";
    string outputMosquitoFile = "data/out_mos_test.csv";

    Simulation model(nDays, containerIntervention, insecticideIntervention, netIntervention, sensitivity, outputFile, outputMosquitoFile);
    model.simulate();
    return 0;
};