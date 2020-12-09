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
    std::vector<int> opsVector;
    std::vector<std::pair<std::string, int>> bootCodeVector;
} CodeData;

class IntMachine{
private:
    std::string filename;
    CodeData codeData;
public:
    explicit IntMachine(std::string filename);
    int parseInput();
    bool analyzeInfiniteLoop(bool initializeOpsVectors);
    void tryRemoveInfiniteLoop();
    int getAccumulator();
};
#endif //AOC2020_INTMACHINE_H
