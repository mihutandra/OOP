#ifndef FILEREPO_H
#define FILEREPO_H

#include<fstream>
#include <sstream>
#include "Repo.h"

class FileRepo: public Repo
{
    std::string filepath;
    std::vector<Song> _songs;

public:
    FileRepo(std::string _filepath);

    std::string& GetFilePath();

    std::vector<Song> getSongsList();

    void load();

    void save();

    void store(const Song& s) override;

    void remove(const Song& s) override;
};

#endif // FILEREPO_H
