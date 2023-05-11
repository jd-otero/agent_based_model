// Human Class

#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include "Human.h"

using namespace std;

Human::Human(int _id, string _state, int _age, string _gender, int _highEd, float _density, int _sewage, int _gas, int _dayOfInfection, int _currentEnvironment, int _homeEnvironment, int _dailyEnvironment, float _biteRate)
{
    id = _id;
    state = _state;
    age = _age;
    gender = _gender;
    highEd = _highEd;
    density = _density;
    sewage = _sewage;
    gas = _gas;
    positionX = 0;
    positionY = 0;
    homeCoordinates = {};
    dailyCoordinates = {};
    currentEnvironment = _currentEnvironment;
    dayOfInfection = _dayOfInfection;
    viremia = (dayOfInfection < -8) ? true : false;
    biteRate = _biteRate;
    homeEnvironment = _homeEnvironment;
    dailyEnvironment = _dailyEnvironment;
    containerInt = 0;
    netInt = 0;
    insecticideInt = 0;
};

Human::Human(){};

// Change states
void Human::changeToInfected(int _day)
{
    if (state == "S")
    {
        state = "I";
        setDayOfInfection(_day);
    }
};

void Human::changeToRecovered()
{
    state = "R";
};

// Set infection day
void Human::setDayOfInfection(int _day)
{
    if (dayOfInfection == 0)
    {
        dayOfInfection = _day;
    }
};

// Update viremic state (10 days of viremia aprox.)
void Human::updateViremia(int _day)
{
    if (state == "I" && viremia == false) // if not viremia and infected, and infected over 4 days ago turn on viremia
    {
        if (_day - dayOfInfection >= 4 && dayOfInfection != 0)
        {
            viremia = true;
        }
    }
    if (viremia == true)
    {
        if (state == "I" && _day - dayOfInfection > 14)
        {
            changeToRecovered();
            viremia = false;
        }
    }
};

// change environment when moving
void Human::changeEnvironment(int _environmentId)
{
    currentEnvironment = _environmentId;
};

// Set coordinates for daily interaction (work/school)
void Human::setDailyCoordinates(int _positionX, int _positionY)
{
    dailyCoordinates = {_positionX, _positionY};
};

// Set coordinates for home
void Human::setHomeCoordinates(int _positionX, int _positionY)
{
    homeCoordinates = {_positionX, _positionY};
};

// Update position (constant if home or work/school)
void Human::updatePosition(int _environmentId, int _positionX, int _positionY)
{
    if (_environmentId == dailyEnvironment)
    {
        positionX = dailyCoordinates[0];
        positionY = dailyCoordinates[1];
    }
    else if (_environmentId == homeEnvironment)
    {
        positionX = homeCoordinates[0];
        positionY = homeCoordinates[1];
    }
    else
    {
        positionX = _positionX;
        positionY = _positionY;
    }
};

// Bite rate (can change if usses net intervention)
void Human::updateBiteRate(float _biteRate)
{
    biteRate = _biteRate;
};

// Container Intevention
void Human::updateContainerInt(float _density, float _gas, float _sewage, int _environmentCases, int _campaign, float _threshold)
{

    cout << density <<endl;
    float fx = -(-0.726 * (gender == "H") ? 1 : 0 - 4.565 * (age > 20) ? 1 : 0 + -11.354 * highEd + 2.968 * (_density) + -1.679 * _gas + 0.755 * (-_sewage));
    //fx += 2 * (_environmentCases) + 2 * (_campaign);
    float gx = float(1 / (1 + exp(-fx)));
    containerInt = (gx >= _threshold) ? 1 : 0;
};

// Net Intervention
void Human::updateNetInt(float _density, float _gas, float _sewage, int _environmentCases, int _campaign, float _threshold)
{
    float fx = -(-0.726 * (gender == "H") ? 1 : 0 + -4.565 * (age > 20) ? 1 : 0 + -11.354 * highEd + 2.968 * (-_density*1000) + -1.679 * _gas + 0.755 * (-_sewage));
    //fx += 2 * (_environmentCases) + 2 * (_campaign);
    float gx = float(1 / (1 + exp(-fx)));
    containerInt = (gx >= _threshold) ? 1 : 0;
};

// Insecticide Intervention
void Human::updateInsecticideInt(float _density, float _gas, float _sewage, int _environmentCases, int _campaign, float _threshold)
{
    float fx = -(-0.726 * (gender == "H") ? 1 : 0 + -4.565 * (age > 20) ? 1 : 0 + -11.354 * highEd + 2.968 * (-_density*1000) + -1.679 * _gas + 0.755 * (-_sewage));
    //fx += 2 * (_environmentCases) + 2 * (_campaign);
    float gx = float(1 / (1 + exp(-fx)));
    containerInt = (gx >= _threshold) ? 1 : 0;
};
