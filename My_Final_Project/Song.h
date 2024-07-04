#ifndef SONG_H
#define SONG_H

#include<string>
#include<vector>

class Song
{
    std::string title;
    std::string artist;
    std::string url;
    int year;
    std::vector<std::string> lyrics;
public:

    Song()=default;


    Song(const std::string _title ,const std::string _artist,const int _year,
                                         const std::string _url = "",const std::vector<std::string> _lyrics = {""});

    std::string get_title() const;

    std::string get_artist() const;


    int get_year() const;

    std::string get_url() const;

    std::vector<std::string> get_lyrics() const;

    void set_title(const std::string _title);
    void set_artist(const std::string _artist);

    void set_year(const int _year);
    void set_url(const std::string _url);

    void set_lyrics(const std::vector<std::string> _lyrics);
};

#endif // SONG_H
