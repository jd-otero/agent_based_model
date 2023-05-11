#ifndef MOVEMENT_H
#define MOVEMENT_H

// Movement Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include "Human.h"
#include "Human.cpp"
#include "Mosquito.h"
#include "Mosquito.cpp"
#include "Environment.h"
#include "Environment.cpp"

using namespace std;
using std::vector;

class Movement
{
public:
    void moveHuman(Human *, Environment *, Environment *);
    void moveMosquito(Mosquito *, Environment *);
    bool checkProximity(Human *, Mosquito *);
    Movement();
};

#endif