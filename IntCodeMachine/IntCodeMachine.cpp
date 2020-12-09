//
// Created by Dan on 2020-12-08.
//

#include "IntCodeMachine.h"
#include <utility>

IntCodeMachine::IntCodeMachine(std::string filename)
{
    this->accumulator = 0;
    this->programCounter = 0;
    this->filename = std::move(filename);
}

int IntCodeMachine::ParseInput()
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

    while(file.good())
    {
        getline(file, line);
        operation = line.substr(0, line.find(' '));
        value = stoi(line.substr((line.find(' '))));
        instruction.operation = ConvertStringToEnum(operation);
        instruction.value = value;
        this->codeData.instructionVector.push_back(instruction);
    }

    file.close();
    return 0;
}

bool IntCodeMachine::AnalyzeLoop()
{
    while (this->programCounter < this->codeData.instructionVector.size())
    {
        if (!this->codeData.instructionVector[this->programCounter].executed)
        {
            this->Execute();
        }
        else{
            return true;
        }
    }
    return false;
}

void IntCodeMachine::Execute()
{
    this->codeData.instructionVector[this->programCounter].executed = true;

    switch (this->codeData.instructionVector[this->programCounter].operation)
    {
        case jmp:
            this->codeData.opsIndexVector.push_back(this->programCounter);
            this->programCounter += this->codeData.instructionVector[this->programCounter].value;
            return;

        case nop:
            this->codeData.opsIndexVector.push_back(this->programCounter);
            this->programCounter++;
            return;

        case acc:
            this->accumulator += this->codeData.instructionVector[this->programCounter].value;
            this->programCounter++;
            return;
    }
}

void IntCodeMachine::RemoveInfiniteLoop()
{
    bool infinite = true;
    for (int idx : this->codeData.opsIndexVector)         // Brute force to see if changing ops removes infinite loop
    {
        this->Reset();
        switch(this->codeData.instructionVector[idx].operation)
        {
            case jmp:
                this->codeData.instructionVector[idx].operation = nop;
                infinite = this->AnalyzeLoop();
                this->codeData.instructionVector[idx].operation = jmp;
                break;

            case nop:
                this->codeData.instructionVector[idx].operation = jmp;
                infinite = this->AnalyzeLoop();
                this->codeData.instructionVector[idx].operation = nop;
                break;

            default:
                break;
        }

        if (!infinite) break;
    }
}

int IntCodeMachine::GetAccumulator() {return this->accumulator;}

void IntCodeMachine::Reset()
{
    for (auto & instruction : this->codeData.instructionVector)
    {
        instruction.executed = false;
    }
    this->programCounter = 0;
    this->accumulator = 0;
}

operationCode IntCodeMachine::ConvertStringToEnum(std::string const &string)
{
    if (string == "jmp") return jmp;
    if (string == "acc") return acc;
    if (string == "nop") return nop;
}
