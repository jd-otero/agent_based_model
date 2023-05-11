#ifndef INTERVENTION_H
#define INTERVENTION_H

// Human Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include "Movement.h"
#include "Movement.cpp"

using namespace std;
using std::vector;

class Intervention
{
public:
    vector<vector<int>> containerIntervened = {};
    vector<vector<int>> netIntervened = {};
    vector<vector<int>> insecticideIntervened = {};

    void updateContainerIntervention(Human *, Environment *, float);
    void updateNetIntervention(Human *, Environment *, float);
    void updateInsecticideIntervention(Human *, Environment *, float);
    void reset();

    Intervention();
};

#endif