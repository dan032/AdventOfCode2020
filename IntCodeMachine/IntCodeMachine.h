//
// Created by Dan on 2020-12-08.
//

#ifndef AOC2020_INTCODEMACHINE_H
#define AOC2020_INTCODEMACHINE_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>

enum operationCode{
    jmp,
    acc,
    nop
};

typedef struct {
    operationCode operation;
    int value;
    bool executed;
} instruction_t;

typedef struct {
    std::vector<int> opsIndexVector;
    std::vector<instruction_t> instructionVector;
} codeData_t;

class IntCodeMachine{
private:
    std::string filename;
    codeData_t codeData;
    int accumulator;
    int programCounter;

    static operationCode ConvertStringToEnum(std::string const &string);
public:
    explicit IntCodeMachine(std::string filename);
    int ParseInput();
    bool AnalyzeLoop();
    void RemoveInfiniteLoop();
    int GetAccumulator();
    void Reset();
    void Execute();
};
#endif //AOC2020_INTCODEMACHINE_H
