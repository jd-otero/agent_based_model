
#include <iostream>
#include <cstdlib>
#include "Intervention.h"

using namespace std;

Intervention::Intervention()
{
    list<vector<int>> containerIntervened = {};
    list<vector<int>> netIntervened = {};
    list<vector<int>> insecticideIntervened = {};
};

// Update Interventions
void Intervention::updateContainerIntervention(Human *_human, Environment *_environment, float _threshold)
{
    float density = _human->getDensity();
    float gas = _human->getGas();
    int sewage = _human->getSewage();
    int cases = _environment->getActiveCases();
    int campaign = _environment->getCampaignState();
    _human->updateContainerInt(density, gas, sewage, cases, campaign, _threshold);
    if (_human->getContainerInt() == 1)
    {
        int env = _environment->getId();
        int posX = _human->getPositionX();
        int posY = _human->getPositionY();
        vector<int> intervenedArea = {env, posX, posY};
        containerIntervened.push_back(intervenedArea);
    }
};

void Intervention::updateNetIntervention(Human *_human, Environment *_environment, float _threshold)
{
    float density = _human->getDensity();
    float gas = _human->getGas();
    int sewage = _human->getSewage();
    int cases = _environment->getActiveCases();
    int campaign = _environment->getCampaignState();
    _human->updateNetInt(density, gas, sewage, cases, campaign, _threshold);
    if (_human->getNetInt() == 1)
    {
        int env = _environment->getId();
        int posX = _human->getPositionX();
        int posY = _human->getPositionY();
        vector<int> intervenedArea = {env, posX, posY};
        netIntervened.push_back(intervenedArea);
        _human->updateBiteRate(0.45);
    }
};

void Intervention::updateInsecticideIntervention(Human *_human, Environment *_environment, float _threshold)
{
    float density = _human->getDensity();
    float gas = _human->getGas();
    int sewage = _human->getSewage();
    int cases = _environment->getActiveCases();
    int campaign = _environment->getCampaignState();
    _human->updateInsecticideInt(density, gas, sewage, cases, campaign, _threshold);
    if (_human->getInsecticideInt() == 1)
    {
        int env = _environment->getId();
        int posX = _human->getPositionX();
        int posY = _human->getPositionY();
        vector<int> intervenedArea = {env, posX, posY};
        insecticideIntervened.push_back(intervenedArea);
    }
};

void Intervention::reset()
{
    containerIntervened = {};
    netIntervened = {};
    insecticideIntervened = {};
};