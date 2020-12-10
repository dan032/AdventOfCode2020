#include <iostream>
#include <cassert>
#include "../IntCodeMachine/IntCodeMachine.h"

int main()
{
    std::string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    IntCodeMachine machine = IntCodeMachine(filename);
    int successful = machine.ParseInput();
    assert(successful != -1);

    machine.AnalyzeLoop();
    std::cout << machine.GetAccumulator() << std::endl;
    return EXIT_SUCCESS;
}
