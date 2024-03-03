// Problem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Entity.h"
#include "EntityType.h"
#include "tests.cpp"

int main()
{
    TestEmpty testEmpty;
    testEmpty.runTests();

    TestFox testFox;
    testFox.runTests();

    TestGopher testGopher;
    testGopher.runTests();

    TestSimulationGrid testSimulationGrid;
    testSimulationGrid.runTests();

    Simulation sim;
    sim.run();

    return 0;
}
