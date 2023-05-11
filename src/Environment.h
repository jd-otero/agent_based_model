#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// Environment Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <list>
#include <cmath>

using namespace std;
using std::vector;

class Environment
{
public:
    int getId() { return id; };
    float getDensity() { return density; };
    int getPopulation() { return population; };
    float getGas() { return gas; };
    float getSewage() { return sewage; };
    float getMeanTemp() { return meanTemp; };
    int getWetDays() { return wetDays; };
    float getPrecipitation() { return precipitation; };
    int getDaysOver90() { return daysOver90; };
    float getNdvi() { return ndvi; };
    float getElevation() { return elevation; };
    double getBirthRate() { return birthRate; };
    double getDeathRateAdults() { return deathRateAdults; };
    double getDeathRateAquatic() { return deathRateAquatic; };
    float getArea() { return area; };
    int getWidth() { return width; };
    int getLength() { return length; };
    int getCampaignState() { return campaignState; };
    int getActiveCases() { return activeCases; };

    // Public lists with humans and mosquitoes
    list<int> mosquitoesInEnvironment;
    list<int> humansInEnvironment;

    Environment(int, float, int, float, float, float, int, float, int, float, float, double, double, float);
    Environment();

    void addHuman(int);
    void removeHuman(int);
    void addMosquito(int);
    void removeMosquito(int);
    void updateDeathRateAdults(float, int);
    void updateDeathRateAquatic(float, int);
    void updateBirthRate(float, int);
    void changeCampaignState(int);
    void resetCases();
    void addCases(int);

private:
    int id;
    float density;
    int population;
    float gas;
    float sewage;
    float meanTemp;
    int wetDays;
    float precipitation;
    int daysOver90;
    float ndvi;
    float elevation;
    double birthRate;
    double deathRateAdults;
    double deathRateAquatic;
    float area;
    int width;
    int length;
    int campaignState;
    int activeCases;
};

#endif