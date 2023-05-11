#ifndef HUMAN_H
#define HUMAN_H

// Human Class

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;
using std::vector;

class Human
{
public:
    int getId() { return id; };
    string getState() { return state; };
    int getAge() { return age; };
    string getGender() { return gender; };
    int getHighEd() { return highEd; };
    float getDensity() { return density; };
    int getSewage() { return sewage; };
    int getGas() { return gas; };
    int getPositionX() { return positionX; };
    int getPositionY() { return positionY; };
    int getDayOfInfection() { return dayOfInfection; };
    int getcurrentEnvironment() { return currentEnvironment; };
    int getHomeEnvironment() { return homeEnvironment; };
    int getDailyEnvironment() { return dailyEnvironment; };
    int getOcasionalEnvironment() { return ocasionalEnvironment; };
    bool getViremia() { return viremia; };
    float getBiteRate() { return biteRate; };
    float getContainerInt() { return containerInt; };
    int getNetInt() { return netInt; };
    int getInsecticideInt() { return insecticideInt; };
    vector<int> getHomeCoordinates() { return homeCoordinates; };
    vector<int> getDailyCoordinates() { return dailyCoordinates; };

    void changeToInfected(int);
    void changeToRecovered();
    void setDayOfInfection(int);
    void updateViremia(int);
    void changeEnvironment(int);
    void setDailyCoordinates(int, int);
    void setHomeCoordinates(int, int);
    void updatePosition(int, int, int);
    void updateBiteRate(float);
    void updateContainerInt(float, float, float, int, int, float);
    void updateNetInt(float, float, float, int, int, float);
    void updateInsecticideInt(float, float, float, int, int, float);

    Human(int, string, int, string, int, float, int, int, int, int, int, int, float);
    Human();

private:
    int id;
    string state;
    int age;
    string gender;
    int highEd;
    float density;
    int sewage;
    int gas;
    int positionX;
    int positionY;
    int currentEnvironment;
    int homeEnvironment;
    int dailyEnvironment;
    int ocasionalEnvironment;
    int dayOfInfection;
    bool viremia;
    float biteRate;
    float containerInt;
    float netInt;
    float insecticideInt;
    vector<int> homeCoordinates;
    vector<int> dailyCoordinates;
};

#endif