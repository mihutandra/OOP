#ifndef TESTREPO_H
#define TESTREPO_H

#include "Repo.h"
#include "SongException.h"
#include <cassert>
#include<iostream>


class TestRepo
{
public:
    static void TestAllRepo()
    {
        TestStore();
        TestFind();
        TestRemove();
        std::cout<<"Repository tests done!"<<std::endl;
    }

private:
    static void TestStore()
    {
        Repo r;
        /*
        Song s1("Better Man", "5 Seconds of Summer", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", {"You'll be the saddest part of me"});
        Song s3("Post Malone", "Hollywood’s Bleeding", {"Tryna chase a feelin', but we'll never feel it"});
*/

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding","Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);
        assert(r.get_all_songs()[0].get_title() == "Better Man");
        assert(r.get_all_songs()[1].get_artist() == "Maneskin");
        assert(r.get_all_songs()[2].get_lyrics()[0] == "Tryna chase a feelin', but we'll never feel it");
    }

    static void TestFind()
    {
        Repo r;
        /*
        Song s1("Better Man", "5 Seconds of Summer", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", {"You'll be the saddest part of me"});
        Song s3("Post Malone", "Hollywood’s Bleeding", {"Tryna chase a feelin', but we'll never feel it"});
        */
        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding","Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);

        assert(r.find("The Loneliest", "Maneskin").get_artist() == "Maneskin");
        assert(r.find("The Loneliest", "Maneskin").get_lyrics()[0] == "You'll be the saddest part of me");

        bool exceptionThrown = false;
        try
        {
            assert(r.find("Saint-Tropez", "Post Malone").get_artist() == "Post Malone");
        }
        catch (const SongException& ex)
        {
            exceptionThrown = true;
            assert(strcmp(ex.what(),"The song 'Saint-Tropez'  by Post Malone does not exists.") == 0);
        }
        assert(exceptionThrown);
    }

    static void TestRemove()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding","Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        r.remove(s3);


        bool exceptionThrown = false;
        try
        {
            assert(r.find("Hollywood’s Bleeding", "Post Malone").get_artist() == "Post Malone");
        }
        catch (const SongException& ex)
        {
            exceptionThrown = true;
            assert(strcmp(ex.what(),"The song 'Hollywood’s Bleeding'  by Post Malone does not exists.") == 0);
        }
        assert(exceptionThrown);
    }
};

#endif // TESTREPO_H
