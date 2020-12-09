#include <iostream>
#include <cassert>
#include "../IntMachine/IntMachine.h"
using namespace std;


int main()
{
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    IntMachine machine = IntMachine(filename);
    int successful = machine.parseInput();
    assert(successful != -1);

    machine.analyzeInfiniteLoop(true);
    machine.tryRemoveInfiniteLoop();
    cout << machine.getAccumulator() << endl;
    return EXIT_SUCCESS;
}

