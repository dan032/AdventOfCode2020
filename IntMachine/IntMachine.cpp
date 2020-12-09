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

int IntMachine::ParseInput()
{
    int value = 0;
    std::string line, operation;
    instruction_t instruction;
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
        instruction.opCode = operation;
        instruction.value = value;
        this->codeData.instructionVector.push_back(instruction);
    }
    file.close();
    return 0;
}

bool IntMachine::AnalyzeInfiniteLoop(bool initializeOpsLoopVector)
{
    std::unordered_set<int> indexSet;      // Will store index to check if op code has already been called
    for (int i = 0; i < this->codeData.instructionVector.size(); i++)
    {
        if (indexSet.find(i) != indexSet.end()) return true;

        indexSet.insert(i);
        if (this->codeData.instructionVector[i].opCode == "acc")
        {
            this->codeData.accumulator += this->codeData.instructionVector[i].value;
        }
        else if (this->codeData.instructionVector[i].opCode == "jmp")
        {
            if (initializeOpsLoopVector)
            {
                this->codeData.opsIndexVector.push_back(i);
            }
            i += this->codeData.instructionVector[i].value - 1;
        }
        else if (this->codeData.instructionVector[i].opCode == "nop")
        {
            if (initializeOpsLoopVector)
            {
                this->codeData.opsIndexVector.push_back(i);
            }
        }
    }
    return false;
}

void IntMachine::TryRemoveInfiniteLoop()
{
    bool infinite = true;
    for (int idx : this->codeData.opsIndexVector)         // Brute force to see if changing ops removes infinite loop
    {
        this->codeData.accumulator = 0;
        if (this->codeData.instructionVector[idx].opCode == "jmp")
        {
            this->codeData.instructionVector[idx].opCode = "nop";
            infinite = this->AnalyzeInfiniteLoop(false);
            this->codeData.instructionVector[idx].opCode ="jmp";
        }
        else if (this->codeData.instructionVector[idx].opCode == "nop")
        {
            this->codeData.instructionVector[idx].opCode = "jmp";
            infinite = this->AnalyzeInfiniteLoop(false);
            this->codeData.instructionVector[idx].opCode ="nop";
        }

        if (!infinite) break;
    }
}

int IntMachine::GetAccumulator() {return this->codeData.accumulator;}