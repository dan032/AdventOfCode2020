//
// Created by Dan on 2020-12-08.
//

#ifndef AOC2020_INTMACHINE_H
#define AOC2020_INTMACHINE_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>

class IntMachine{
private:
    int acc;
    std::string filename;
    std::vector<int> opsVector;
    std::vector<std::pair<std::string, int>> dataVector;
public:
    IntMachine();
    explicit IntMachine(std::string filename);
    int parseInput();
    bool analyzeInfiniteLoop(bool initializeOpsVectors);
    void tryRemoveInfiniteLoop();
    int getAccumulator();
};


#endif //AOC2020_INTMACHINE_H
