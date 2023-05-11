#ifndef MOSQUITO_H
#define	MOSQUITO_H

// Mosquito Class

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;
using std::vector;

class Mosquito{
    public:
        int getId() {return id;};
        bool isInfected() {return infected;};
        int getAge() {return age;};
        int getCurrentEnvironment() {return currentEnvironment;};
        int getPositionX() {return positionX;};
        int getPositionY() {return positionY;};
        int getDayOfInfection() {return dayOfInfection;};
        int getNumberOfBites() {return numberOfBites;};
        int getNeededBites() {return neededBites;};
        bool isAlive() {return alive;};
        bool isAdult() {return adult;};
        int getLifespan() {return lifespan;};
        float getDevelopmentRate() {return developmentRate;};

        bool bite(float);
        bool infectingBite(float, int);
        bool infectiousBite(float);
        void changeToInfected(int);
        void updateAge();
        void die();
        void move(int, int);
        void updateNumberOfBites();

        Mosquito(int, bool, int , int, int , int, float, int);
        Mosquito(int, int, int, int);
        Mosquito();
        ~Mosquito();

    private:
        int id;
        bool infected;
        int age;
        int positionX;
        int positionY;
        int currentEnvironment;
        int dayOfInfection;
        int numberOfBites;
        int neededBites;
        int maxBitesPerDay;
        int bitesToday;
        bool alive;
        bool adult;
        int lifespan;
        float developmentRate;
};

#endif