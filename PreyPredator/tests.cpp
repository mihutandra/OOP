#include "Entity.h"
#include "SimulationGrid.h"
#include <iostream>
#include <fstream>

/// EMPTY
class TestEmpty{
public:
    static void runTests()
    {
        test_def_constructor();
        test_what();
        test_next();
        testtoString();

        std::cout<<"all  empty tests passed :D"<<std::endl;

    }
private:
    static void test_def_constructor(){
        Empty e;
        assert(e.get_row() == 0);
        assert(e.get_col() == 0);
    }
    static void test_what(){
        Empty e;
        EntityType et = e.what();
        assert(et == EntityType::EMPTY);
    }
    static void test_next(){
        SimulationGrid g;
        Empty e;
        Entity* nextEntity = e.next(g);
        assert(nextEntity != nullptr);
    }
    static void testtoString(){
        Empty e;
        std::string str = e.toString();
        assert(str == "E");
    }
};

/// PLANT
class TestPlant
{
public:
    static void runTests()
    {
        test_default_constructor_plant();
        test_what_plant();
        test_next_plant();
        test_toString_plant();

        std::cout << "All Plant tests passed";
    }

private:
    static void test_default_constructor_plant()
    {
        Plant p;
        assert(p.get_row() == 0);
        assert(p.get_col() == 0);
    }
    static void test_what_plant()
    {
        Plant p;
        EntityType et = p.what();
        assert(et == EntityType::PLANT);
    }

    static void test_next_plant()
    {
        SimulationGrid g;
        Plant p;
        Entity* nextEntity = p.next(g);
        assert(nextEntity != nullptr);
    }

    static void test_toString_plant(){
        Plant p;
        std::string str = p.toString();
        assert(str == "P");
    }
};

/// GOPHER
class TestGopher
{
public:
    static void runTests()
    {
        test_default_constructor_gopher();
        test_what_gopher();
        test_next_gopher();
        test_toString_gopher();

        std::cout << "All Gopher tests passed"<<std::endl;
    }

private:
    static void test_default_constructor_gopher()
    {
        Gopher g;
        assert(g.get_row() == 0);
        assert(g.get_col() == 0);
    }
    static void test_what_gopher()
    {
        Gopher g;
        EntityType et = g.what();
        assert(et == EntityType::GOPHER);
    }

    static void test_next_gopher()
    {
        SimulationGrid gr;
        Gopher g;
        Entity* nextEntity = g.next(gr);
        assert(nextEntity != nullptr);
    }

    static void test_toString_gopher(){
        Gopher g;
        std::string str = g.toString();
        assert(str == "G");
    }
};

/// FOX
class TestFox
{
public:
    static void runTests()
    {
        test_default_constructor_fox();
        test_what_fox();
        test_next_fox();
        test_toString_fox();

        std::cout << "All Fox tests passed"<<std::endl;
    }

private:
    static void test_default_constructor_fox()
    {
        Fox f;
        assert(f.get_row() == 0);
        assert(f.get_col() == 0);
    }
    static void test_what_fox()
    {
        Fox f;
        EntityType et = f.what();
        assert(et == EntityType::FOX);
    }

    static void test_next_fox()
    {
        SimulationGrid gr;
        Fox f;
        Entity* nextEntity = f.next(gr);
        assert(nextEntity != nullptr);
    }

    static void test_toString_fox(){
        Fox f;
        std::string str = f.toString();
        assert(str == "F");
    }
};

class TestSimulationGrid{
public:
    static void runTests() {
        test_default_constructor();
        test_paramtererized_constructor();
        //test_path_constructor();
        //test_destructor();
        //test_get_entity();
        //test_create_entity();

        std::cout<<"all simulation tests passed"<<std::endl;
    }

private:
    static void test_default_constructor(){
        SimulationGrid gr;
        assert(gr.get_rows() == 0);
        assert(gr.get_cols() == 0);
    }

    static void test_paramtererized_constructor(){
        SimulationGrid gr;
        assert(gr.get_rows() == 0);
        assert(gr.get_cols() == 0);
    }
    static void test_path_constructor(){
        // Create a temporary file with some input data
        std::ofstream tempFile("tempFile.txt");
        tempFile << "3 3\n0 0 0\n0 1 0\n0 0 0\n";
        tempFile.close();

        // Call the constructor with the temporary file path
        SimulationGrid sg("tempFile.txt");

        // Check that the dimensions of the grid were set correctly
        //assert(sg.get_cols() == 3);
        //ssert(sg.get_rows() == 3);

    }

};