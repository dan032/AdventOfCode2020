//
// Created by Dan on 2020-12-08.
//

#include "IntMachine.h"
#include <utility>

IntMachine::IntMachine(std::string filename)
{
    this->codeData.accumulator = 0;
    this->filename = std::move(filename);
}

int IntMachine::parseInput()
{
    int value = 0;
    std::string line, operation;
    std::pair<std::string, int> opPair;
    std::ifstream file(this->filename);

    if (!file.is_open())
    {
        perror("Invalid File\n");
        return -1;
    }

    while(file.good())                  // Populate vector with all op codes and their values
    {
        getline(file, line);
        operation = line.substr(0, line.find(' '));
        value = stoi(line.substr((line.find(' '))));
        opPair = make_pair(operation, value);
        this->codeData.bootCodeVector.push_back(opPair);
    }
    file.close();
    return 0;
}

bool IntMachine::analyzeInfiniteLoop(bool initializeOpsVectors)
{
    std::unordered_set<int> m;      // Will store index to check if op code has already been called
    for (int i = 0; i < this->codeData.bootCodeVector.size(); i++)
    {
        if (m.find(i) != m.end()) return true;

        m.insert(i);
        if (this->codeData.bootCodeVector[i].first == "acc")
        {
            this->codeData.accumulator += this->codeData.bootCodeVector[i].second;
        }
        else if (this->codeData.bootCodeVector[i].first == "jmp")
        {
            if (initializeOpsVectors)
            {
                this->codeData.opsVector.push_back(i);
            }
            i += this->codeData.bootCodeVector[i].second - 1;
        }
        else if (this->codeData.bootCodeVector[i].first == "nop")
        {
            if (initializeOpsVectors)
            {
                this->codeData.opsVector.push_back(i);
            }
        }
    }
    return false;
}

void IntMachine::tryRemoveInfiniteLoop()
{
    bool infinite = true;
    for (int op : this->codeData.opsVector)         // Brute force to see if changing ops removes infinite loop
    {
        this->codeData.accumulator = 0;
        if (this->codeData.bootCodeVector[op].first == "jmp")
        {
            this->codeData.bootCodeVector[op].first = "nop";
            infinite = this->analyzeInfiniteLoop(false);
            this->codeData.bootCodeVector[op].first ="jmp";
        }
        else if (this->codeData.bootCodeVector[op].first == "nop")
        {
            this->codeData.bootCodeVector[op].first = "jmp";
            infinite = this->analyzeInfiniteLoop(false);
            this->codeData.bootCodeVector[op].first ="nop";
        }

        if (!infinite) break;
    }
}

int IntMachine::getAccumulator() {return this->codeData.accumulator;}