//
// Created by Dan on 2020-12-08.
//

#include "IntMachine.h"
#include <utility>

IntMachine::IntMachine()
{
    this->acc = 0;
    this->filename = "";
}
IntMachine::IntMachine(std::string filename)
{
    this->acc = 0;
    this->filename = std::move(filename);
}

void IntMachine::parseInput()
{
    std::string line, operation;
    int value = 0;
    std::pair<std::string, int> opPair;
    std::ifstream file(this->filename);

    if (!file.is_open())
    {
        throw std::invalid_argument("Invalid File");
    }

    while(file.good())                  // Populate vector with all op codes and their values
    {
        getline(file, line);
        operation = line.substr(0, line.find(' '));
        value = stoi(line.substr((line.find(' '))));
        opPair = make_pair(operation, value);
        this->dataVector.push_back(opPair);
    }
    file.close();
}

bool IntMachine::checkInfiniteLoop(bool initializeOpsVectors)
{
    std::unordered_set<int> m;      // Will store index to check if op code has already been called
    for (int i = 0; i < this->dataVector.size(); i++)
    {
        if (m.find(i) != m.end()) return true;

        m.insert(i);
        if (this->dataVector[i].first == "acc")
        {
            this->acc += this->dataVector[i].second;
        }
        else if (this->dataVector[i].first == "jmp")
        {
            if (initializeOpsVectors)
            {
                this->opsVector.push_back(i);
            }
            i += this->dataVector[i].second - 1;
        }
        else if (this->dataVector[i].first == "nop")
        {
            if (initializeOpsVectors)
            {
                this->opsVector.push_back(i);
            }
        }
    }
    return false;
}

void IntMachine::tryRemoveInfiniteLoop()
{
    bool infinite = true;
    for (int op : opsVector)         // Brute force to see if changing ops removes infinite loop
    {
        this->acc = 0;
        if (this->dataVector[op].first == "jmp")
        {
            this->dataVector[op].first = "nop";
            infinite = this->checkInfiniteLoop(false);
            this->dataVector[op].first ="jmp";
        }
        else if (this->dataVector[op].first == "nop")
        {
            this->dataVector[op].first = "jmp";
            infinite = this->checkInfiniteLoop(false);
            this->dataVector[op].first ="nop";
        }

        if (!infinite) break;
    }
}

int IntMachine::getAccumulator() {return this->acc;}