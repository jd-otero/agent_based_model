// Movement Class

#include <iostream>
#include <cstdlib>
#include "Movement.h"

using namespace std;
std::mt19937 gen2(rd()); // Second random (for initialization)

Movement::Movement()
{
}

// Move humans
void Movement::moveHuman(Human *human, Environment *oldEnvironment, Environment *newEnvironment)
{
    // Move random if destination environment is different from home or work
    std::uniform_int_distribution<> distrX(0, newEnvironment->getLength());
    int positionX = distrX(gen2);
    std::uniform_int_distribution<> distrY(0, newEnvironment->getWidth());
    int positionY = distrY(gen2);
    // Move
    oldEnvironment->removeHuman(human->getId());
    human->changeEnvironment(newEnvironment->getId());
    human->updatePosition(newEnvironment->getId(), positionX, positionY);
    newEnvironment->addHuman(human->getId());
};

void Movement::moveMosquito(Mosquito *mosquito, Environment *environment)
{
    int maxX = environment->getLength();
    int maxY = environment->getWidth();

    // How much will it move
    std::uniform_int_distribution<> distNew(-2, 2);
    int newX = distNew(gen);
    int newY = distNew(gen);

    int positionX = mosquito->getPositionX();
    int positionY = mosquito->getPositionY();

    // Move mosquito
    if (newX + positionX < maxX && newX + positionX >= 0)
    {
        positionX = positionX + newX;
    };
    if (newY + positionY < maxY && newY + positionY >= 0)
    {
        positionY = positionY + newY;
    };
    mosquito->move(positionX, positionY);
};

// Check if human and mosquito are in the same location
bool Movement::checkProximity(Human *human, Mosquito *mosquito)
{
    if (human->getPositionX() == mosquito->getPositionX() && human->getPositionY() == mosquito->getPositionY())
    {
        return true;
    }
    else
    {
        return false;
    }
};
