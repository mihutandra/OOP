#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"

class Playlist
{
    std::vector<Song> play_list;
public:
    Playlist();
    Playlist(std::vector<Song> p);
    std::vector<Song> get_playlist();
    void addSong(Song s);
    void removeSong(Song s);
    void clear(Song s);
    Playlist generateRandom(int n, std::vector<Song> other);
};

#endif // PLAYLIST_H
