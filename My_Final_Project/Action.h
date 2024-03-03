#ifndef ACTION_H
#define ACTION_H

#include "Repo.h"
#include<iostream>

class Action
{
public:
    Repo& _repo;
    Song _song;
public:
    Action(Repo& r, Song s): _repo{r}, _song{s}{};
    virtual void applyUndo()= 0;
    virtual void applyRedo() = 0;
    virtual ~Action() = default;
};

class ActionAdd : public Action
{
public:
    ActionAdd(Repo& r, Song s):Action{r, s}{};
    void applyUndo() override
    {
        _repo.remove(_song);
    }
    void applyRedo() override
    {
        _repo.store(_song);
    }
};

class ActionDelete : public Action
{
public:
    ActionDelete(Repo& r, Song s):Action{r, s}{};
    void applyRedo() override
    {
        _repo.store(_song);
    }
    void applyUndo() override
    {
        _repo.remove(_song);
    }
};

#endif // ACTION_H
