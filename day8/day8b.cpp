#include <iostream>
#include "../IntMachine/IntMachine.h"
using namespace std;


int main()
{
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    IntMachine machine = IntMachine(filename);

    try{
        machine.parseInput();
    }
    catch(exception& exception){
        cout  << exception.what() << endl;
    }

    machine.checkInfiniteLoop(true);
    machine.tryRemoveInfiniteLoop();
    cout << machine.getAccumulator() << endl;
    return EXIT_SUCCESS;
}

