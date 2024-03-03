#ifndef SONGCONTROLLER_H
#define SONGCONTROLLER_H

#include<stack>
#include "Repo.h"
#include "Action.h"

class SongController
{
    Repo& repository;
    std::stack<Action*> action_undo;
    std::stack<Action*> action_redo;
public:

    SongController(Repo &_repo) : repository(_repo) {}

    std::vector<Song> get_all_songs();


    void add_song(const std::string title,const std::string artist,const int year,
                                          const std::string url= {""},const std::vector<std::string> lyrics= {""});

    void remove(const Song& s);

    void clear();


    const Song& search_song(const std::string& title,const std::string& artist);

    std::vector<Song> sortByArtist(bool ascendingOrder);

    std::vector<Song> sortByTitle(bool ascendingOrder);

    void undo();

    void redo();
};

#endif // SONGCONTROLLER_H
