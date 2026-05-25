#pragma once
#include<iostream>
#include<utility>
#include<vector>

#include"common.h"
#include"logger.h"
#include"state.h"
#include"strategy/strategy.h"

class Simulator{
  public:
    Simulator(
        State state,
        Strategy& strategy,
        Logger& logger
    );
    ~Simulator();

    std::vector<std::pair<char,char>> simulate();

  private:
    State state_;
    Strategy& strategy_;
    Logger& logger_;
};
