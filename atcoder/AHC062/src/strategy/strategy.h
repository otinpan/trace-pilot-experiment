#pragma once
#include<iostream>
#include<vector>
#include<random>

#include"../common.h"
#include"../state.h"
#include"../logger.h"
#include"../timer.h"

class Strategy{
  public:
    Strategy();
    virtual ~Strategy();

    virtual std::vector<std::pair<char,char>> solve(State& state,Logger& logger);

  protected:
    std::mt19937 rng_;
    int score(const State& state) const;
};
