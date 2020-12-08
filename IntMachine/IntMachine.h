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
    std::vector<int> opsVector;
    std::vector<std::pair<std::string, int>> dataVector;
    std::string filename;
    int acc;
public:
    IntMachine();
    explicit IntMachine(std::string filename);
    void parseInput();
    bool checkInfiniteLoop(bool initializeOpsVectors);
    void tryRemoveInfiniteLoop();
    int getAccumulator();
};


#endif //AOC2020_INTMACHINE_H
