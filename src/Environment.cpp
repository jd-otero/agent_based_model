// Environment Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include "Environment.h"

using namespace std;

Environment::Environment(int _id, float _density, int _population, float _gas, float _sewage, float _meanTemp, int _wetDays, float _precipitation, int _daysOver90, float _ndvi, float _elevation, double _birthRate, double _deathRate, float _area)
{
    id = _id;
    density = _density;
    population = _population;
    gas = _gas;
    sewage = _sewage;
    meanTemp = _meanTemp;
    wetDays = _wetDays;
    precipitation = _precipitation;
    daysOver90 = _daysOver90;
    ndvi = _ndvi;
    elevation = _elevation;
    birthRate = _birthRate;
    deathRateAdults = _deathRate;
    deathRateAquatic = _deathRate;
    area = _area;
    width = int(round(sqrt(_area / 1.6) / 22));        // horizontal, 1.6 ratio between v and h, 10m blocks (can be changed)
    length = int(round(sqrt(_area / 1.6) * 1.6 / 22)); // vertical
    list<int> humansInEnvironment;
    list<int> mosquitoesInEnvironment;
    campaignState = 0;
    activeCases = 0;
};

Environment::Environment(){};

// Add and remove humans and mosquitoes
void Environment::addHuman(int _humanId)
{
    humansInEnvironment.push_back(_humanId);
};

void Environment::removeHuman(int _humanId)
{
    humansInEnvironment.remove(_humanId);
};

void Environment::addMosquito(int _mosquitoId)
{
    mosquitoesInEnvironment.push_back(_mosquitoId);
};

void Environment::removeMosquito(int _mosquitoId)
{
    mosquitoesInEnvironment.remove(_mosquitoId);
};

void Environment::changeCampaignState(int campState)
{
    campaignState = campState;
};

// Reset cases count
void Environment::resetCases()
{
    activeCases = 0;
};

// Add case to environment
void Environment::addCases(int cases)
{
    activeCases += cases;
};

// Birth and Death rates for mosquitoes
void Environment::updateDeathRateAdults(float _temperature, int _days_ov_90)
{
    double temperature = (double)(_temperature);
    double days_ov_90 = (double)(_days_ov_90);
    deathRateAdults = (double)(0.8692 - 0.159 * temperature + 0.01116 * pow(temperature, 2) - 0.0003409 * pow(temperature, 3) + 0.000003804 * pow(temperature, 4) + 0.027 + 0.047 * days_ov_90);
};

void Environment::updateDeathRateAquatic(float _temperature, int _days_ov_90)
{
    double temperature = (double)(_temperature);
    double days_ov_90 = (double)(_days_ov_90);
    deathRateAquatic = (double)(2.13 - 0.3797 * temperature + 0.02457 * pow(temperature, 2) - 0.0006778 * pow(temperature, 3) + 0.000006792 * pow(temperature, 4) + 0.026 + 0.03 * _days_ov_90);
};

void Environment::updateBirthRate(float _temperature, int _days_ov_90)
{
    double temperature = (double)(_temperature);
    double days_ov_90 = (double)(_days_ov_90);
    birthRate = (double)(-0.000016 * pow(temperature, 3) + 0.00117114 * pow(temperature, 2) - 0.024371 * temperature + 0.186171 + 0.004 + 0.018 * _days_ov_90);
};
