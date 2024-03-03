#ifndef TESTSONGCONTROLLER_H
#define TESTSONGCONTROLLER_H

#endif // TESTSONGCONTROLLER_H


#include<iostream>
#include<cassert>
#include "SongController.h"
#include "SongException.h"

class TestSongController
{
public:
    static void testAllSongController()
    {
        test_constructor();
        test_add_song();
        test_search_song();
        test_sortByArtist();
        test_sortByTitle();
        std::cout<<"SongController tests done!"<<std::endl;
    }
private:
    static void test_constructor()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding", "Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        SongController sc(r);

        assert(sc.get_all_songs()[0].get_artist() == "5 Seconds of Summer");
        assert(sc.get_all_songs()[1].get_artist() == "Maneskin");
        assert(sc.get_all_songs()[2].get_artist() == "Post Malone");
    }

    static void test_add_song()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Post Malone", "Hollywood’s Bleeding", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        SongController sc(r);

        sc.add_song("Blue on Black","Five Finger Death Punch",2022, "u4", {"You turned and you ran, oh yeah"});
        assert(sc.get_all_songs()[3].get_artist() == "Five Finger Death Punch");
        assert(r.get_all_songs()[3].get_artist() == "Five Finger Death Punch");
    }

    static void test_search_song()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding", "Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        SongController sc(r);

        assert(sc.search_song("Hollywood’s Bleeding", "Post Malone").get_artist() == "Post Malone");
        assert(sc.search_song("Hollywood’s Bleeding", "Post Malone").get_lyrics()[0] == "Tryna chase a feelin', but we'll never feel it");

        bool exceptionThrown = false;
        try
        {
            assert(sc.search_song("Saint-Tropez", "Post Malone").get_artist() == "Post Malone");
        }
        catch (const SongException& ex)
        {
            exceptionThrown = true;
            assert(strcmp(ex.what(),"The song 'Saint-Tropez'  by Post Malone does not exists.") == 0);
        }
        assert(exceptionThrown);
    }

    static void test_sortByArtist()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding", "Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        SongController sc(r);
        std::vector<Song> rez;
        bool ascending = true;
        for(int i = 0; i<sc.get_all_songs().size();i++)
        {
            rez.push_back(sc.sortByArtist(ascending)[i]);
        }
        assert(rez[0].get_artist() == "5 Seconds of Summer");

        ascending = false;
        std::vector<Song> rez1;
        for(int i = 0; i<sc.get_all_songs().size();i++)
        {
            rez1.push_back(sc.sortByArtist(ascending)[i]);
        }
        assert(rez1[0].get_artist() == "Post Malone");
    }

    static void test_sortByTitle()
    {
        Repo r;

        Song s1("Better Man", "5 Seconds of Summer", 2019, "u1", {"New friends again and again, gone when the morning comes"});
        Song s2("The Loneliest", "Maneskin", 2020, "u2", {"You'll be the saddest part of me"});
        Song s3("Hollywood’s Bleeding", "Post Malone", 2018, "u3", {"Tryna chase a feelin', but we'll never feel it"});

        r.store(s1);
        r.store(s2);
        r.store(s3);

        SongController sc(r);
        std::vector<Song> rez;
        bool ascending = true;
        for(int i = 0; i<sc.get_all_songs().size();i++)
        {
            rez.push_back(sc.sortByTitle(ascending)[i]);
        }
        assert(rez[0].get_artist() == "5 Seconds of Summer");

        ascending = false;
        std::vector<Song> rez1;
        for(int i = 0; i<sc.get_all_songs().size();i++)
        {
            rez1.push_back(sc.sortByTitle(ascending)[i]);
        }
        assert(rez1[0].get_artist() == "Maneskin");
    }
};
