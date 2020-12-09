#include <iostream>
#include <cassert>
#include "../IntMachine/IntMachine.h"

int main()
{
    std::string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    IntMachine machine = IntMachine(filename);
    int successful = machine.ParseInput();
    assert(successful != -1);

    machine.AnalyzeInfiniteLoop(false);
    std::cout << machine.GetAccumulator() << std::endl;
    return EXIT_SUCCESS;
}
