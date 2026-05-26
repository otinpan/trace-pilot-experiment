#pragma once
#include<iostream>
#include<vector>

#include"common.h"

class State{
  public:
    State(std::vector<std::vector<int>> kingdom);
    ~State();

    bool apply(Direction dir);
    void undo();

    const std::vector<std::vector<int>>& kingdom() const {return kingdom_;}
    const Pos& pos() const {return pos_;}
    const std::vector<Pos>& visited() const {return visited_;}
    const std::vector<Direction>& path() const {return path_;}
    long long score() const {return score_;}
    int turn() const {return turn_;}

  private:
    std::vector<std::vector<int>> init_kingdom_; // kingdomの初期値
    std::vector<std::vector<int>> kingdom_; // 今のkingdomの状態 -1がvisited
    Pos pos_;
    std::vector<Direction> path_;
    std::vector<Pos> visited_;
    // @trace-pilot 1b115d9534ad365932dccdab9e5c7de0b6dac331
    // intだとscore = -170177899
    long long score_;
    int turn_;
};
