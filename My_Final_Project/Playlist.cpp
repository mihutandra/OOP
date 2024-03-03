#include "Playlist.h"
#include "SongException.h"
#include <random>

Playlist::Playlist()
{

}

Playlist::Playlist(std::vector<Song> p)
{
    for(int i = 0; i < p.size(); i++)
    {
        play_list.push_back(p[i]);
    }
}

void Playlist::addSong(Song s)
{
    auto it = std::find_if(play_list.begin(), play_list.end(), [&](const Song& song)
    {
        return song.get_title() == s.get_title() && song.get_artist() == s.get_artist();
    });


    if (it != play_list.end())
    {
        throw SongException("A song '" + s.get_title() + "'  by " + s.get_artist() + " already exists.");
    }
    else
    {
        play_list.push_back(s);
    }
}
void Playlist::removeSong(Song s)
{
    for (auto it = play_list.begin(); it != play_list.end(); it++)
    {
        if (it->get_title() == s.get_title() && it->get_artist() == s.get_artist())
        {
            play_list.erase(it);
            break;
        }
    }
}
void Playlist::clear(Song s)
{
    play_list.clear();
}

Playlist Playlist::generateRandom(int n, std::vector<Song> other)
{
    std::vector<Song> tempPlaylist;
    for(int i = 0; i < other.size(); i++)
    {
        tempPlaylist.push_back(other[i]);
    }


    std::shuffle(tempPlaylist.begin(), tempPlaylist.end(), std::default_random_engine());

    // Create a new Playlist object with the generated songs
    Playlist randomPlaylist;
    int i = 0;
    for (const auto& song : tempPlaylist)
    {
        if(i < n)
        {
            randomPlaylist.addSong(song);
        }
        else
            break;
        i++;
    }

    return randomPlaylist;
}

std::vector<Song> Playlist::get_playlist()
{
    return this->play_list;
}
