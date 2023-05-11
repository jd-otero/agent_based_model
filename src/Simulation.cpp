
// Simulation Class

#include <iostream>
#include <cstdlib>
#include "Simulation.h"

using namespace std;

Simulation::Simulation(int _nDays, bool _containerIntervention, bool _insecticideIntervention, bool _netIntervention, float _sensitivity, string _humanOutputFile, string _mosquitoOutputFile)
{
    nDays = _nDays;
    map<int, Environment> environments = {};
    map<int, Human> humans = {};
    map<int, Mosquito> mosquitoes = {};
    Movement mover;
    Intervention interventor;
    containerIntervention = _containerIntervention;
    insecticideIntervention = _insecticideIntervention;
    netIntervention = _netIntervention;
    humanOutputFile = _humanOutputFile;
    mosquitoOutputFile = _mosquitoOutputFile;
    sensitivity = _sensitivity;
};

// Read data file of Ibague's sectores
vector<std::vector<string>> Simulation::simulationData(string fileName)
{
    ifstream data(fileName);
    string line;
    vector<std::vector<std::string>> simData;
    while (std::getline(data, line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> observation;
        while (getline(lineStream, cell, ','))
        {
            observation.push_back(cell);
        }
        simData.push_back(observation);
    }
    simData.erase(simData.begin());
    return simData;
};

// Read general data of Ibague's weather
vector<std::vector<float>> Simulation::generalData(string fileName)
{
    ifstream data(fileName);
    string line;
    vector<std::vector<std::string>> moveData;
    while (std::getline(data, line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> observation;
        while (getline(lineStream, cell, ','))
        {
            observation.push_back(cell);
        }
        moveData.push_back(observation);
    }
    moveData.erase(moveData.begin());
    vector<vector<float>> moveDataOutput = {};
    for (int i = 0; i < moveData.size(); i++)
    {
        vector<float> temp_vec = {};
        for (int j = 0; j < moveData[i].size(); j++)
        {
            float temp = std::stof(moveData[i][j]);
            temp_vec.push_back(temp);
        }
        moveDataOutput.push_back(temp_vec);
    }
    return moveDataOutput;
};

int Simulation::weightedRandom(vector<float> probabilities)
{
    srand(time(NULL));
    int output = 0;
    vector<int> transformedP;
    int accumulated = 0;
    for (float i : probabilities)
    {
        int transformed = int(i * 1000) + accumulated;
        transformedP.push_back(transformed);
        accumulated = transformed;
    }
    std::uniform_int_distribution<> distInt(0, 1000);
    int randomInteger = distInt(gen2);
    // int randomInteger = rand() % 100;
    for (int i = 0; i < probabilities.size(); i++)
    {
        if (randomInteger < transformedP[i])
        {
            output = i;
            break;
        }
    }
    return output;
};

void Simulation::initialize(string simData, string flowData)
{
    // data input
    vector<std::vector<string>> data = simulationData(simData);
    vector<std::vector<float>> moveData = generalData(flowData);
    // initial populations
    int totalHumans = 0;
    int totalMosquitoes = 0;
    for (int env = 0; env < 64; env++)
    {
        srand(time(NULL));
        // Environment attributes from DANE database
        float density = std::stof(data[env][45]);
        int population = int(round(std::stof(data[env][32])));
        float gas = std::stof(data[env][29]);
        float sewage = std::stof(data[env][30]);
        float temp = std::stof(data[env][49]);
        int wetDays = int(round(std::stof(data[env][51])));
        float precipitation = std::stof(data[env][50]);
        int daysOver90 = int(round(std::stof(data[env][52])));
        float ndvi = std::stof(data[env][54]);
        float elevation = std::stof(data[env][53]);
        double birthRate = 0.04;
        double deathRate = 0.04;
        float area = std::stof(data[env][1]);
        // std::normal_distribution <double> mosquitoPopulation(2.1, 2.9);
        int initialMosquitoes = (int)(population * 1.3 * 2.1 / 2.7); // there are 2.4 people per house
        // environment creation
        Environment newEnv(env, density, population, gas, sewage, temp, wetDays, precipitation, daysOver90, ndvi, elevation, birthRate, deathRate, area);
        environments.insert(std::pair<int, Environment>(env, newEnv));

        // Human possible attributes
        vector<string> possibleStatesHuman{"S", "I", "R"};
        vector<int> possibleAgesHuman{0, 10, 20, 30, 40, 50, 60, 70, 80};
        vector<string> possibleGendersHuman{"M", "F"};
        vector<int> possibleHighEdHuman{1, 0};
        vector<int> possibleSewageHuman{1, 0};
        vector<int> possibleGasHuman{1, 0};
        int initialHumansSize = humans.size();
        for (auto hum = totalHumans; hum < totalHumans + population; hum++)
        {
            srand(time(NULL));
            // Weights for demographic varibles
            vector<float> ages_weights = {std::stof(data[env][35]),
                                          std::stof(data[env][36]),
                                          std::stof(data[env][37]),
                                          std::stof(data[env][38]),
                                          std::stof(data[env][39]),
                                          std::stof(data[env][40]),
                                          std::stof(data[env][41]),
                                          std::stof(data[env][42]),
                                          std::stof(data[env][43])};
            int age = possibleAgesHuman[weightedRandom(ages_weights)];
            string stateH = possibleStatesHuman[weightedRandom(vector<float>{1, 0})];
            int dayOfInf = 0;
            if (stateH == "I")
            {
                std::uniform_int_distribution<> distDayInf(-15, 0);
                dayOfInf = distDayInf(gen2);
            }
            vector<float> genderWeights = {std::stof(data[env][33]),
                                           std::stof(data[env][34])};
            string gender = possibleGendersHuman[weightedRandom(genderWeights)];
            vector<float> highEdWeights = {std::stof(data[env][44]),
                                           1 - std::stof(data[env][44])};
            int highEd = possibleHighEdHuman[weightedRandom(highEdWeights)];
            vector<float> sewageWeights = {sewage, (float)(1.0 - sewage)};
            vector<float> gasWeights = {gas, (float)(1.0 - gas)};
            int sewageHuman = possibleSewageHuman[weightedRandom(sewageWeights)];
            int gasHuman = possibleGasHuman[weightedRandom(gasWeights)];
            // random position in grid
            std::uniform_int_distribution<> distrHumanX(0, environments[env].getLength());
            int positionHumanX = distrHumanX(gen2);
            std::uniform_int_distribution<> distrHumanY(0, environments[env].getWidth());
            int positionHumanY = distrHumanY(gen2);
            // daily interaction (Work, school, etc.)
            int dailyEnv = weightedRandom(moveData[env]);
            // human creation
            Human newHuman(hum, stateH, age, gender, highEd, density, sewageHuman, gasHuman, dayOfInf, env, env, dailyEnv, 0.65);
            humans.insert(std::pair<int, Human>(hum, newHuman));
            environments[env].addHuman(hum);
        }
        // Mosquito attributes
        vector<bool> infectedMosquito{false, true};
        std::uniform_int_distribution<> ageMosquito(0, 30);
        for (auto mos = totalMosquitoes; mos < totalMosquitoes + initialMosquitoes; mos++)
        {
            srand(time(NULL));
            // Wheigts for mosquitoes
            int age = ageMosquito(gen2);
            bool infectedM = false;
            // if(age >= 15){
            infectedM = infectedMosquito[weightedRandom(vector<float>{0.975, 0.007})]; // 0.008
            //}
            // int age = rand() % 50;
            // cout << "age: " << age <<endl;
            std::uniform_int_distribution<> distrMosquitoX(0, environments[env].getLength());
            int positionMosquitoX = distrMosquitoX(gen2);
            std::uniform_int_distribution<> distrMosquitoY(0, environments[env].getWidth());
            int positionMosquitoY = distrMosquitoY(gen2);
            // float developmentRate = 0.0834;
            float developmentRate = 0.091;
            int lifespan = 30;
            // mosquito creation
            Mosquito newMosquito(mos, infectedM, age, positionMosquitoX, positionMosquitoY, env, developmentRate, lifespan);
            mosquitoes.insert(pair<int, Mosquito>(mos, newMosquito));
            environments[env].addMosquito(mos);
        }
        totalHumans += population;
        totalMosquitoes += initialMosquitoes;
    }
    for (auto &kh : humans)
    {
        Human *tempHuman = &kh.second;
        // Home environment
        Environment homeEnvironment = environments[tempHuman->getHomeEnvironment()];
        std::uniform_int_distribution<> distrHomeHumanX(0, homeEnvironment.getLength());
        int positionHomeHumanX = distrHomeHumanX(gen2);
        std::uniform_int_distribution<> distrHomeHumanY(0, homeEnvironment.getWidth());
        int positionHomeHumanY = distrHomeHumanY(gen2);
        tempHuman->setHomeCoordinates(positionHomeHumanX, positionHomeHumanY);

        // Daily Environment
        Environment dailyEnvironment = environments[tempHuman->getDailyEnvironment()];
        std::uniform_int_distribution<> distrDailyHumanX(0, dailyEnvironment.getLength());
        int positionDailyHumanX = distrDailyHumanX(gen2);
        std::uniform_int_distribution<> distrDailyHumanY(0, dailyEnvironment.getWidth());
        int positionDailyHumanY = distrDailyHumanY(gen2);
        tempHuman->setDailyCoordinates(positionDailyHumanX, positionDailyHumanY);

        tempHuman->updatePosition(homeEnvironment.getId(), positionHomeHumanX, positionHomeHumanY);
    }
    // humans with dengue
    for (int i = 0; i < (int)(humans.size() * 0.0052); i++) // 0052
    {
        std::uniform_int_distribution<> distrHumanInf(0, humans.size() - 1); // number relative to number of mosquitoes in env
        auto it = humans.begin();
        std::advance(it, distrHumanInf(gen2));
        std::uniform_int_distribution<> distrDay(-25, 0);
        int day = distrDay(gen2);
        humans[(it->first)].changeToInfected(distrDay(gen2));
    }
};

// Birth rate - for each environment
int Simulation::birthRate(int mosquitoesCount, Environment *tempEnvironment, int deadMosquitoes)
{
    int newMosquitoes = deadMosquitoes + (int)(tempEnvironment->getBirthRate() * tempEnvironment->mosquitoesInEnvironment.size());
    return newMosquitoes;
};

list<int> Simulation::deathRate(Environment *tempEnvironment, list<int> toKill, int infectedM)
{
    list<int> adultMosquitoes = {};
    list<int> aquaticMosquitoes = {};
    for (auto i : tempEnvironment->mosquitoesInEnvironment)
    {
        if (mosquitoes[i].isAdult())
        {
            adultMosquitoes.push_back(i);
        }
        else
        {
            aquaticMosquitoes.push_back(i);
        }
    }

    int toDeleteAdults = (int)(tempEnvironment->getDeathRateAdults() * adultMosquitoes.size());
    for (int i = 0; i < toDeleteAdults; i++)
    {
        std::uniform_int_distribution<> distrKillMosquito(0, adultMosquitoes.size() - 1); // number relative to number of mosquitoes in env
        auto it = adultMosquitoes.begin();
        std::advance(it, distrKillMosquito(gen));
        if (infectedM < 40 && mosquitoes[*it].isInfected())
        {
            continue;
        }
        else
        {
            toKill.push_back(*it);
        }
    }
    int toDeleteAquatic = (int)(tempEnvironment->getDeathRateAquatic() * aquaticMosquitoes.size());
    for (int i = 0; i < toDeleteAquatic; i++)
    {
        std::uniform_int_distribution<> distrKillMosquito(0, aquaticMosquitoes.size() - 1); // number relative to number of mosquitoes in env
        auto it = aquaticMosquitoes.begin();
        std::advance(it, distrKillMosquito(gen));
        toKill.push_back(*it);
    }
    return toKill;
};

// Delete mosquitoes from simulation
void Simulation::deleteMosquitoes(list<int> toKill, Environment *tempEnvironment)
{
    for (auto it : toKill)
    {
        mosquitoes.erase(it);
        tempEnvironment->removeMosquito(it);
    }
};

// Add mosquitoes
void Simulation::addMosquitoes(int mosquitoesCount, Environment *tempEnvironment, int mosquitoesToAdd, int dayOv90)
{
    if (mosquitoes.size() <= humans.size() * 5)
    {
        for (auto newMosIndex = mosquitoesCount; newMosIndex < mosquitoesCount + mosquitoesToAdd; newMosIndex++)
        {
            // Random initial position
            std::uniform_int_distribution<> distrMosquitoX(0, tempEnvironment->getLength());
            int positionMosquitoX = distrMosquitoX(gen);
            std::uniform_int_distribution<> distrMosquitoY(0, tempEnvironment->getWidth());
            int positionMosquitoY = distrMosquitoY(gen);
            vector<int> toLook = {tempEnvironment->getId(), positionMosquitoX, positionMosquitoY};
            // If the area is intervened by container intervention, ignore mosquito
            if (find(interventor.containerIntervened.begin(), interventor.containerIntervened.end(), toLook) != interventor.containerIntervened.end())
            {
                continue;
            }
            float developmentRate = 0.112; // 0.0834
            int lifespan = 30;
            if (dayOv90 == 1)
            {
                developmentRate = 0.25;
                lifespan = 22;
            }
            Mosquito newMosquito(newMosIndex, false, 0, positionMosquitoX, positionMosquitoY, tempEnvironment->getId(), developmentRate, lifespan);
            tempEnvironment->addMosquito(newMosIndex);
            mosquitoes.insert(std::pair<int, Mosquito>(newMosIndex, newMosquito));
        }
    }
};

// Daily update of mosquitoes age.
list<int> Simulation::updateMosquitoes(Environment *tempEnvironment)
{
    list<int> toKill = {};
    for (auto km : tempEnvironment->mosquitoesInEnvironment)
    {
        vector<int> toLook = {tempEnvironment->getId(), mosquitoes[km].getPositionX(), mosquitoes[km].getPositionY()};
        // Update alive mosquitoes age
        Mosquito *tempMosquito = &mosquitoes[km];
        tempMosquito->updateAge();
        // Kill old mosquitoes
        if (!tempMosquito->isAlive())
        {
            toKill.push_back(tempMosquito->getId());
        }
        // If area is treated with insecticide, add mosquitoes to kill list.
        else if (find(interventor.insecticideIntervened.begin(), interventor.insecticideIntervened.end(), toLook) != interventor.insecticideIntervened.end())
        {
            toKill.push_back(tempMosquito->getId());
        }
    }

    return toKill;
};

// Update daily viremic state of humans
void Simulation::updateHumans(int day)
{
    for (auto &kh : humans)
    {
        Human *tempHuman = &kh.second;
        tempHuman->updateViremia(day);
    }
};

void Simulation::writeFile(vector<vector<int>> input, string filename)
{
    std::ofstream outputFile;
    outputFile.open(filename);
    for (int i = 0; i < input.size(); i++)
    {
        std::string d = std::to_string(i) + ",";
        for (int j = 0; j < input[i].size(); j++)
        {
            d = d + std::to_string(input[i][j]) + ",";
        }
        d = d + "\n";
        outputFile << d;
    }
    outputFile.close();
};

void Simulation::simulate()
{
    srand(time(NULL));
    // all days should be simualted by hours to account for movement
    string simData = "data/sectores_ibague.csv";
    string flowData = "data/flow_sectores_ibague.csv";
    initialize(simData, flowData);

    // temperature data
    vector<std::vector<float>> meanTempData = generalData("data/temperature_ibague.csv");
    vector<std::vector<float>> daysOv90Data = generalData("data/temp_ov_90_ibague.csv");

    // count initial mosquitoes
    int mosquitoesCount = 0;
    for (int i = 0; i < environments.size(); i++)
    {
        mosquitoesCount += environments[i].mosquitoesInEnvironment.size();
    }
    int environmentsCount = environments.size();

    // Dynamics of infection
    vector<vector<int>> SIR = {};
    vector<vector<int>> SIRM = {};

    for (int day = 0; day < nDays; day++)
    {
        // environment cases

        // reset interventions
          interventor.reset();

        // write current human state
        int suceptible = 0;
        int infected = 0;
        int recovered = 0;
        int viremic = 0;

        vector<vector<float>> temp_test = {};
        for (auto &kh : humans)
        {
            Human *tempHuman = &kh.second;
            tempHuman->updateBiteRate(0.65);
            if (containerIntervention)
            {
                interventor.updateContainerIntervention(tempHuman, &environments[kh.second.getId()], sensitivity);
            }
            if (netIntervention)
            {
                interventor.updateNetIntervention(tempHuman, &environments[kh.second.getId()], sensitivity);
            }
            if (insecticideIntervention)
            {
                interventor.updateInsecticideIntervention(tempHuman, &environments[kh.second.getId()], sensitivity);
            }
            if (tempHuman->getState() == "S")
            {
                suceptible++;
            }
            else if (tempHuman->getState() == "I")
            {
                infected++;
                environments[kh.second.getHomeEnvironment()].addCases(1);

                if (tempHuman->getViremia())
                {
                    viremic++;
                }
            }
            else
            {
                recovered++;
            }
        }
        vector<int> tempVector = {};
        tempVector.push_back(suceptible);
        tempVector.push_back(infected);
        tempVector.push_back(recovered);
        SIR.push_back(tempVector);

        //  write current mosquito state
        int suceptibleM = 0;
        int infectedM = 0;
        for (auto km : mosquitoes)
        {
            if (mosquitoes[km.first].isInfected() == false)
            {
                suceptibleM++;
            }
            else
            {
                infectedM++;
            }
        }
        vector<int> tempVectorM = {};
        tempVectorM.push_back(suceptibleM);
        tempVectorM.push_back(infectedM);
        SIRM.push_back(tempVectorM);

        // Daily interaction (twice a day)
        for (int time = 0; time < 2; time++)
        {
            for (auto &kh : humans)
            {
                Human *tempHuman = &kh.second;
                Environment *tempEnvironment = &environments[tempHuman->getcurrentEnvironment()];
                for (const auto &km : tempEnvironment->mosquitoesInEnvironment)
                {
                    Mosquito *tempMosquito = &mosquitoes[km];
                    // Check if human and mosquito are in the same position
                    if (mover.checkProximity(tempHuman, tempMosquito))
                    {
                        // Try to bite
                        if (tempMosquito->bite(tempHuman->getBiteRate()))
                        {
                            // Could or not be infectuous
                            if (tempMosquito->isInfected())
                            {
                                // Mosquit to Human intection
                                if (tempMosquito->infectingBite(0.11, day))
                                {
                                    tempHuman->changeToInfected(day);
                                }
                            }
                            else if (tempHuman->getViremia())
                            {
                                // Human to Mosquito intection
                                if (tempMosquito->infectiousBite(1))
                                {
                                    tempMosquito->changeToInfected(day);
                                }
                            }
                        }
                    }
                    // Move mosquito at the end of each iteration (very caotic)
                    if (tempMosquito->isAdult())
                    {
                        mover.moveMosquito(tempMosquito, tempEnvironment);
                    }
                }

                // Move humans from home to work and viceversa unless it's the weekend, where movement is random
                if (day % 6 != 0 && day % 7 != 0)
                {
                    if (time % 2 == 0)
                    {
                        mover.moveHuman(tempHuman, &environments[tempHuman->getHomeEnvironment()], &environments[tempHuman->getDailyEnvironment()]);
                    }
                    else if (time % 2 > 0)
                    {
                        mover.moveHuman(tempHuman, &environments[tempHuman->getDailyEnvironment()], &environments[tempHuman->getHomeEnvironment()]);
                    }
                }
                else
                {
                    if (time % 2 == 0)
                    {
                        std::uniform_int_distribution<> distEnvMove(0, environmentsCount);
                        mover.moveHuman(tempHuman, &environments[tempHuman->getHomeEnvironment()], &environments[distEnvMove(gen2)]);
                    }
                    else if (time % 2 > 0)
                    {
                        mover.moveHuman(tempHuman, &environments[tempHuman->getcurrentEnvironment()], &environments[tempHuman->getHomeEnvironment()]);
                    }
                }
            }
        }

        // Update viramia in humans
        updateHumans(day);

        for (auto &ke : environments)
        {
            Environment *tempEnvironment = &ke.second;
            // Mosquitoes death and birth according to rates in each environment
            list<int> deadMosquitoes = updateMosquitoes(tempEnvironment);
            tempEnvironment->updateBirthRate(meanTempData[day][1], (int)daysOv90Data[day][1]);
            tempEnvironment->updateDeathRateAdults(meanTempData[day][1], (int)daysOv90Data[day][1]);
            tempEnvironment->updateDeathRateAquatic(meanTempData[day][1], (int)daysOv90Data[day][1]);
            int newMosquitoes = birthRate(mosquitoesCount, tempEnvironment, deadMosquitoes.size());
            list<int> mosquitoesToDelete = deathRate(tempEnvironment, deadMosquitoes, infectedM);
            deleteMosquitoes(mosquitoesToDelete, tempEnvironment);
            addMosquitoes(mosquitoesCount, tempEnvironment, newMosquitoes, (int)daysOv90Data[day][1]);
            // Global mosquito count
            mosquitoesCount += newMosquitoes;
            tempEnvironment->changeCampaignState(0);
            tempEnvironment->resetCases();
        }
    }
    writeFile(SIR, humanOutputFile);
    writeFile(SIRM, mosquitoOutputFile);
};
