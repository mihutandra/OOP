#ifndef TESTFILEREPO_H
#define TESTFILEREPO_H

#endif // TESTFILEREPO_H

#include<iostream>
#include "SongException.h"
#include <cassert>
#include"FileRepo.h"


/*
    FileRepo();

    void load();

    void save();

    void store(const Song& s) override;

    void remove(const Song& s) override;
*/

class TestFileRepo
{
public:
    static void testAllFileRepo()
    {
        test_load();
        //test_store();
        //test_remove();
        std::cout<<"File repository tests done!"<<std::endl;
    }
private:

    static void test_load()
    {
        FileRepo testSource("C:/Users/flore/OneDrive/Desktop/Songs.txt");
        std::vector<Song> rez;
        testSource.load();

    }

    static void test_store()
    {

    }

    static void test_remove()
    {

    }
};
