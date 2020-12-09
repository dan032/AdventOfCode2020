//
// Created by Dan on 2020-12-08.
//

#ifndef AOC2020_INTMACHINE_H
#define AOC2020_INTMACHINE_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>

typedef struct {
    int accumulator;
    std::vector<int> opsLoopVector;
    std::vector<std::pair<std::string, int>> bootCodeVector;
} CodeData;

class IntMachine{
private:
    std::string filename;
    CodeData codeData;
public:
    explicit IntMachine(std::string filename);
    int ParseInput();
    bool AnalyzeInfiniteLoop(bool initializeOpsLoopVector);
    void TryRemoveInfiniteLoop();
    int GetAccumulator();
};
#endif //AOC2020_INTMACHINE_H
