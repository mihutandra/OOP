#include "FileRepo.h"
#include <iostream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

FileRepo::FileRepo(std::string _filepath)
{
    filepath = _filepath;
}

std::string& FileRepo::GetFilePath()
{
    return this->filepath;
}

void FileRepo::load()
{
    std::fstream fin(filepath);

    if (!fin.is_open())
    {
        throw std::runtime_error("Failed to open: " + filepath);
    }


    std::string line;

    std::string _artist, _title;
    std::string _url;
    int _year;
    std::vector<std::string> _lyrics;

    while (std::getline(fin, line))
    {

        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value))
        {
            if (key == "AREIST")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                _artist.assign(value);
            }
            else if (key == "TITLE")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                _title.assign(value);
            }

            else if (key == "YEAR")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                //_year.assign(value);
                _year = std::stoi(value);
            }

            else if (key == "URL")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 2);
                _url.assign(value);
            }
            else if (value != "LYRICS=")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 1);

                std::string data;
                std::istringstream valueStream(value);

                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~";

                    std::size_t pos = 0;

                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;

                    if (data.size() > 1)
                    {

                        //remove '' if they are at the end of the word
                        if ((int)data[data.size() - 1] == 39)
                        {
                            if ((int)data[data.size() - 2] == 39)
                                data = data.substr(0, data.size() - 2);
                            else
                                data = data.substr(0, data.size() - 1);
                        }

                        //remove '' if they are at the beginning of the word
                        if ((int)data[0] == 39)
                        {
                            if ((int)data[1] == 39)
                                data = data.substr(2, data.size());
                            else
                                data = data.substr(1, data.size());
                        }
                    }

                    data[0] = tolower(data[0]);
                    _lyrics.push_back(data);
                }
            }
        }
        else
        {
            if (key[0] != '"')
            {
                std::string data;
                std::istringstream valueStream(key);
                while (std::getline(valueStream, data, ' '))
                {
                    std::string separators = "-+=#,.?!/;:&*$^_<>@(){}[]`~";

                    std::size_t pos = 0;
                    while ((pos = data.find_first_of(separators, pos)) != std::string::npos)
                    {
                        data = data.substr(0, pos);
                    }

                    pos = 0;

                    if (data.size() > 1)
                    {

                        //remove '' if they are at the end of the word
                        if ((int)data[data.size() - 1] == 39)
                        {
                            if ((int)data[data.size() - 2] == 39)
                                data = data.substr(0, data.size() - 2);
                            else
                                data = data.substr(0, data.size() - 1);
                        }

                        //remove '' if they are at the beginning of the word
                        if ((int)data[0] == 39)
                        {
                            if ((int)data[1] == 39)
                                data = data.substr(2, data.size());
                            else
                                data = data.substr(1, data.size());
                        }
                    }

                    data[0] = tolower(data[0]);
                    _lyrics.push_back(data);
                }
                _lyrics.push_back(key);
            }
            else
            {
                //Song s;
                std::vector<std::string> all_lyrics;

                for (int i = 0; i < _lyrics.size() ; i++)
                {
                    all_lyrics.push_back(_lyrics[i]);
                }

                _songs.push_back(Song(_title, _artist,_year,_url, all_lyrics));
                _title = "";
                _artist = "";
                _url = "";
                _lyrics.clear();
            }
        }
    }

    fin.close();

    std::ofstream file(filepath, std::ios::trunc); // Open the file in truncate mode

    // Check if the file is opened successfully
    if (file.is_open())
    {
        // File is opened successfully, so it can be considered empty now
        file.close();
    }
    else
    {
        // Failed to open the file
        throw std::runtime_error("Failed to open: " + filepath);
    }
}


void FileRepo::save()
{
    std::fstream fout(filepath);

    Repo sngs;

    if (!fout.is_open())
    {
        throw std::runtime_error("Failed to open: " + filepath);
    }

    for(auto& song: sngs.get_all_songs())
    {
        fout<<song.get_title()<<std::endl;

        fout<<song.get_artist()<<std::endl;

        fout<<song.get_year()<<std::endl;

        fout<<song.get_url()<<std::endl;

        for(int i =0; i<song.get_lyrics().size(); i++)
        {
            fout<<song.get_lyrics()[i];
            fout<<std::endl;
        }
        fout<<std::endl;
    }

    fout.close();
}

void FileRepo::store(const Song& s)
{
    Repo::store(s); // Call the parent class implementation

    // Save the updated data to the file
    std::ofstream fout(filepath, std::ios::app); // Open the file in append mode
    if (fout.is_open())
    {
        fout<<s.get_title()<<std::endl;
        fout<<s.get_artist()<<std::endl;

        fout<<s.get_year()<<std::endl;
        fout<<s.get_url()<<std::endl;


        for(int i =0; i<s.get_lyrics().size(); i++)
        {
            fout<<s.get_lyrics()[i];
            fout<<std::endl;
        }
        fout<<std::endl;
        fout.close();
    }
    else
    {
        throw std::runtime_error("Unable to open the file for writing.");
    }

}

void FileRepo::remove(const Song& s)
{
    Repo::remove(s);// Call the parent class implementation

    // Save the updated data to the file
    std::ofstream file(filepath);
    if (file.is_open())
    {
        std::ofstream file(filepath, std::ios::trunc); // Open the file in truncate mode

        // Check if the file is opened successfully
        if (file.is_open())
        {
            // File is opened successfully, so it can be considered empty now
            file.close();
        }
        else
        {
            // Failed to open the file
            throw std::runtime_error("Failed to open: " + filepath);
        }

        save();
    }
    else
    {
        throw std::runtime_error("Unable to open the file for writing.");
    }

}

std::vector<Song> FileRepo::getSongsList()
{
    return this->_songs;
}
