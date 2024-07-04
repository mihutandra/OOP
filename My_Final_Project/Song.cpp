#include "Song.h"

Song::Song(const std::string _title,const std::string _artist,const int _year,
                                         const std::string _url, const std::vector<std::string> _lyrics)
{
    title = _title;
    artist = _artist;
    year = _year;
    url = _url;
    lyrics = _lyrics;
}


std::string Song::get_title() const
{
    return this->title;
}

std::string Song::get_artist() const
{
    return this->artist;
}


int Song::get_year() const
{
    return this->year;
}

std::string Song::get_url() const
{
    return this->url;
}


std::vector<std::string> Song::get_lyrics() const
{
    return this->lyrics;
}

void Song::set_title(const std::string _title)
{
    title = _title;
}
void Song::set_artist(const std::string _artist)
{
    artist = _artist;
}

void Song::set_year(const int _year)
{
    year = _year;
}
void Song::set_url(const std::string _url)
{
    url = _url;
}

void Song::set_lyrics(const std::vector<std::string> _lyrics)
{
    lyrics = _lyrics;
}

