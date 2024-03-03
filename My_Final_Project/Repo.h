#ifndef REPO_H
#define REPO_H

#include"Song.h"

class Repo
{
    std::vector<Song> songs;
public:

    Repo();

    Repo(const Repo&) = delete; //copy const
    Repo& operator=(const Repo&) = delete; //asign op

    const std::vector<Song> get_all_songs() const;


    virtual void store(const Song& s);

    virtual const Song& find(const std::string& title, const std::string& artist);

    virtual void remove(const Song& s);

    void clear();
};

#endif // REPO_H
