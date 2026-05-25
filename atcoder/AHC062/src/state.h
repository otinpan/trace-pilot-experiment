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

  private:
    std::vector<std::vector<int>> init_kingdom_; // kingdomの初期値
    std::vector<std::vector<int>> kingdom_; // 今のkingdomの状態 -1がvisited
    Pos pos_;
    std::vector<Direction> path_;
    std::vector<Pos> visited_;
};
