#include "SongController.h"
#include<algorithm>
#include<iostream>



std::vector<Song> SongController::get_all_songs()
{
    return this->repository.get_all_songs();
}

void SongController::clear()
{
    this->repository.clear();
}

void SongController::add_song(const std::string title,const std::string artist,const int year,
                                        const std::string url, const std::vector<std::string> lyrics)
{
    Song newSong(title, artist, year, url, lyrics);
    repository.store(newSong);
    action_undo.push(new ActionAdd{repository, newSong});
    action_redo = std::stack<Action*>();
}

void SongController::remove(const Song& s)
{
    repository.remove(s);

    action_redo.push(new ActionAdd{repository, s});
    //action_undo.push(new ActionAdd{repository, s});
    action_redo = std::stack<Action*>();
}

const Song& SongController::search_song(const std::string& title,const std::string& artist)
{
    return repository.find(title, artist);
}

std::vector<Song> SongController::sortByArtist(bool ascendingOrder)
{
    std::vector<Song> sortedSongs = repository.get_all_songs();
    std::sort(sortedSongs.begin(), sortedSongs.end(), [&](const Song& s1, const Song& s2)
              {
                  if (ascendingOrder)
                  {
                      return s1.get_artist() < s2.get_artist();
                  }
                  else
                  {
                      return s1.get_artist() > s2.get_artist();
                  }
              });
    return sortedSongs;
}

std::vector<Song> SongController::sortByTitle(bool ascendingOrder)
{
    std::vector<Song> sortedSongs = repository.get_all_songs();
    std::sort(sortedSongs.begin(), sortedSongs.end(), [&](const Song& s1, const Song& s2)
              {
                  if (ascendingOrder)
                  {
                      return s1.get_title() < s2.get_title();
                  }
                  else
                  {
                      return s1.get_title() > s2.get_title();
                  }
              });
    return sortedSongs;
}

void SongController::undo()
{
    if(!action_undo.empty())
    {
        Action* temp = action_undo.top();
        action_undo.pop();
        action_redo.push(temp);
        temp->applyUndo();
        delete temp;
    }
    std::cout<<action_redo.size()<<std::endl;
}

void SongController::redo()
{
   if (!action_redo.empty())
    {
        Action* action = action_redo.top(); // Get the most recent undone action
        action_redo.pop();
        action->applyRedo(); // Apply the redo operation
        action_undo.push(action);
        //delete action;
    }
}

