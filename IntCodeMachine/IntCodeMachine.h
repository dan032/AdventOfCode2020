//
// Created by Dan on 2020-12-08.
//

#ifndef AOC2020_INTCODEMACHINE_H
#define AOC2020_INTCODEMACHINE_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>

typedef struct {
    std::string opCode;
    int value = 0;
} instruction_t;

typedef struct {
    int accumulator;
    std::vector<int> opsIndexVector;
    std::vector<instruction_t> instructionVector;
} codeData_t;

class IntCodeMachine{
private:
    std::string filename;
    codeData_t codeData;
public:
    explicit IntCodeMachine(std::string filename);
    int ParseInput();
    bool AnalyzeInfiniteLoop(bool initializeOpsIndexVector);
    void TryRemoveInfiniteLoop();
    int GetAccumulator();
};
#endif //AOC2020_INTCODEMACHINE_H
