#include "Repo.h"
#include"SongException.h"

#include <iostream>
Repo::Repo()
{

}

const std::vector<Song> Repo::get_all_songs() const
{
    return this->songs;
}

void Repo::store(const Song& s)
{
    auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song)
    {
        return song.get_title() == s.get_title() && song.get_artist() == s.get_artist();
    });


    if (it != songs.end())
    {
        throw SongException("A song '" + s.get_title() + "'  by " + s.get_artist() + " already exists.");
    }
    else
    {
        songs.push_back(s);
    }
}

const Song& Repo::find(const std::string& _title, const std::string& _artist)
{

    auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song)
    {
        return song.get_title() == _title && song.get_artist() == _artist;
     });

    if (it == songs.end())
    {
        throw SongException("The song '" + _title + "'  by " + _artist + " does not exists.");

    }
    return *it;
}

void Repo::remove(const Song& s)
{
    auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song)
    {
        return song.get_title() == s.get_title() && song.get_artist() == s.get_artist();
    });


    if (it == songs.end())
    {
        throw SongException("The song '" + s.get_title() + "'  by " + s.get_artist() + " does not exists.");
    }
    else
    {
        songs.erase(it);
    }
}

void Repo::clear()
{
    songs.clear();
}

