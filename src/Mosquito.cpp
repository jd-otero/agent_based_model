// Mosquito Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <time.h>
#include "Mosquito.h"

using namespace std;
using std::vector;

// Random numbers
std::random_device rd;
std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));

Mosquito::Mosquito(int _id, bool _infected, int _age, int _positionX, int _positionY, int _currentEnvironment, float _developmentRate, int _lifespan)
{
    id = _id;
    infected = _infected;
    age = _age;
    positionX = _positionX;
    positionY = _positionY;
    currentEnvironment = _currentEnvironment;
    std::uniform_int_distribution<> dayOfInf(-10, 0);
    dayOfInfection = (_infected) ? dayOfInf(gen) : 0;
    numberOfBites = 0;
    neededBites = 100;
    maxBitesPerDay = 4;
    bitesToday = 0;
    alive = true;
    adult = (_age * _developmentRate >= 1) ? true : false;
    lifespan = _lifespan;
    developmentRate = _developmentRate;
};

Mosquito::Mosquito(){};

Mosquito::~Mosquito(){};

// Mosquito bite
bool Mosquito::bite(float _biteProbability)
{
    bool output = false;
    if (adult)
    {
        if (numberOfBites <= neededBites && bitesToday <= maxBitesPerDay)
        {
            std::uniform_int_distribution<> biteProb(0, 1000);
            int temp = biteProb(gen);
            if (temp < _biteProbability * 1000)
            {
                // if bites, update bite count
                updateNumberOfBites();
                output = true;
            }
        }
    }
    return output;
};

// Is bite infecting? (Human to Mosquito)
bool Mosquito::infectingBite(float _infectingProb, int _day)
{
    bool output = false;
    if (dayOfInfection != 0 && _day - dayOfInfection > 5)
    {
        std::uniform_int_distribution<> infectProb(0, 1000);
        output = (infectProb(gen) <= _infectingProb * 1000); // rate
    }
    return output;
};

// Iss bite infectious? (Mosquito to Human)
bool Mosquito::infectiousBite(float _infectiousProb)
{
    std::uniform_int_distribution<> infectProb(0, 1000);
    return (infectProb(gen) <= _infectiousProb * 1000); // rate
};

// Change state
void Mosquito::changeToInfected(int _day)
{
    dayOfInfection = _day;
    infected = true;
};

// Update age (die if older than lifespan)
void Mosquito::updateAge()
{
    bitesToday = 0;
    age++;
    if (developmentRate * age >= 1)
    {
        adult = true;
    }
    if (age >= lifespan)
    {
        die();
    }
};

// Change alive state
void Mosquito::die()
{
    alive = false;
};

// Movement
void Mosquito::move(int _newX, int _newY)
{
    positionX = _newX;
    positionY = _newY;
};

// Bite count
void Mosquito::updateNumberOfBites()
{
    bitesToday++;
    numberOfBites++;
};
